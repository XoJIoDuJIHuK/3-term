class Program
{
    static void Main()
    {
        string[] str = Console.ReadLine().Split(' ');
        int[,] arr = new int[str.Length, 3];
        for (int i = 0; i < str.Length; i++)
        {
            arr[i, 0] = int.Parse(str[i]);
            int j_biggest = -1;
            int value_biggest = int.MinValue;
            for (int j = 0; j < i; j++)
            {
                if (arr[j, 1] > value_biggest && arr[j, 0] < arr[i, 0])
                {
                    value_biggest = arr[j, 1];
                    j_biggest = j;
                }
            }
            if (j_biggest == -1)
            {
                arr[i, 1] = 1;
                arr[i, 2] = i;
            }
            else
            {
                arr[i, 1] = value_biggest + 1;
                arr[i, 2] = j_biggest;
            }
        }
        string resultString = "";
        int max_value = 0;
        int i_max = -1;
        for (int i = 0; i < str.Length; i++)
        {
            if (arr[i, 1] > max_value)
            {
                max_value = arr[i, 1];
                i_max = i;
            }
        }
        Console.WriteLine(max_value);
        for (int i = 0; i < str.Length; i++)
        {
            Console.Write($"{arr[i, 1]} ");
        }
        Console.WriteLine();
        while (true)
        {
            resultString = arr[i_max, 0] + " " + resultString;
            if (i_max == arr[i_max, 2]) break;
            i_max = arr[i_max, 2];
        }
        Console.WriteLine(resultString);
    }
}