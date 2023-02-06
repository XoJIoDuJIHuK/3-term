#include <iostream>
using namespace std;

void hanoi(int n, int from, int to, int buffer)
{
    if (n)
    {   
        hanoi(n - 1, from, buffer, to);
        cout << "Move disk " << n << " from pin " << from << " to pin " << to << ".\n";
        hanoi(n - 1, buffer, to, from);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int k, N;
    cout << "Введите N:" << endl;
    cin >> N;
    cout << "Введите k:" << endl;
    cin >> k;
    hanoi(N, 1, k, k + 1);
    return 0;
}