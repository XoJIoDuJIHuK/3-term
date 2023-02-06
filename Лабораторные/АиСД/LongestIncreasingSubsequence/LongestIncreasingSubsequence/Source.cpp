#include <iostream>
#include <climits>
using namespace std;

// Функция для нахождения длины самой длинной возрастающей подпоследовательности
int LIS(int arr[], int i, int n, int prev)
{
    // Базовый случай: ничего не осталось
    if (i == n) {
        return 0;
    }

    // случай 1: исключить текущий элемент и обработать
    // оставшиеся элементы
    int excl = LIS(arr, i + 1, n, prev);

    // случай 2: включить текущий элемент, если он больше
    // чем предыдущий элемент в LIS
    int incl = 0;
    if (arr[i] > prev) {
        incl = 1 + LIS(arr, i + 1, n, arr[i]);
    }

    // вернуть максимум из двух вышеперечисленных вариантов
    return max(incl, excl);
}

int main()
{
    int arr[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "The length of the LIS is " << LIS(arr, 0, n, INT_MIN);

    return 0;
}