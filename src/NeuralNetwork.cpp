#include "pch.h"

NeuralNetwork::NeuralNetwork(Matrix input, Matrix target, Matrix weights0, Matrix weights1, float learningRate) :
	mInput(input), mTarget(target), mWeights0(weights0), mWeights1(weights1), mLearningRate(learningRate) {}

NeuralNetwork::NeuralNetwork(Matrix input, Matrix target, short neuronCount, float learningRate) :
	mInput(input), mTarget(target), mLearningRate(learningRate)
{
	std::vector<float> weightDistribution(neuronCount);
	std::random_device rd;
	std::default_random_engine rng(rd());

	for (short i = 0; i < neuronCount; i++)
	{
		weightDistribution[i] = 0.09 - ((0.18 / (neuronCount - 1)) * i) +
			std::uniform_real_distribution<float> (-0.001, 0.001)(rng);
	}
	std::shuffle(weightDistribution.begin(), weightDistribution.end(), rng);
	Matrix W1(weightDistribution, 1, neuronCount);

	const auto inputCols = mInput.getNumCols();
	std::vector<float> w0;

	for (short i = 0; i < inputCols; i++)
	{
		w0.insert(w0.end(), weightDistribution.begin(), weightDistribution.end());
	}
	Matrix W0(w0, neuronCount, inputCols);

	mWeights1 = std::move(W1);
	mWeights0 = std::move(W0);
}

void NeuralNetwork::train(int epochs)
{
	for (int i = 0; i < epochs; i++) {

		// Create Layer 0 (Input -> Hidden)
		layer0 = mInput * mWeights0;
		layer0.applyFunction(Matrix::sigmoid);

		// Create Layer 1 (Hidden -> Output)
		layer1 = layer0 * mWeights1;
		layer1.applyFunction(Matrix::sigmoid);

		// Calculate Delta of Layer 1
		deltaLayer1 = (mTarget - layer1);
		layer1D = layer1;
		layer1D.applyFunction(Matrix::sigmoidDerivate);
		deltaLayer1 = deltaLayer1 >> layer1D;

		// Backpropagation to Layer 0
		deltaLayer0 = deltaLayer1 * mWeights1.transposed();
		layer0D = layer0;
		layer0D.applyFunction(Matrix::sigmoidDerivate);
		deltaLayer0 = deltaLayer0 >> layer0D;

		// Apply Error to weights
		mWeights1 = mWeights1 + (layer0.transposed() * (deltaLayer1 * mLearningRate));
		mWeights0 = mWeights0 + (mInput.transposed() * (deltaLayer0 * mLearningRate));
	};
}

void NeuralNetwork::test()
{
	auto input = mInput.getRawData();
	auto output = layer1.getRawData();
	auto expectation = mTarget.getRawData();

	for (short i = 0; i < mInput.getNumRows(); i++)
	{
		for (short j = 0; j < mInput.getNumCols(); j++)
		{
			std::cout << input[i][j] << " ";
		}
		std::cout << "-> " << output[i][0] << "       Expected:" << expectation[i][0] << std::endl;
	}
}
