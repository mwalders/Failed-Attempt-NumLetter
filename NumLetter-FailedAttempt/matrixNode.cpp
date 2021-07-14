#include "matrixNode.h"

matrixNode::matrixNode()
{
    for (int i = 0; i < matrix.rows * matrix.columns; i++)
    {
        Key[i] = false;
    }
}

void matrixNode::initialize(int inputNumber, map<int, bool> inputKey, int inputXTransform, int inputYTransform, vector<int> inputTransformList, ofstream* file)
{
    Number = inputNumber;
    outputFile = file;
    Xtransform = inputXTransform;
    Ytransform = inputYTransform;

    for (int i = 0; i < matrix.rows * matrix.columns; i++)
    {
        Key[i] = inputKey[i];
    }

    for (auto list_it = inputTransformList.begin(); list_it != inputTransformList.end(); list_it++)
    {
        transformList.push_back(*list_it);
    }
    transformList.push_back(inputXTransform);
    transformList.push_back(inputYTransform);

    vector<vector<int>>::iterator it, end;

    switch (inputNumber)
    {
    case 0:
        it = matrix.Zeroes.begin();
        end = matrix.Zeroes.end();
        break;
    case 1:
        it = matrix.Ones.begin();
        end = matrix.Ones.end();
        break;
    case 2:
        it = matrix.Twos.begin();
        end = matrix.Twos.end();
        break;
    case 3:
        it = matrix.Threes.begin();
        end = matrix.Threes.end();
        break;
    case 4:
        it = matrix.Fours.begin();
        end = matrix.Fours.end();
        break;
    }

    for (; it < end; it++)
    {
        Key[calculateTransform(it->front(), it->back(), inputXTransform, inputYTransform)] = true;
    }
}

bool matrixNode::evaluate(int inputXtransform, int inputYtransform, int inputNumber)
{
    vector<vector<int>>::iterator it, end;

    switch (inputNumber)
    {
    case 0:
        it = matrix.Zeroes.begin();
        end = matrix.Zeroes.end();
        break;
    case 1:
        it = matrix.Ones.begin();
        end = matrix.Ones.end();
        break;
    case 2:
        it = matrix.Twos.begin();
        end = matrix.Twos.end();
        break;
    case 3:
        it = matrix.Threes.begin();
        end = matrix.Threes.end();
        break;
    case 4:
        it = matrix.Fours.begin();
        end = matrix.Fours.end();
        break;
    }

    bool result = true;
    int front, back, transform;
    bool keyResult;
    for (; it != end; it++)
    {
        front = it->front();
        back = it->back();
        transform = calculateTransform(front, back, inputXtransform, inputYtransform);
        keyResult = Key[transform];

        if (Key[calculateTransform(it->front(), it->back(), inputXtransform, inputYtransform)])
        {
            result = false;
            break;
        }
    }

    return result;
}

int matrixNode::calculateTransform(int X, int Y, int XTrans, int YTrans)
{
    if (XTrans < 0)
    {
        X = matrix.rows - X;
        X = (X - XTrans) % matrix.rows;
        X = matrix.rows - X;
    }
    else if (XTrans == matrix.rows)
    {
        X = matrix.rows - X;
    }
    else
    {
        X = (X + XTrans) % matrix.rows;
    }

    if (YTrans < 0)
    {
        Y = matrix.columns - Y;
        Y = (Y - YTrans) % matrix.columns;
        Y = matrix.columns - Y;
    }
    else if (YTrans == matrix.columns)
    {
        Y = matrix.columns - Y;
    }
    else
    {
        Y = (Y + YTrans) % matrix.columns;
    }

    return matrix.Coords2Num[{X, Y}];
}

void matrixNode::grow()
{
    matrixNode* tempNode;

    for (int i = 0; i <= matrix.rows; i++)
    {
        for (int j = 0; j <= matrix.columns; j++)
        {
            if (evaluate(i, j, Number + 1))
            {
                if ((Number + 1) >= 4)
                {
                    if ((transformList[0] != transformList[2]) || (transformList[0] != transformList[4]) || (transformList[0] != transformList[6]) || (transformList[0] != Xtransform))
                    {
                        if ((transformList[1] != transformList[3]) || (transformList[1] != transformList[5]) || (transformList[1] != transformList[7]) || (transformList[1] != Ytransform))
                        {
                            if (outputFile->is_open())
                            {
                                for (auto it = transformList.begin(); it != transformList.end(); it++)
                                {
                                    *outputFile << *it << '\t';
                                    cout << *it << ", ";
                                }
                                *outputFile << Xtransform << '\t' << Ytransform << '\n';
                                cout << Xtransform << ", " << Ytransform << endl;
                            }
                        }
                    }
                }
                else
                {
                    tempNode = new matrixNode;
                    tempNode->initialize(Number + 1, Key, i, j, transformList, outputFile);
                    children.push_back(*tempNode);
                }
            }
        }
    }
}

void matrixNode::trim()
{
    if (!children.empty())
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            if (!children.empty())
            {
                break;
            }
            if (it->children.empty())
            {
                it = children.erase(it);
            }

        }
    }
}
