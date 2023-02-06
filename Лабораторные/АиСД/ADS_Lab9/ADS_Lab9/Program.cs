class Program
{
    static void f(List<int> list)
    {
        list[2] = 1;
    }
    static void Main()
    {
        int evolutionsAmount = 10;
        Console.Write("Enter evolutions amount: ");//для быстрого показа комментить это
        evolutionsAmount = int.Parse(Console.ReadLine());

        Cities cities = new();
        Console.WriteLine("Enter Ox Oy of cities, end to break");

        string input = "";
        while (true)//для быстрого показа комментить это
        {
            input = Console.ReadLine();
            if (input == "end" && cities.allCities.Count >= 8) break;
            string[] arrParm = input.Split(' ');
            if (arrParm.Length != 2) Console.WriteLine("Invalid input");
            cities.AddCity(int.Parse(arrParm[0]), int.Parse(arrParm[1]));
        }
        //for (int i = 1; i < 9; i++) cities.AddCity(i, i); //и раскомментить это
        var population = cities.GetPopulation(0, new List<int> { });
        Cities.WriteListOfCities(population);
        for (int i = 0; i < evolutionsAmount; i++)
        {
            Cities.Intersect(population);
        }
        var best = Cities.FindMin(population);
        Console.WriteLine($"\nBest way: {best} {best.length}");

    }
}