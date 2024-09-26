#include "util/math.hh"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

const int fold_size = 1025;

float cheby[16][513];

float fold[1025];
float fold_max[513];

const float triangles[8][9] = {
	{
		-1.00000000000000000000000000000000f,
		-0.75000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		-0.25000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		0.25000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		0.75000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-0.66666000000000003034017481695628f,
		-0.33333000000000001517008740847814f,
		0.00000000000000000000000000000000f,
		0.33333000000000001517008740847814f,
		0.66666000000000003034017481695628f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		-0.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		-1.00000000000000000000000000000000f,
		-0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		0.50000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
	},
	{
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		0.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
		1.00000000000000000000000000000000f,
		-1.00000000000000000000000000000000f,
	},
};

// [0..1] --> [-1..1]
static float faster_sine(float x)
{
	x = (x * 2.f) - 1.f;
	return 4.f * (x - x * fabsf(x));
}

// [0..1] --> [-1..1]
static float fast_sine(float x)
{
	float y = faster_sine(x);
	y = 0.225f * (y * fabsf(y) - y) + y;
	return y;
}

std::string format_float(float x)
{
	std::string s = std::to_string(x);
	if (s.find('.') == std::string::npos)
		return s + ".f";
	else
		return s + "f";
}

void buildFoldTables()
{
	ofstream myfile;
	myfile.open("../processors/wavefold_tables.h");

	myfile << "#pragma once" << endl;

	myfile << "#include"
		   << "\""
		   << "interp_array.hh"
		   << "\"" << endl;

	// cheby table generation

	const int cheby_size = 513;
	const int cheby_tables = 16;

	// cheby[1] = [-1..1]
	for (int i = 0; i < cheby_size; i++)
		cheby[0][i] = float(i * 2) / float(cheby_size - 1) - 1.0f;

	// cheby[2] = 2 * cheby[1] * cheby[1] - 1
	for (int i = 0; i < cheby_size; i++)
		cheby[1][i] = 2.0f * cheby[0][i] * cheby[0][i] - 1.0f;

	// cheby[n] = 2 * cheby[1] * cheby[n-1] - cheby[n-2]
	for (int n = 2; n < cheby_tables; n++)
		for (int i = 0; i < cheby_size; i++)
			cheby[n][i] = 2.0f * cheby[0][i] * cheby[n - 1][i] - cheby[n - 2][i];

	myfile << "extern const InterpArray<float, 513> cheby[16] = " << endl << "{";

	for (int i = 0; i < 16; i++) {
		if (i == 0)
			myfile << endl;
		myfile << "{";
		for (int x = 0; x < 513; x++) {
			myfile << format_float(cheby[i][x]) << ",";
		}
		if (i < 15)
			myfile << "}," << endl;
		else {
			myfile << "}" << endl;
			myfile << "};";
		}
	}

	myfile << endl;

	// fold table generation

	const int fold_size = 1025;

	{
		float folds = 6.0f;
		fold[0] = 0.0f;
		for (int i = 1; i < fold_size; ++i) {
			// TODO: this -3 make the wavefolding curve symmetrical; why?
			float x = float(i - 1) / float(fold_size - 3); // 0..1
			x = folds * (2.0f * x - 1.0f);				   // -folds..folds
			float g = 1.0f / (1.0f + fabsf(x));			   // 0..0.5
			float p = 16.0f / (2.0f * M_PI) * x * g;
			while (p > 1.0f)
				p--;
			while (p < 0.0f)
				p++;
			x = -g * (x + fast_sine(p));
			fold[i] = x;
		}
	}

	myfile << "extern const InterpArray<float, 1025> fold = " << endl;
	myfile << "{ ";

	for (int i = 0; i < 1025; i++) {
		myfile << format_float(fold[i]) << ",";
	}
	myfile << "};" << endl;

	// fold max table generation
	{
		float max = 0.f;
		int start = (fold_size - 1) / 2;
		for (int i = 0; i < 513; ++i) {
			max = std::max(fabsf(fold[i + start]), max);
			// the attenuation factor accounts for interpolation error, so
			// we don't overestimate the 1/x curve and amplify to clipping
			if (max == 0.0f)
				fold_max[i] = 0.0f;
			else
				fold_max[i] = 0.95f / (max);
		}
	}

	myfile << "extern const InterpArray<float, 513> fold_max = " << endl << "{";

	for (int i = 0; i < 513; i++) {
		myfile << format_float(fold_max[i]) << ",";
	}
	myfile << "};" << endl;

	myfile << "extern const InterpArray<float, 9> triangles[8] = " << endl;
	myfile << "{" << endl;

	for (int i = 0; i < 8; i++) {
		myfile << "{";
		for (int x = 0; x < 9; x++) {
			myfile << format_float(triangles[i][x]) << ",";
		}
		myfile << "}," << endl;
	}
	myfile << "};" << endl;

	myfile.close();
}

void buildTrigTables()
{
	ofstream myfile;
	myfile.open("../cpputil/util/math_tables.cc");

	myfile << "#include"
		   << "\""
		   << "interp_array.hh"
		   << "\"" << endl;

	const int trigTableLength = 2048;

	myfile << "extern const InterpArray<float," << trigTableLength << "> sinTable = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / (float)trigTableLength;
		myfile << format_float(sinf(index * 2.0f * M_PI)) << ",";
	}
	myfile << "};" << endl;

	myfile << "extern const InterpArray<float," << trigTableLength << "> tanTable = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / (float)trigTableLength * M_PI;
		myfile << format_float(tan(index)) << ",";
	}
	myfile << "};" << endl;

	float voltageRange = 5.f;
	float powRange = (float)(trigTableLength - 1) / voltageRange;
	myfile << "extern const InterpArray<float," << trigTableLength << "> exp5Table = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / powRange;
		myfile << format_float(powf(2.0f, index)) << ",";
	}
	myfile << "};" << endl;

	voltageRange = 10.f;
	powRange = (float)(trigTableLength - 1) / voltageRange;
	myfile << "extern const InterpArray<float," << trigTableLength << "> exp10Table = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / powRange;
		myfile << format_float(powf(2.0f, index)) << ",";
	}
	myfile << "};" << endl;

	myfile << "extern const InterpArray<float," << trigTableLength << "> pow9Table = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / (float)(trigTableLength - 1);
		myfile << format_float(powf(index, 8.8f)) << ",";
	}
	myfile << "};" << endl;

	myfile << "extern const InterpArray<float," << trigTableLength << "> logTable = " << endl;
	myfile << "{";
	for (int i = 0; i < trigTableLength; i++) {
		float index = (float)i / (float)(trigTableLength - 1);
		myfile << format_float(logf(MathTools::map_value(index, 0.0f, 1.0f, 20.0f, 20000.0f))) << ",";
	}
	myfile << "};" << endl;

	myfile.close();
}

int main()
{
	buildFoldTables();
	buildTrigTables();

	return 0;
}
