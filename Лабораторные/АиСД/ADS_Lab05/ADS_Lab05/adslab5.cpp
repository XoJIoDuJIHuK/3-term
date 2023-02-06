#include <iostream>
#include <vector>
#include <list>
#define inf 2147000000
using namespace std;

const int mat[8][8] =
{
	{0, 2, inf, 8, 2, inf, inf, inf},
	{2, 0, 3, 10, 5, inf, inf, inf},
	{inf, 3, 0, inf, 12, inf, inf, 7},
	{8, 10, inf, 0, 14, 3, 1, inf},
	{2, 5, 12, 14, 0, 11, 4, 8},
	{inf, inf, inf, 3, 1, 0, 6, inf},
	{inf, inf, inf, 1, 4, 6, 0, 9},
	{inf, inf, 7, inf, 8, inf, 9, 0}
};

const int List[16][3] = {
	{1,4,7},
	{2,1,5},
	{2,1,2},
	{3,2,3},
	{3,4,6},
	{4,5,7},
	{5,2,5},
	{6,6,7},
	{7,3,8},
	{8,5,8},
	{8,1,4},
	{9,7,8},
	{10,2,4},
	{11,5,6},
	{12,3,5},
	{14,4,5}
};

bool verInTree[8];
bool edgInTree[16];

bool Contains(int mas[], int a)
{
	if (mas[0] == a || mas[1] == a) return 1;
	return 0;
}

bool Contains(vector <int> List, int a)
{
	for (int i = 0; i < List.size(); i++)
	{
		if (List[i] == a) return true;
	}
	return false;
}

void main()
{
	setlocale(LC_ALL, "ru");
	for (int i = 0; i < 8; i++) verInTree[i] = false;
	int n = 1;
	cout << "Enter 1 <= n <= 8\n";
	cin >> n;
	if (!(1 <= n <= 8))
	{
		cout << "Invalid n, начнём с первого\n";
		n = 1;
	}
	verInTree[n - 1] = true;
	for (int k = 0; k < 7; k++)
	{
		int imin = -1, jmin = -1, lmin = inf;
		for (int i = 0; i < 8; i++)
		{
			if (verInTree[i])
			{
				for (int j = 0; j < 8; j++)
				{
					if (i == j) continue;
					if (!verInTree[j] && mat[i][j] < lmin)
					{
						imin = i;
						jmin = j;
						lmin = mat[i][j];
					}
				}
			}
		}
		if (imin != -1 && jmin != -1 && lmin != inf)
		{
			verInTree[jmin] = true;
			printf("Ребро V%d-V%d\n", imin + 1, jmin + 1);
		}
	}

	cout << "\ncrascal\n\n";
	//Алгоритм Краскала

	/*for (int i = 0; i < 8; i++) verInTree[i] = false;
	int n = 1;
	cout << "Enter 1 <= n <= 16\n";
	cin >> n;
	if (!(1 <= n <= 16))
	{
		cout << "Invalid n, начнём с первого\n";
		n = 1;
	}
	edgInTree[n - 1] = true;
	verInTree[list[n - 1][1] - 1] = true;
	verInTree[list[n - 1][2] - 1] = true;
	printf("Ребро между V%d и V%d\n", list[n - 1][1], list[n - 1][2]);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			list[j][1] - 1;
			list[j][2] - 1;
			if (edgInTree[j]) continue;
			if (verInTree[list[j][1] - 1] && !verInTree[list[j][2] - 1] || \
				!verInTree[list[j][1] - 1] && verInTree[list[j][2] - 1])
			{
				edgInTree[j] = true;
				verInTree[list[j][1] - 1] = true;
				verInTree[list[j][2] - 1] = true;
				printf("Ребро между V%d и V%d\n", list[j][1], list[j][2]);
			}
		}
	}*/
	list <pair <int, int>> set[4];
	vector <int> listOfVertexes[4];
	//int set[4][8][2];
	bool pointedEdge[16];
	bool pointedVer[8];
	for (int i = 0; i < 16; i++) pointedEdge[i] = false;
	for (int i = 0; i < 8; i++) pointedVer[i] = false;
	/*pointedEdge[0] = true;
	pointedVer[3] = true;
	pointedVer[6] = true;
	listOfVertexes[0].push_back(4);
	listOfVertexes[0].push_back(7);
	cout << "4-7\n";*/
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (pointedEdge[j]) continue;
			int numOfSetOfFirst = -1;
			int numOfSetOfSecond = -1;
			for (int k = 0; k < 4; k++)
			{
				if (numOfSetOfFirst != -1 && numOfSetOfSecond != -1) break;
				for (int l = 0; l < listOfVertexes[k].size(); l++)
				{
					if (Contains(listOfVertexes[k], List[j][1]))
					{
						numOfSetOfFirst = k;
					}
					if (Contains(listOfVertexes[k], List[j][2]))
					{
						numOfSetOfSecond = k;
					}
				}
			}
			if (numOfSetOfFirst == numOfSetOfSecond && numOfSetOfFirst != -1 && numOfSetOfSecond != -1) continue;
			else if (numOfSetOfFirst != -1 && numOfSetOfSecond != -1)
			{
				for (int k = 0; k < listOfVertexes[numOfSetOfSecond].size(); k++)
				{
					listOfVertexes[numOfSetOfFirst].push_back(listOfVertexes[numOfSetOfSecond][k]);
				}
				listOfVertexes[numOfSetOfSecond].clear();
				pointedEdge[j] = true;
			}
			else if (numOfSetOfFirst == -1 && numOfSetOfSecond != -1)
			{
				listOfVertexes[numOfSetOfSecond].push_back(List[j][1]);
				pointedEdge[i] = true;
			}
			else if (numOfSetOfFirst != -1 && numOfSetOfSecond == -1)
			{
				listOfVertexes[numOfSetOfFirst].push_back(List[j][2]);
				pointedEdge[i] = true;
			}
			else if (numOfSetOfFirst == -1 && numOfSetOfSecond == -1)
			{
				for (int k = 0; k < 4; k++)
				{
					if (listOfVertexes[k].size() == 0)
					{
						listOfVertexes[k].push_back(List[j][1]);
						listOfVertexes[k].push_back(List[j][2]);
						pointedEdge[j] = true;
						break;
					}
				}
			}
			pointedVer[List[j][1] - 1] = true;
			pointedVer[List[j][2] - 1] = true;
			cout << List[j][1] << '-' << List[j][2] << endl;
			break;
		}
	}
}