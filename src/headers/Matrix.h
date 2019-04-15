#pragma once
#include "pch.h"

class Matrix
{
public:
	Matrix(std::vector<float> vec, short cols, short rows);
	Matrix(); // DO NOT USE

	Matrix operator+(const Matrix& m2);
	Matrix operator+=(const Matrix& m2);
	Matrix operator-(const Matrix& m2);
	Matrix operator-=(const Matrix& m2);
	Matrix operator*(float multiplier);
	Matrix operator*=(float multiplier);
	Matrix operator*=(const Matrix& m2);
	Matrix operator*(const Matrix& m2);
	Matrix operator>>(const Matrix& m2);

	std::vector<std::vector<float>> getRawData();
	std::vector<std::vector<float>> vectorTo2D(std::vector<float> vec, short cols, short rows);
	void print();
	int getNumCols();
	int getNumRows();
	void applyFunction(std::function<float(float)> func);
	Matrix transposed();
	void transpose();

	static float sigmoid(float input);
	static float sigmoidDerivate(float input);
	static void applyFunction(std::vector<float> container, std::function<float(float)> func);
	static void applyFunction(std::vector<std::vector<float>> container, std::function<float(float)> func);
private:
	void initData(std::vector<float> raw);

	short mCols;
	short mRows;
	std::vector<std::vector<float>> rawData;
};