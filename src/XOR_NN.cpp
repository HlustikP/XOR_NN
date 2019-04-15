#include "pch.h"

// XOR Input
std::vector<float> dataInput{
	0.0, 0.0,
	0.0, 1.0,
	1.0, 0.0,
	1.0, 1.0 };

//  Expected Output
std::vector<float> dataExpected{
	0.0,
	1.0,
	1.0,
	0.0 };

int main(int argc, const char* argv[]) {
	Matrix input(dataInput, 2, 4);
	Matrix target(dataExpected, 1, 4);

	NeuralNetwork NN0(input, target, 4);
	NN0.train();
	NN0.test();

	std::cin.get();
	return 0;
}
