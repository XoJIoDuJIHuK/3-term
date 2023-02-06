class City
{
    public int Ox;
    public int Oy;
    public City()
    {
        Ox = 0;
        Oy = 0;
    }
    public City(int ox, int oy)
    {
        Ox = ox;
        Oy = oy;
    }
    public override string ToString()
    {
        return $"{Ox};{Oy}";
    }
}
