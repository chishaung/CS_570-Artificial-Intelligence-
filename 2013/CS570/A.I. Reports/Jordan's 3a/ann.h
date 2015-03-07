
#ifndef ANN_H
#define ANN_H
#pragma once
class ann
{
private:
	
	float Activation(float);
	void makeMatrix(int, int, float, float**);
	float dActivation(float);

public:
	int NUMINPUT;
	int NUMHIDDEN;
	int NUMOUTPUT;
	int NUMTARGETS;

	float *ACTIVE_IN;
	float *ACTIVE_HID;
	float *ACTIVE_OUT;

	float WEIGHT_IN [7][7];
	float WEIGHT_OUT [7][2];

	float MOMENT_IN [7][7];
	float MOMENT_OUT [7][2];
	ann(int, int, int);
	~ann(void);

	void update(float*, float *, float *);
	float backPropogate(float *, float, float);
	void printWeight();
};

#endif


