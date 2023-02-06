#include <iostream>
#pragma comment (lib, "..\\Debug\\Asm01a.lib")

extern "C"
{
	__int32 __stdcall getmin(__int32* arrPtr, unsigned int length);
	__int32 __stdcall getmax(__int32* arrPtr, unsigned int length);
};

int main()
{
	const unsigned __int32 ARR_SIZE = 10;
	__int32 arr[ARR_SIZE] = { -2, 5, 3, 21, 4, -4, 2, -8, 7, 1 };
	_int32 min = getmin(arr, ARR_SIZE);
	_int32 max = getmax(arr, ARR_SIZE);
	std::cout << getmax(arr, ARR_SIZE) + getmin(arr, ARR_SIZE) << "\n";

	return 0;
}