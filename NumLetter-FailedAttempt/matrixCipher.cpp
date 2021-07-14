#include "matrixCipher.h"

matrixCipher::matrixCipher()
{
	int location = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Coords2Num[{i, j}] = location;
			location++;
			
			switch (cipherIntegers[i][j])
			{
			case 0:
				Zeroes.push_back({ i,j });
				break;
			case 1:
				Ones.push_back({ i,j });
				break;
			case 2:
				Twos.push_back({ i,j });
				break;
			case 3:
				Threes.push_back({ i,j });
				break;
			case 4:
				Fours.push_back({ i,j });
				break;
			}
		}
	}

}
