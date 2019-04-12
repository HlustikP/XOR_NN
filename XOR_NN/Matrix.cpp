#include "pch.h"

Matrix::Matrix(std::vector<float> vec, short cols, short rows)
{
	mCols = cols;
	mRows = rows;

	try {
		initData(vec);
	}
	catch (const char* e) {
		std::cerr << e << std::endl;
		return;
	}
}

Matrix::Matrix()
{
}

Matrix Matrix::operator+(const Matrix& m2)
{
	const auto rows = this->mRows;
	const auto cols = this->mCols;
	if (cols != m2.mCols || rows != m2.mRows)
	{
		throw "Error on Matrix operation '+': Number of Cols or Rows don't match!";
	}

	std::vector<float> vec = {};

	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			vec.push_back(this->rawData[i][j] + m2.rawData[i][j]);
		}
	}

	Matrix m(vec, this->mCols, this->mRows);

	return m;
}

Matrix Matrix::operator+=(const Matrix& m2)
{
	if (this->mCols != m2.mCols || this->mRows != m2.mRows)
	{
		throw "Error on Matrix operation '+=': Number of Cols or Rows don't match!";
	}

	return this->operator+(m2);
}

Matrix Matrix::operator-(const Matrix& m2)
{
	const auto rows = this->mRows;
	const auto cols = this->mCols;
	if (cols != m2.mCols || rows != m2.mRows)
	{
		throw "Error on Matrix operation '-': Number of Cols or Rows don't match!";
	}

	std::vector<float> vec = {};

	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			vec.push_back(this->rawData[i][j] - m2.rawData[i][j]);
		}
	}

	Matrix m(vec, this->mCols, this->mRows);

	return m;
}

Matrix Matrix::operator-=(const Matrix& m2)
{
	if (this->mCols != m2.mCols || this->mRows != m2.mRows)
	{
		throw "Error on Matrix operation '-=': Number of Cols or Rows don't match!";
	}

	return this->operator-(m2);
}

Matrix Matrix::operator*(float multiplier)
{
	const auto rows = this->mRows;
	const auto cols = this->mCols;

	for (short i = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++)
		{
			this->rawData[i][j] *= multiplier;

		}
	}

	return *this;
}

Matrix Matrix::operator*=(float multiplier)
{
	return this->operator*(multiplier);
}

Matrix Matrix::operator*=(const Matrix& m2)
{
	return this->operator*(m2);
}

Matrix Matrix::operator*(const Matrix& m2)
{
	const auto rows = this->mRows;
	const auto cols = this->mCols;
	if (cols != m2.mRows)
	{
		throw "Error on Matrix operation '*': Number of Cols of left matrix doesnt match number of Rows of right matrix!";
	}

	std::vector<float> vec(m2.mCols * this->mRows);

	std::vector<float> leftM = {};
	std::vector<float> rightM = {};
	float product = 0.0f;

	for (short i = 0, index = 0; i < rows; i++)
	{
		leftM = this->rawData[i];

		for (short j = 0; j < m2.mCols; j++)
		{
			const auto leftMSize = leftM.size();
			rightM.resize(leftMSize);
			product = 0.0f;

			for (short k = 0; k < m2.mRows; k++)
			{
				//rightM.push_back(m2.rawData[k][j]);
				rightM[k] = m2.rawData[k][j];
			}

			for (short i = 0; i < leftMSize; i++)
			{
				product += leftM[i] * rightM[i];
			}

			vec[index] = product;
			index++;
		}
	}

	Matrix m(vec, m2.mCols, this->mRows);

	return m;
}

Matrix Matrix::operator>>(const Matrix& m2)
{
	if (this->mCols != m2.mCols || this->mRows != m2.mRows)
	{
		throw "Error on Matrix operation '>>': Number of Cols or Rows don't Match!";
	}
	std::vector<float> vec;
	const auto m1Data = this->getRawData();
	const auto m2Data = m2.rawData;
	for (short i = 0; i < m1Data.size(); i++)
	{
		for (short j = 0; j < m1Data[i].size(); j++)
		{
			vec.push_back(m1Data[i][j] * m2Data[i][j]);
		}
	}
	Matrix mat(vec, this->mCols, this->mRows);
	return mat;
}

std::vector<std::vector<float>> Matrix::getRawData()
{
	return rawData;
}

std::vector<std::vector<float>> Matrix::vectorTo2D(std::vector<float> vec, short cols, short rows)
{
	std::vector<std::vector<float> > retVector(rows, std::vector<float>(cols));

	for (short i = 0, index = 0; i < rows; i++)
	{
		for (short j = 0; j < cols; j++, index++)
		{
			retVector[i][j] = vec[index];
		}
	}

	return retVector;
}

void Matrix::print()
{
	for (short i = 0; i < mRows; i++)
	{
		for (short j = 0; j < mCols; j++)
		{
			std::cout << rawData[i][j] << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Matrix::getNumCols()
{
	return mCols;
}

int Matrix::getNumRows()
{
	return mRows;
}

float Matrix::sigmoid(float input)
{
	return 1 / (1 + exp(-input));
}

float Matrix::sigmoidDerivate(float sigmoidInput)
{
	return sigmoidInput * (1 - sigmoidInput);
}

void Matrix::applyFunction(std::function<float(float)> func)
{
	for (auto& i : rawData)
	{
		for (auto& j : i)
		{
			j = func(j);
		}
	}
}

Matrix Matrix::transposed()
{
	std::vector<float> vec(mCols * mRows);
	auto data = rawData;

	for (short i = 0; i < data.size(); i++)
	{
		for (short j = 0; j < data[i].size(); j++)
		{
			vec[i + j * (mRows)] = data[i][j];
		}
	}

	Matrix m(vec, mRows, mCols);

	return m;
}

void Matrix::transpose()
{
	std::vector<float> vec(mCols * mRows);
	auto data = rawData;

	for (short i = 0; i < data.size(); i++)
	{
		for (short j = 0; j < data[i].size(); j++)
		{
			vec[i + j * (mRows)] = data[i][j];
		}
	}

	mCols ^= mRows;
	mRows ^= mCols;
	mCols ^= mRows;
	rawData = vectorTo2D(vec, mCols, mRows);
}

void Matrix::applyFunction(std::vector<float> container, std::function<float(float)> func)
{
	for (auto i : container)
	{
		i = func(i);
	}
}

void Matrix::applyFunction(std::vector<std::vector<float>> container, std::function<float(float)> func)
{
	for (auto& i : container)
	{
		for (float j : i)
		{
			j = func(j);
		}
	}
}

void Matrix::initData(std::vector<float> raw)
{
	if ((mCols * mRows) != raw.size())
	{
		throw "Error while creating Matrix: Number of Elements doesn't match product of rows and cols!";
	}
	rawData = vectorTo2D(raw, mCols, mRows);
}