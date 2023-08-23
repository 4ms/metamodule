#include <cstdio>
#include <cstdlib>

namespace rack::dsp
{
void minBlepImpulse(int z, int o, float *output);
}

#include <vector>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(
			"Usage: gen_minblep Z C\n\nWhere Z is the number of Zero Crossings, and C is the amount of Oversampling\n");
		return -1;
	}

	unsigned ZeroXings = atoi(argv[1]);
	unsigned Oversample = atoi(argv[2]);

	if (ZeroXings * Oversample > 16384) {
		printf("Z * C must be < 16384\n");
		return -2;
	}

	std::vector<float> output;
	output.resize(ZeroXings * Oversample * 2 + 1);

	rack::dsp::minBlepImpulse(ZeroXings, Oversample, output.data());

	output[output.size() - 1] = 1.f;

	unsigned i = 0;
	printf("#pragma once\n");
	printf("#include <array>\n");
	printf("\n");
	printf("constexpr std::array<float, %zu> MinBlep_%d_%d = {\n", output.size(), ZeroXings, Oversample);
	for (auto x : output) {
		printf("%f, ", x);
		if (i++ == 15) {
			i = 0;
			printf("\n");
		}
	}
	printf("};\n");
}
