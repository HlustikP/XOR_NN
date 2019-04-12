#pragma once
#include "pch.h"

class NeuralNetwork
{
public:
	NeuralNetwork(Matrix input, Matrix target, Matrix weights0, Matrix weights1, float learningRate = 1.0);
	NeuralNetwork(Matrix input, Matrix target, short neuronCount = 4, float learningRate = 1.0);
	void train(int epochs = 10000);
	void test();
private:
	Matrix mInput;
	Matrix mTarget;
	Matrix mWeights0;
	Matrix mWeights1;
	float mLearningRate;

	Matrix layer0;
	Matrix layer1;
	Matrix deltaLayer0;
	Matrix deltaLayer1;
	Matrix layer0D;
	Matrix layer1D;
};
