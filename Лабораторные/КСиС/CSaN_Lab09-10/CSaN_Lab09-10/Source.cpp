#include <iostream>
using namespace std;
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <conio.h>
#include <Ws2tcpip.h>
#pragma comment(lib , "iphlpapi.lib")
#pragma comment(lib , "ws2_32.lib")
void GetMacAddress(unsigned char*, struct in_addr);
int main()
{
	setlocale(LC_ALL, "RUS");
	unsigned char mac[6];
	struct in_addr srcip = { 0 };
	struct sockaddr_in sa;
	char ip_address[32];
	WSADATA firstsock;
	unsigned char mac_in[6];
	unsigned char ip_out[4];
	if (WSAStartup(MAKEWORD(2, 2), &firstsock) != 0)
	{
		cout << "ќшибка инициализации winsock";
		cout << WSAGetLastError();
		return -1;
	}
	cout << "¬ведите IP : ";
	cin >> ip_address;
	//преобразование IP адреса другим способом
	//srcip.s_addr = inet_addr(ip_address);
	inet_pton(AF_INET, ip_address, &(sa.sin_addr));
	//ѕолучение MAC по IP
	GetMacAddress(mac, sa.sin_addr);
	//GetMacAddress(mac, srcip);
	printf("MAC адрес : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	printf("\n");

	cout << "¬ведите физический адрес побайтно: ";
	for (int i = 0; i < 6; i++)
	{
		int a;
		cin >> a;
		mac_in[i] = a;
	}
	MIB_IPNETTABLE* pIpNetTable = (MIB_IPNETTABLE*) new char[0xffff];
	ULONG cbIpNetTable = 0xFFFF;
	if (NO_ERROR ==
		GetIpNetTable(pIpNetTable, &cbIpNetTable, true))
	{
		for (DWORD i = 0; i < pIpNetTable->dwNumEntries; i++)
		{
			//если адрес в поле dwAddr совпадает с искомым ip
			//и dwType отличен от 2.
			//значение 2 соответсвует недоступной или
			//незаконченной ARP записи
			if (pIpNetTable->table[i].dwAddr == 0xc82ba8c0)
			{
				for (int j = 0; j < 6; j++)
				{
					cout << pIpNetTable->table[i].bPhysAddr[j] << '-';
				}
				cout << endl;
			}
			bool macFound = true;
			for (int j = 0; j < 6 && macFound; j++) if (pIpNetTable->table[i].bPhysAddr[j] != mac_in[j]) macFound = false;
			if (macFound)
			{
				cout << hex << (int)pIpNetTable->table[i].bPhysAddr << endl;
				int ip = pIpNetTable->table[i].dwAddr;
				cout << "IP: " << ip % 0x100 << '.' << (ip / 0x100) % 0x100 << '.' <<
					(ip / 0x10000) % 0x100 << '.' << ip / 0x1000000;
				cout << endl << hex << ip << endl;
				delete[] pIpNetTable;
				//192.168.1.12
				//12.1.168.192
				//0c01a8c0
			}
		}
	}

	return 0;
}
void GetMacAddress(unsigned char* mac, struct in_addr
	destip)
{
	DWORD ret;
	IPAddr srcip;
	ULONG MacAddr[2];
	ULONG PhyAddrLen = 6;
	int i;
	srcip = 0;
	//ѕослать ARP пакет
	ret = SendARP((IPAddr)destip.S_un.S_addr,
		srcip, MacAddr, &PhyAddrLen);
	//ѕреобразовать адрес
	if (PhyAddrLen)
	{
		BYTE* bMacAddr = (BYTE*)&MacAddr;
		for (i = 0; i < (int)PhyAddrLen; i++)
		{
			mac[i] = (char)bMacAddr[i];
		}
	}
}