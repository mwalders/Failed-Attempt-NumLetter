#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "matrixCipher.h"

using namespace std;

class matrixNode
{
public:
	matrixNode();
	void initialize(int inputNumber, map<int, bool> inputKey, int inputXTransform, int inputYTransform, vector<int> inputTransformList, ofstream* file);
	map<int, bool> Key;
	int Number;
	ofstream* outputFile;
	vector<int> transformList;
	int Xtransform;
	int Ytransform;
	bool evaluate(int inputXtransform, int inputYtransform, int inputNumber);
	matrixNode* parent = NULL;
	vector<matrixNode> children;
	int calculateTransform(int X, int Y, int XTrans, int YTrans);
	void grow();
	void trim();

private:
	matrixCipher matrix;
};

