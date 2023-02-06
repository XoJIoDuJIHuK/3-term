class Cities
{
    public struct Way
    {
        public List<City> list;
        public double length = 0;
        public Way()
        {
            list = new();
            length = 0;
        }
        public Way(City city)
        {
            list = new() { city };
            length = 0;
        }
        public void Add(City city)
        {
            if (!list.Contains(city))
            {
                if (list.Count != 0) length += GetDistance(list[list.Count - 1], city);
                list.Add(city);
            }
            else
            {
                Console.WriteLine("This city already is in way");
            }
        }
        public void Insert(int index, City city)
        {
            list.Insert(index, city);
            if (index > 0)
            {
                length += GetDistance(list[index - 1], city);
            }
            if (index < list.Count - 1)
            {
                length += GetDistance(list[index + 1], city);
            }
        }
        public static Way Append(Way a, Way b)
        {
            Way c = new();
            foreach (var city in a.list)
            {
                c.list.Add(city);
            }
            foreach (var city in b.list)
            {
                c.list.Add(city);
            }
            c.length = a.length + b.length + GetDistance(a.list[a.list.Count - 1], b.list[0]);
            return c;
        }
        public override string ToString()
        {
            string str = "";
            foreach (var c in list)
            {
                str += $"{c} ";
            }
            return str;
        }
    }
    private const int MAXX = 187;
    private const int MAXY = 187;
    public List<City> allCities = new();
    public double minimalPathLength = double.MaxValue;
    static int Factorial(int num)
    {
        if (num == 0) return 1;
        else return (num * Factorial(num - 1));
    }
    static double GetDistance(City a, City b)
    {
        return Math.Sqrt(Math.Pow(a.Ox - b.Ox, 2) + Math.Pow(a.Oy - b.Oy, 2));
    }
    public void AddCity(int x, int y)
    {
        foreach (var c in allCities)
        {
            if (c.Ox == x && c.Oy == y)
            {
                Console.WriteLine("City already exists on these coordinates");
                return;
            }
        }
        allCities.Add(new City(x, y));
    }
    public void RemoveCity(int x, int y)
    {
        if (allCities.Count <= 8)
        {
            Console.WriteLine("There must be at least 8 cities, gtfo");
            return;
        }
        foreach (var c in allCities)
        {
            if (c.Ox == x && c.Oy == y)
            {
                allCities.Remove(c);
                return;
            }
        }
    }
    public void PrintGraph()
    {
        for (int x = 0; x < MAXX; x++)
        {
            for (int y = 0; y < MAXY; y++)
            {
                bool cityExists = false;
                foreach (var c in allCities)
                {
                    if (c.Ox == x && c.Oy == y)
                    {
                        Console.Write('*');
                        cityExists = true;
                        break;
                    }
                }
                if (!cityExists)
                {
                    Console.Write(' ');
                }
            }
            Console.WriteLine();
        }
    }
    public List<Way> GetPopulation(int startIndex, List<int> visitedCities)
    {
        List<Way> list = new();
        visitedCities.Add(startIndex);
        if (visitedCities.Count == allCities.Count)
            list.Add(new Way(allCities[startIndex]));
        else
        {
            for (int i = 0; i < allCities.Count; i++)
            {
                if (!visitedCities.Contains(i))
                {
                    List<Way> citiesLocal = GetPopulation(i, new List<int>(visitedCities));
                    foreach (var c in citiesLocal)
                    {
                        c.Insert(0, allCities[startIndex]);
                        list.Add(c);
                    }
                }
            }
        }
        if (startIndex == 0)
        {
            int finalPopulationCount = allCities.Count + 2;
            List<int> markedChromosomes = new();
            for (int i = 0; i < finalPopulationCount; i++)
            {
                Random rand = new();
                int index = rand.Next(0, list.Count);
                while (true)
                {
                    if (!markedChromosomes.Contains(index)) break;
                    index = rand.Next(0, list.Count);
                }
                markedChromosomes.Add(index);
            }
            List<Way> finalPopulation = new();
            foreach (var c in markedChromosomes) finalPopulation.Add(list[c]);
            return finalPopulation;
        }
        return list;
    }
    public static void WriteListOfCities(List<Way> list)
    {
        foreach (var l in list)
        {
            Console.Write($"{l} length: {l.length}\n");
        }
    }
    public static Way Fill(Way p1, Way p2, int tearPoint, int wayLength)
    {
        Way child = new();
        for (int k = 0; k < tearPoint; k++)
        {
            child.Add(p1.list[k]);
        }
        for (int k = tearPoint; k < wayLength; k++)
        {
            if (child.list.Contains(p2.list[k])) continue;
            child.Add(p2.list[k]);
        }
        for (int i = tearPoint; child.list.Count < wayLength; i++)
        {
            if (!child.list.Contains(p1.list[i])) child.Add(p1.list[i]);
        }
        return child;
    }
    public static void Intersect(List<Way> population)
    {
        int startCount = population.Count;
        int tearPoint = 4;
        for (int i = 0; i < startCount - 1; i++)
        {
            for (int j = i + 1; j < startCount; j++)
            {
                Console.WriteLine($"\nParent {i}: {population[i]} {population[i].length}");
                Console.WriteLine($"Parent {j}: {population[j]} {population[j].length}");
                Way son1 = Fill(population[i], population[j], tearPoint, population[0].list.Count);
                Way son2 = Fill(population[j], population[i], tearPoint, population[0].list.Count);
                Console.WriteLine($"Son 1: {son1} {son1.length}");
                Console.WriteLine($"Son 2: {son2} {son2.length}\n");
                population.Add(son1);
                population.Add(son2);
            }
        }
        int newCount = population.Count;
        for (int i = 0; i < newCount - startCount; i++)
        {
            int indexMax = -1;
            double maxValue = double.MinValue;
            for (int j = 0; j < population.Count; j++)
            {
                if (population[j].length > maxValue)
                {
                    indexMax = j;
                    maxValue = population[j].length;
                }
            }
            if (indexMax == -1) Console.WriteLine("indexMax == -1 wtf");
            else
            {
                population.RemoveAt(indexMax);
            }
        }
        WriteListOfCities(population);
    }
    public static Way FindMin(List<Way> population)
    {
        Way ret = population[0];
        for (int i = 1; i < population.Count; i++)
        {
            if (population[i].length < ret.length)
            {
                ret = population[i];
            }
        }
        return ret;
    }
}
