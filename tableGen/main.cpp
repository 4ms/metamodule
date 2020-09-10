#include <fstream>
#include <iostream>

#include "math.h"
#include <cmath>
using namespace std;

const int fold_size = 1025;

float cheby[16][513];

float fold[1025];
float fold_max[513];

int main()
{
	ofstream myfile;

	myfile.open("src/processors/wavefold_tables.h");

	//cheby table generation

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

	myfile << "const float newcheby[16][513] = " << endl
		   << "{";

	for (int i = 0; i < 16; i++) {
		if (i == 0)
			myfile << endl;
		myfile << "{";
		for (int x = 0; x < 513; x++) {
			myfile << cheby[i][x] << ",";
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
			float x = float(i) / float(fold_size - 3); // 0..1
			x = folds * (2.0f * x - 1.0f);			   // -folds..folds
			float g = 1.0f / (1.0f + fabsf(x));		   // 0..0.5
			float p = 16.0f / (2.0f * M_PI) * x * g;
			while (p > 1.0f)
				p--;
			while (p < 0.0f)
				p++;
			x = -g * (x + sin(p));
			fold[i] = x;
		}
	}

	myfile << "const float newfold[1025] = " << endl;
	myfile << "{ ";

	for (int i = 0; i < 1025; i++) {
		myfile << fold[i] << ",";
	}

	myfile << "};" << endl;

	//fold max table generation
	{
		float max = 0.f;
		int start = (fold_size - 1) / 2;
		for (int i = 0; i < 513; ++i) {
			max = std::max(std::fabsf(fold[i + start]), max);
			// the attenuation factor accounts for interpolation error, so
			// we don't overestimate the 1/x curve and amplify to clipping
			fold_max[i] = 0.95f / (max);
		}
	}

	myfile << "const float fold_max[513] = " << endl
		   << "{";

	for (int i = 0; i < 513; i++) {
		if (i < 512)
			myfile << fold_max[i] << ",";
		else
			myfile << fold_max[i] << "};" << endl;
	}

	myfile.close();
	return 0;
}