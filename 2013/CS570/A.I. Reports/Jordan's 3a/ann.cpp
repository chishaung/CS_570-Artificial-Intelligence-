#include "ann.h"
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;


ann::ann(int numInput, int numHidden, int numOutput){
	srand(time(NULL));
	//number of input + 1 for bias node
	NUMINPUT = numInput;
	//number of hidden
	NUMHIDDEN = numHidden;
	//number of output
	NUMOUTPUT = numOutput;
	//number of targets we are looking for
	NUMTARGETS = 2;

	ACTIVE_IN = new float [NUMINPUT];
	ACTIVE_HID = new float [NUMHIDDEN];
	ACTIVE_OUT = new float [NUMOUTPUT];

	
	//activation functions need to be arrays
	for(int i = 0; i < NUMINPUT; i++){
		ACTIVE_IN[i] = 1.0;
	}
	for(int i = 0; i < NUMHIDDEN; i++){
		ACTIVE_HID[i] = 1.0;
	}
	for(int i = 0; i < NUMOUTPUT; i++){
		ACTIVE_OUT[i] = 1.0;
	}
	
	//make the input -> hidden matrix
	for(int i = 0; i < NUMINPUT; i++){
		for(int j = 0; j < NUMHIDDEN; j++){
			float var = rand() % 4 - 2;
			var = var/10;
			WEIGHT_IN[i][j] = var;
			MOMENT_IN[i][j] = 0.0;
		}
	}
	//make the hidden -> output matrix
	for(int i = 0; i < NUMHIDDEN; i++){
		for(int j = 0; j < NUMOUTPUT; j++){
			float var = rand() % 4 - 2;
			WEIGHT_OUT[i][j] = var;
			MOMENT_OUT[i][j] = 0.0;
		}
	}
}


ann::~ann(void)
{
}

float ann::Activation(float x){
	return tanh(x);
	//return 1/(1+exp(-x));
}
void ann::makeMatrix(int rows, int cols, float value, float **matrix){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			matrix[i][j] = value;
		}
	}
}
float ann::dActivation(float x){
	return (1 - (x*x));
	//return exp(x)/((exp(x) + 1)*(exp(x) + 1));
}

void ann::update(float *inputs, float *burn, float *thrust){
	float sum = 0.0;

	for(int i = 0; i < NUMINPUT; i++){
		//activation matrix?
		ACTIVE_IN[i] = Activation(inputs[i]/200);
		//cout << "IN " << ACTIVE_IN[i] << endl;
	}

	for(int i = 0; i < NUMHIDDEN; i++){
		sum = 0.0;
		for(int j = 0; j < NUMINPUT; j++){
			sum = sum + ACTIVE_IN[j] * WEIGHT_IN[j][i];
		}
		ACTIVE_HID[i] = Activation(sum);
		//cout << "HID " << ACTIVE_HID[i] << endl;
	}

	//output activation
	for(int i = 0; i < NUMOUTPUT; i++){
		sum = 0.0;
		for(int j = 0; j < NUMHIDDEN; j++){
			sum = sum + ACTIVE_HID[j] * WEIGHT_OUT[j][i];
		}
		ACTIVE_OUT[i] = Activation(sum);
		//cout << "OUT " << ACTIVE_OUT[i] << endl;
	}

	*burn = 200*ACTIVE_OUT[0];
	*thrust = 200*ACTIVE_OUT[1];
}

float ann::backPropogate(float *targets, float learning_rate, float momentum_factor){
	float error;
	float change;
	float *output_deltas = new float[NUMOUTPUT];
	float *hidden_deltas = new float[NUMHIDDEN];

	//calculate the error terms for output
	for(int i = 0; i < NUMOUTPUT; i++){
		error = (targets[i]/200) - ACTIVE_OUT[i];
		output_deltas[i] = dActivation(ACTIVE_OUT[i]) * error;
	}
	
	//now calculate the errors for the hidden nodes
	for(int i = 0; i < NUMHIDDEN; i++){
		error = 0.0;
		for(int j = 0; j < NUMOUTPUT; j++){
			error = error + output_deltas[j] * WEIGHT_OUT[i][j];
		}
		hidden_deltas[i] = dActivation(ACTIVE_HID[i]) * error;
	}

	//update the output weights
	for(int i = 0; i < NUMHIDDEN; i++){
		for(int j = 0; j < NUMOUTPUT; j++){
			change = output_deltas[j]*ACTIVE_HID[i];
			WEIGHT_OUT[i][j] = WEIGHT_OUT[i][j] + learning_rate*change + momentum_factor*MOMENT_OUT[i][j];
			MOMENT_OUT[i][j] = change;
		}
	}

	//update the input weights
	for(int i = 0; i < NUMINPUT; i++){
		for(int j = 0; j < NUMHIDDEN; j++){
			change = hidden_deltas[j]*ACTIVE_IN[i];
			WEIGHT_IN[i][j] = WEIGHT_IN[i][j] + learning_rate*change + momentum_factor*MOMENT_IN[i][j];
			MOMENT_IN[i][j] = change;
		}
	}

	//calculate the error
	error = 0.0;
	for(int i = 0; i < NUMTARGETS; i++){
		error = error + 0.5*((targets[i]/200) - ACTIVE_OUT[i])*((targets[i]/200) - ACTIVE_OUT[i]);
	}
	return error;
}

void ann::printWeight(){
	for(int i = 0; i < NUMINPUT; i++){
		for(int j = 0; j < NUMHIDDEN; j++){
			cout << setw(7) << WEIGHT_IN[i][j];
		}
		cout << endl;
	}

	cout << "WEIGHT IN" << endl;
}

