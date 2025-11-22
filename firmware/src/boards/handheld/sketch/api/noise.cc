#include "../api.hh"
#include <cmath>

namespace Handheld
{

// Perlin noise implementation based on Ken Perlin's improved noise
// Reference: https://mrl.nyu.edu/~perlin/noise/

namespace
{

// Permutation table (repeated twice to avoid overflow)
// clang-format off
constexpr int permutation[] = {
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
	240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177,
	33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146,
	158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
	63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100,
	109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206,
	59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153,
	101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246,
	97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192,
	214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
	67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
	// Repeat
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
	240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177,
	33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146,
	158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
	63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100,
	109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206,
	59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153,
	101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246,
	97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192,
	214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
	67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

// clang-format on
static_assert(sizeof(permutation) == 512 * sizeof(int));

// Fade function for smooth interpolation: 6t^5 - 15t^4 + 10t^3
inline float fade(float t) {
	return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

// Gradient for 1D noise
inline float grad1d(int hash, float x) {
	// Use the lower bit to determine gradient direction
	int h = hash & 1;
	return h == 0 ? x : -x;
}

// Gradient for 2D noise
inline float grad2d(int hash, float x, float y) {
	// Convert hash to one of 8 gradient directions
	int h = hash & 7;
	float u = h < 4 ? x : y;
	float v = h < 4 ? y : x;
	return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
}

// Gradient for 3D noise
inline float grad3d(int hash, float x, float y, float z) {
	// Convert hash to one of 12 gradient directions
	int h = hash & 15;
	float u = h < 8 ? x : y;
	float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

} // namespace

float noise(float x) {
	// Find unit cube that contains point
	int X = (int)std::floor(x) & 255;

	// Find relative x in cube
	x -= std::floor(x);

	// Compute fade curve
	float u = fade(x);

	// Hash coordinates
	int a = permutation[X];
	int b = permutation[X + 1];

	// Interpolate between gradients
	float result = lerp(grad1d(a, x), grad1d(b, x - 1.0f), u);

	// Map from [-1, 1] to [0, 1] for Processing compatibility
	return (result + 1.0f) * 0.5f;
}

float noise(float x, float y) {
	// Find unit square that contains point
	int X = (int)std::floor(x) & 255;
	int Y = (int)std::floor(y) & 255;

	// Find relative x, y in square
	x -= std::floor(x);
	y -= std::floor(y);

	// Compute fade curves
	float u = fade(x);
	float v = fade(y);

	// Hash coordinates of square corners
	int a = permutation[X] + Y;
	int b = permutation[X + 1] + Y;

	// Interpolate between gradients
	float result =
		lerp(lerp(grad2d(permutation[a], x, y), grad2d(permutation[b], x - 1.0f, y), u),
			 lerp(grad2d(permutation[a + 1], x, y - 1.0f), grad2d(permutation[b + 1], x - 1.0f, y - 1.0f), u),
			 v);

	// Map from [-1, 1] to [0, 1] for Processing compatibility
	return (result + 1.0f) * 0.5f;
}

float noise(float x, float y, float z) {
	// Find unit cube that contains point
	int X = (int)std::floor(x) & 255;
	int Y = (int)std::floor(y) & 255;
	int Z = (int)std::floor(z) & 255;

	// Find relative x, y, z in cube
	x -= std::floor(x);
	y -= std::floor(y);
	z -= std::floor(z);

	// Compute fade curves
	float u = fade(x);
	float v = fade(y);
	float w = fade(z);

	// Hash coordinates of cube corners
	int a = permutation[X] + Y;
	int aa = permutation[a] + Z;
	int ab = permutation[a + 1] + Z;
	int b = permutation[X + 1] + Y;
	int ba = permutation[b] + Z;
	int bb = permutation[b + 1] + Z;

	// Interpolate between gradients
	float result = lerp(
		lerp(lerp(grad3d(permutation[aa], x, y, z), grad3d(permutation[ba], x - 1.0f, y, z), u),
			 lerp(grad3d(permutation[ab], x, y - 1.0f, z), grad3d(permutation[bb], x - 1.0f, y - 1.0f, z), u),
			 v),
		lerp(lerp(grad3d(permutation[aa + 1], x, y, z - 1.0f), grad3d(permutation[ba + 1], x - 1.0f, y, z - 1.0f), u),
			 lerp(grad3d(permutation[ab + 1], x, y - 1.0f, z - 1.0f),
				  grad3d(permutation[bb + 1], x - 1.0f, y - 1.0f, z - 1.0f),
				  u),
			 v),
		w);

	// Map from [-1, 1] to [0, 1] for Processing compatibility
	return (result + 1.0f) * 0.5f;
}

} // namespace Handheld
