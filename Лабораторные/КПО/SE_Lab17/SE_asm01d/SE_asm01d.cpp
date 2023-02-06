extern "C"
{
	int getmin(int* array, int length)
	{
		int ret = array[0];
		for (int i = 1; i < length; i++)
		{
			if (array[i] < ret)
			{
				ret = array[i];
			}
		}
		return ret;
	}
	int getmax(int* array, int length)
	{
		int ret = array[0];
		for (int i = 1; i < length; i++)
		{
			if (array[i] > ret)
			{
				ret = array[i];
			}
		}
		return ret;
	}
}