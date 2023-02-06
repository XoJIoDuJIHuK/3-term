class Program
{
    static int Max(int a, int b)
    {
        if (a >= b) return a;
        return b;
    }
    static void Main()
    {
        Console.Write("Weight: ");
        int W = Convert.ToInt32(Console.ReadLine());
        Console.Write("N: ");
        int N = Convert.ToInt32(Console.ReadLine());
        string[] str;
        string[] names = new string[N];
        int[,] values = new int[N, 2];
        int[,] matrix = new int[N + 1, W + 1];
        for (int i = 0; i < N; i++)
        {
            str = Console.ReadLine().Split(' ');
            names[i] = str[0];
            values[i, 0] = Convert.ToInt32(str[1]);//вес
            values[i, 1] = Convert.ToInt32(str[2]);//стоимость
        }
        for (int i = 1; i < N + 1; i++)
        {
            for (int j = 0; j < W + 1; j++)
            {
                matrix[i, j] = matrix[i - 1, j];
                if (values[i - 1, 0] <= j) matrix[i, j] = Max(matrix[i, j], matrix[i - 1, j - values[i - 1, 0]]
                    + values[i - 1, 1]);
            }
        }
        for (int i = 0; i < N + 1; i++)
        {
            for (int j = 0; j < W + 1; j++)
            {
                if (matrix[i, j] <= 9) Console.Write(' ');
                Console.Write(' ');
                Console.Write(matrix[i, j]);
            }
            Console.WriteLine();
        }
        int i_max = N;
        int j_max = W;
        while (i_max > 0)
        {
            if (matrix[i_max, j_max] == matrix[i_max - 1, j_max]) i_max--;
            else
            {
                Console.WriteLine(names[i_max - 1]);
                j_max -= values[i_max - 1, 0];
            }
        }
    }
}