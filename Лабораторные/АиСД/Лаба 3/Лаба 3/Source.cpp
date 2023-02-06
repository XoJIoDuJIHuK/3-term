#include <iostream>
#define Inf 2147483647
using namespace std;

int matSme[9][9] = {
	{ 0, 7, 10,0, 0, 0, 0, 0, 0 },
	{ 7, 0, 0, 0, 0, 9, 27,0, 0 },
	{ 10,0, 0, 0, 31,8, 0, 0, 0 },
	{ 0, 0, 0, 0, 32,0, 0, 17,21},
	{ 0, 0, 31,32,0, 0, 0, 0, 0 },
	{ 0, 9, 8, 0, 0, 0, 0, 11,0 },
	{ 0, 27,0, 0, 0, 0, 0, 0, 15},
	{ 0, 0, 0, 17,0, 11,0, 0, 15},
	{ 0, 0, 0, 21,0, 0, 15,15,0 }
};
int matDij[9][9];
bool pointed[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int numOfPointed = 0;
int lastPointed = -1;

void main()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			matDij[i][j] = Inf;
		}
	}
	int start;
	cout << "enter start vertex ";
	cin >> start;
	for (int i = 0; i < 9; i++) matDij[i][start - 1] = 0;
	pointed[start - 1] = true;
	numOfPointed++;
	lastPointed = start - 1;
	for (int i = 1; numOfPointed < 9; i++)
	{
		//cout << "last pointed " << lastPointed + 1 << endl;
		int smallestValue = Inf;
		int smallestIndex = -1;
		for (int j = 0; j < 9; j++)
		{
			if (pointed[j] || matSme[lastPointed][j] == 0) continue;
			int newValue = matSme[lastPointed][j] + matDij[8][lastPointed];
			if (matDij[i - 1][j] > newValue) 
				for (int k = i; k < 9; k++)
				{
					matDij[k][j] = newValue;
				}
		}
		for (int j = 0; j < 9; j++)
		{
			if (pointed[j]) continue;
			if (matDij[i][j] < smallestValue)
			{
				smallestValue = matDij[i][j];
				smallestIndex = j;
			}
		}
		/*cout << "mas of pointed on step " << i << ": ";
		for (int j = 0; j < 9; j++)
		{
			if (pointed[j]) cout << j + 1 << " ";
			else cout << 0 << " ";
		}*/
		//cout << endl;
		pointed[smallestIndex] = true;
		numOfPointed++;
		lastPointed = smallestIndex;
		for (int k = i; k < 9; k++) matDij[k][smallestIndex] = smallestValue;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (matDij[i][j] == Inf) cout << "In  ";
			else cout << matDij[i][j] << " ";
			if (matDij[i][j] < 100) cout << " ";
			if (matDij[i][j] < 10) cout << " ";
		}
		cout << endl;
	}
}