#include <iostream>
#define Inf 2147000000
using namespace std;

int D[6][6] = {
    { 0, 28, 21, 59, 12, 27 },
    { 7, 0, 24, Inf, 21, 9 },
    { 9, 32, 0, 13, 11, Inf },
    { 8, Inf, 5, 0, 16, Inf },
    { 14, 13, 15, 10, 0, 22 },
    { 15, 18, Inf, Inf, 6, 0 }
};
int S[6][6] = {
    { 0, 2, 3, 4, 5, 6 },
    { 1, 0, 3, 4, 5, 6 },
    { 1, 2, 0, 4, 5, 6 },
    { 1, 2, 3, 0, 5, 6 },
    { 1, 2, 3, 4, 0, 6 },
    { 1, 2, 3, 4, 5, 0 }
};

int min(int a, int b)
{
    if (a <= b) return a;
    else return b;
}

int main()
{
    for (int m = 0; m < 6; m++)
    {
        for (int i = 0; i < 6; i++)
        {
            if (i == m) continue;
            for (int j = 0; j < 6; j++)
            {
                if (j == m || i == j) continue;
                if (D[i][m] == Inf || D[m][j] == Inf) continue;
                else if (D[i][m] + D[m][j] < D[i][j])
                {
                    D[i][j] = D[i][m] + D[m][j];
                    S[i][j] = m + 1;
                }
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int num = D[i][j];
            if (num < 10) cout << num << "   ";
            else if (num != Inf) cout << num << "  ";
            else cout << "Inf ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << S[i][j] << " ";
        }
        cout << endl;
    }
}