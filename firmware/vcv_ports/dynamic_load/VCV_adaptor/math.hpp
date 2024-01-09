#pragma once
#include <algorithm>
#include <cmath>

namespace rack::math
{

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880f
#endif
#ifndef M_E
#define M_E 2.7182818284590452354f
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2	0.70710678118654752440f
#endif

// #define M_LOG2E 1.4426950408889634074f
// #define M_LOG10E 0.43429448190325182765f
// #define M_LN2 _M_LN2
// #define M_LN10 2.30258509299404568402f
// #define M_PI 3.14159265358979323846f
// #define M_PI_2 1.57079632679489661923f
// #define M_PI_4 0.78539816339744830962f
// #define M_1_PI 0.31830988618379067154f
// #define M_2_PI 0.63661977236758134308f
// #define M_2_SQRTPI 1.12837916709551257390f
// #define M_SQRT2 1.41421356237309504880f

////////////////////
// basic integer functions
////////////////////

/** Returns true if `x` is odd. */
template<typename T>
bool isEven(T x) {
	return x % 2 == 0;
}

/** Returns true if `x` is odd. */
template<typename T>
bool isOdd(T x) {
	return x % 2 != 0;
}

/** Limits `x` between `a` and `b`.
If `b < a`, returns a.
*/
int clamp(int x, int a, int b);

/** Limits `x` between `a` and `b`.
If `b < a`, switches the two values.
*/
int clampSafe(int x, int a, int b);

/** Euclidean modulus. Always returns `0 <= mod < b`.
`b` must be positive.
See https://en.wikipedia.org/wiki/Euclidean_division
*/
int eucMod(int a, int b);

/** Euclidean division.
`b` must be positive.
*/
int eucDiv(int a, int b);
void eucDivMod(int a, int b, int *div, int *mod);

/** Returns `floor(log_2(n))`, or 0 if `n == 1`. */
int log2(int n);

/** Returns whether `n` is a power of 2. */
template<typename T>
bool isPow2(T n) {
	return n > 0 && (n & (n - 1)) == 0;
}

/** Returns 1 for positive numbers, -1 for negative numbers, and 0 for zero.
See https://en.wikipedia.org/wiki/Sign_function.
*/
template<typename T>
T sgn(T x) {
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

////////////////////
// basic float functions
////////////////////

/** Limits `x` between `a` and `b`.
If `b < a`, returns a.
*/
float clamp(float x, float a = 0.f, float b = 1.f);

/** Limits `x` between `a` and `b`.
If `b < a`, switches the two values.
*/
float clampSafe(float x, float a = 0.f, float b = 1.f);

/** Converts -0.f to 0.f. Leaves all other values unchanged. */
#if defined __clang__
// Clang doesn't support disabling individual optimizations, just everything.
__attribute__((optnone))
#else
__attribute__((optimize("signed-zeros")))
#endif
inline float
normalizeZero(float x) {
	return x + 0.f;
}

/** Euclidean modulus. Always returns `0 <= mod < b`.
See https://en.wikipedia.org/wiki/Euclidean_division.
*/
float eucMod(float a, float b);

/** Returns whether `a` is within epsilon distance from `b`. */
bool isNear(float a, float b, float epsilon = 1e-6f) ;

/** If the magnitude of `x` if less than epsilon, return 0. */
float chop(float x, float epsilon = 1e-6f) ;

/** Rescales `x` from the range `[xMin, xMax]` to `[yMin, yMax]`.
*/
float rescale(float x, float xMin, float xMax, float yMin, float yMax) ;

/** Linearly interpolates between `a` and `b`, from `p = 0` to `p = 1`.
*/
float crossfade(float a, float b, float p) ;

/** Linearly interpolates an array `p` with index `x`.
The array at `p` must be at least length `floor(x) + 2`.
*/
float interpolateLinear(const float *p, float x) ;

/** Complex multiplication `c = a * b`.
Arguments may be the same pointers.
Example:

	cmultf(ar, ai, br, bi, &ar, &ai);
*/
void complexMult(float ar, float ai, float br, float bi, float *cr, float *ci) ;

////////////////////
// 2D vector and rectangle
////////////////////

struct Rect;

/** 2-dimensional vector of floats, representing a point on the plane for graphics.
*/
struct Vec {
	float x = 0.f;
	float y = 0.f;

	Vec() = default;
	Vec(float xy)
		: x(xy)
		, y(xy) {
	}
	Vec(float x, float y)
		: x(x)
		, y(y) {
	}

	float &operator[](int i) {
		return (i == 0) ? x : y;
	}
	const float &operator[](int i) const {
		return (i == 0) ? x : y;
	}
	/** Negates the vector.
	Equivalent to a reflection across the `y = -x` line.
	*/
	Vec neg() const {
		return {-x, -y};
	}
	Vec plus(Vec b) const {
		return {x + b.x, y + b.y};
	}
	Vec minus(Vec b) const {
		return {x - b.x, y - b.y};
	}
	Vec mult(float s) const {
		return {x * s, y * s};
	}
	Vec mult(Vec b) const {
		return {x * b.x, y * b.y};
	}
	Vec div(float s) const {
		return {x / s, y / s};
	}
	Vec div(Vec b) const {
		return {x / b.x, y / b.y};
	}
	float dot(Vec b) const {
		return x * b.x + y * b.y;
	}
	float arg() const ;
	float norm() const ;
	Vec normalize() const {
		return div(norm());
	}
	float square() const {
		return x * x + y * y;
	}
	float area() const {
		return x * y;
	}
	/** Rotates counterclockwise in radians. */
	Vec rotate(float angle) ;
	/** Swaps the coordinates.
	Equivalent to a reflection across the `y = x` line.
	*/
	Vec flip() const {
		return {y, x};
	}
	Vec min(Vec b) const ;
	Vec max(Vec b) const ;
	Vec abs() const ;
	Vec round() const ;
	Vec floor() const ;
	Vec ceil() const ;
	bool equals(Vec b) const {
		return x == b.x && y == b.y;
	}
	bool isZero() const {
		return x == 0.f && y == 0.f;
	}
	bool isFinite() const ;
	Vec clamp(Rect bound) const;
	Vec clampSafe(Rect bound) const;
	Vec crossfade(Vec b, float p) ;

	// Method aliases
	bool isEqual(Vec b) const {
		return equals(b);
	}
};

/** 2-dimensional rectangle for graphics.
Mathematically, Rects include points on its left/top edge but *not* its right/bottom edge.
The infinite Rect (equal to the entire plane) is defined using pos=-inf and size=inf.
*/
struct Rect {
	Vec pos;
	Vec size;

	Rect() = default;
	Rect(Vec pos, Vec size)
		: pos(pos)
		, size(size) {
	}
	Rect(float posX, float posY, float sizeX, float sizeY)
		: pos(Vec(posX, posY))
		, size(Vec(sizeX, sizeY)) {
	}
	/** Constructs a Rect from a top-left and bottom-right vector.
	*/
	static Rect fromMinMax(Vec a, Vec b) ;
	/** Constructs a Rect from any two opposite corners.
	*/
	static Rect fromCorners(Vec a, Vec b) ;
	/** Returns the infinite Rect. */
	static Rect inf() ;

	/** Returns whether this Rect contains a point, inclusive on the left/top, exclusive on the right/bottom.
	Correctly handles infinite Rects.
	*/
	bool contains(Vec v) const ;
	/** Returns whether this Rect contains (is a superset of) a Rect.
	Correctly handles infinite Rects.
	*/
	bool contains(Rect r) const ;
	/** Returns whether this Rect overlaps with another Rect.
	Correctly handles infinite Rects.
	*/
	bool intersects(Rect r) const ;
	bool equals(Rect r) const ;
	float getLeft() const {
		return pos.x;
	}
	float getRight() const {
		return (size.x == INFINITY) ? INFINITY : (pos.x + size.x);
	}
	float getTop() const {
		return pos.y;
	}
	float getBottom() const {
		return (size.y == INFINITY) ? INFINITY : (pos.y + size.y);
	}
	float getWidth() const {
		return size.x;
	}
	float getHeight() const {
		return size.y;
	}
	/** Returns the center point of the rectangle.
	Returns a NaN coordinate if pos=-inf and size=inf.
	*/
	Vec getCenter() const {
		return pos.plus(size.mult(0.5f));
	}
	Vec getTopLeft() const {
		return pos;
	}
	Vec getTopRight() const {
		return {getRight(), getTop()};
	}
	Vec getBottomLeft() const {
		return {getLeft(), getBottom()};
	}
	Vec getBottomRight() const {
		return {getRight(), getBottom()};
	}
	/** Clamps the edges of the rectangle to fit within a bound. */
	Rect clamp(Rect bound) const ;
	/** Nudges the position to fix inside a bounding box. */
	Rect nudge(Rect bound) const ;
	/** Returns the bounding box of the union of `this` and `b`. */
	Rect expand(Rect b) const ;
	/** Returns the intersection of `this` and `b`. */
	Rect intersect(Rect b) const ;
	/** Returns a Rect with its position set to zero. */
	Rect zeroPos() const ;
	/** Expands each corner. */
	Rect grow(Vec delta) const ;
	/** Contracts each corner. */
	Rect shrink(Vec delta) const ;
	/** Returns `pos + size * p` */
	Vec interpolate(Vec p) ;

	// Method aliases
	bool isContaining(Vec v) const ;
	bool isIntersecting(Rect r) const ;
	bool isEqual(Rect r) const ;
};

// Vec Vec::clamp(Rect bound) const ;

// inline Vec Vec::clampSafe(Rect bound) const ;

// Operator overloads for Vec
inline Vec operator+(const Vec &a) {
	return a;
}
inline Vec operator-(const Vec &a) {
	return a.neg();
}
inline Vec operator+(const Vec &a, const Vec &b) {
	return a.plus(b);
}
inline Vec operator-(const Vec &a, const Vec &b) {
	return a.minus(b);
}
inline Vec operator*(const Vec &a, const Vec &b) {
	return a.mult(b);
}
inline Vec operator*(const Vec &a, const float &b) {
	return a.mult(b);
}
inline Vec operator*(const float &a, const Vec &b) {
	return b.mult(a);
}
inline Vec operator/(const Vec &a, const Vec &b) {
	return a.div(b);
}
inline Vec operator/(const Vec &a, const float &b) {
	return a.div(b);
}
inline Vec operator+=(Vec &a, const Vec &b) {
	return a = a.plus(b);
}
inline Vec operator-=(Vec &a, const Vec &b) {
	return a = a.minus(b);
}
inline Vec operator*=(Vec &a, const Vec &b) {
	return a = a.mult(b);
}
inline Vec operator*=(Vec &a, const float &b) {
	return a = a.mult(b);
}
inline Vec operator/=(Vec &a, const Vec &b) {
	return a = a.div(b);
}
inline Vec operator/=(Vec &a, const float &b) {
	return a = a.div(b);
}
inline bool operator==(const Vec &a, const Vec &b) {
	return a.equals(b);
}
inline bool operator!=(const Vec &a, const Vec &b) {
	return !a.equals(b);
}

// Operator overloads for Rect
inline bool operator==(const Rect &a, const Rect &b) {
	return a.equals(b);
}
inline bool operator!=(const Rect &a, const Rect &b) {
	return !a.equals(b);
}

/** Expands a Vec and Rect into a comma-separated list.
Useful for print debugging.

	printf("(%f %f) (%f %f %f %f)", VEC_ARGS(v), RECT_ARGS(r));

Or passing the values to a C function.

	nvgRect(vg, RECT_ARGS(r));
*/
#define VEC_ARGS(v) (v).x, (v).y
#define RECT_ARGS(r) (r).pos.x, (r).pos.y, (r).size.x, (r).size.y

} // namespace rack::math
