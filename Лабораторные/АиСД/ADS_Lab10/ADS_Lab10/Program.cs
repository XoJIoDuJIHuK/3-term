class Program
{
    static double[,,] matrix;
    static double ETA = 100;    // величина, на котрую нужно делить расстояние между городами в формуле желания
    static double Q = 100;      // величина феромона, выделяемого одни муравьём за один проход
    static double p = 0.8;      // какая часть феромона останется на дорожке после одной итерации
    public struct Way
    {
        public List<int> list;
        public double length = 0;
        public Way()
        {
            list = new();
            length = 0;
        }
        public Way(int index)
        {
            list = new() { index };
            length = 0;
        }
        public void Add(int index)
        {
            if (!list.Contains(index))
            {
                if (list.Count != 0) length += matrix[list.Count - 1, index, 0];
                list.Add(index);
            }
            else
            {
                Console.WriteLine("This city already is in way");
            }
        }
        public override string ToString()
        {
            string str = "";
            foreach (var c in list)
            {
                str += $"{c} ";
            }
            str += $"{length}";
            return str;
        }
    }
    static int Factorial(int num)
    {
        if (num == 0) return 1;
        else return (num * Factorial(num - 1));
    }
    static double GetDistance(int i, int j, int[,,] matrix)
    {
        return matrix[i, j, 0];
    }
    static void Main()
    {
        var random = new Random();

        Console.Write("Enter number of cities: ");
        //int numOfCities = 10;
        int numOfCities = int.Parse(Console.ReadLine());
        int antsCount = numOfCities;
        Console.Write("Enter alpha: ");
        //int alpha = 1;
        int alpha = int.Parse(Console.ReadLine());
        Console.Write("Enter beta: ");
        //int beta = 1;
        int beta = int.Parse(Console.ReadLine());
        Console.Write("Enter count of iterations: ");
        //int iterCount = 100;
        int iterCount = int.Parse(Console.ReadLine());

        int[,] citiesCoordinates = new int[numOfCities, 2];
        bool Contains(int x, int y)
        {
            for (int i = 0; i < numOfCities; i++)
            {
                if (x == citiesCoordinates[i, 0] && y == citiesCoordinates[i, 1]) return true;
            }
            return false;
        }
        for (int i = 0; i < numOfCities; i++)
        {
            int Ox = random.Next(1, 1000);
            int Oy = random.Next(1, 1000);
            while (Contains(Ox, Oy))
            {
                Ox = random.Next(1, 1000);
                Oy = random.Next(1, 1000);
            }
            citiesCoordinates[i, 0] = Ox;
            citiesCoordinates[i, 1] = Oy;
        }
        matrix = new double[numOfCities, numOfCities, 2];//i, j - номера городов, z = 0 - расстояние
                                                         //z = 1 - количество феромона
        for (int i = 0; i < numOfCities - 1; i++)//заполнение матрицы расстояниями и феромонами
        {
            for (int j = i + 1; j < numOfCities; j++)
            {
                matrix[i, j, 0] = Math.Sqrt(Math.Pow(citiesCoordinates[i, 0] - citiesCoordinates[j, 0], 2) +
                    Math.Pow(citiesCoordinates[i, 1] - citiesCoordinates[j, 1], 2));
                matrix[j, i, 0] = matrix[i, j, 0];

                //Console.Write($"Enter amount of feromone between cities {i} and {j}: ");
                //matrix[i, j, 1] = double.Parse(Console.ReadLine());
                matrix[i, j, 1] = random.NextDouble();
                matrix[j, i, 1] = matrix[i, j, 1];
            }
        }

        int NextCity(List<int> visited)
        {
            int currentIndex = visited[visited.Count - 1];
            double denominator = 0;
            for (int m = 0; m < numOfCities; m++)
            {
                if (!visited.Contains(m)) denominator += Math.Pow(matrix[currentIndex, m, 1], alpha) * 
                        Math.Pow(ETA / matrix[currentIndex, m, 0], beta);
            }
            double P(int i, int j)//желание перейти из i-го в j-й город
            {
                return Math.Pow(matrix[i, j, 1], alpha) * Math.Pow(ETA / matrix[i, j, 0], beta)  / denominator;
            }

            List<int> unvisitedIndexes = new();
            List<double> wishes = new();
            for (int i = 0; i < numOfCities; i++)
            {
                if (!visited.Contains(i))
                {
                    wishes.Add(P(currentIndex, i));
                    unvisitedIndexes.Add(i);
                }
            }

            var random = new Random();
            double randValue = random.NextDouble();
            int index = 0;
            while (randValue - wishes[index] > 0)
            {
                randValue -= wishes[index];
                index++;
            }
            return unvisitedIndexes[index];
        }

        Way bestWay = new()
        {
            length = double.MaxValue
        };
        for (int i = 0; i < iterCount; i++)// начало итераций
        {
            List<Way> listOfWays = new();
            for (int j = 0; j < antsCount; j++)
            {
                int currentIndex = j;
                List<int> visited = new() { currentIndex };
                Way way = new();
                way.Add(currentIndex);
                while (visited.Count < numOfCities)
                {
                    currentIndex = NextCity(visited);
                    way.Add(currentIndex);
                    visited.Add(currentIndex);
                }
                for (int k = 0; k < numOfCities - 1; k++)
                {           //i             //j
                    matrix[way.list[k], way.list[k + 1], 1] += Q / matrix[way.list[k], way.list[k + 1], 0];
                    matrix[way.list[k + 1], way.list[k], 1] += Q / matrix[way.list[k + 1], way.list[k], 0];
                }
                listOfWays.Add(way);
            }
            for (int i1 = 0; i1 < numOfCities; i1++)
            {
                for (int j1 = 0; j1 < numOfCities; j1++)
                {
                    matrix[i1, j1, 1] *= p;
                }
            }
            Way FindMin()
            {
                Way ret = bestWay;
                for (int i = 0; i < listOfWays.Count; i++)
                {
                    if (listOfWays[i].length < ret.length) ret = listOfWays[i];
                }
                return ret;
            }
            bestWay = FindMin();
            Console.WriteLine($"Best way on iteration {i}: {bestWay}");
        }
    }
}