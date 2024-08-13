#pragma once

class DCBlock {
public:
	DCBlock()
	{
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
	}

	virtual float update(float input)
	{
		float output = 0;
		float fTemp0 = float(input);
		fVec0[0] = fTemp0;
		fRec0[0] = ((fTemp0 + (0.995000005f * fRec0[1])) - fVec0[1]);
		output = float(fRec0[0]);
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];

		return (output);
	}

private:
	float fVec0[2];
	float fRec0[2];
};