#include <map>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>


using namespace std;

const int BLOCK_SIZE = 1024;

static char *maxAddrPtr = NULL;

void MallocMemory(int size)
{
	std::map<int, char*> memoryMap;

	char *p = NULL;
	for (int i = 0; i < size; ++i)
	{
		p = new char[BLOCK_SIZE];
		char v = rand() % 128;
		memset(p, v, BLOCK_SIZE);
		memoryMap.insert(make_pair(i, p));
	}


	if (maxAddrPtr == NULL)
	{
		maxAddrPtr = p;
	}

	int maxAddrV = rand() % 128;
	memset(maxAddrPtr, maxAddrV, BLOCK_SIZE);
	cout << "Set Max Address Value " << maxAddrV << endl;
	cout << (unsigned long long)maxAddrPtr << " maxAddrPtr[0] " << (int)(maxAddrPtr[0]) << " maxAddrPtr[end] "
		<< (int)(maxAddrPtr[BLOCK_SIZE - 1]) << endl;

	sleep(2);
	std::map<int, char*>::iterator iter = memoryMap.begin();
	for (; iter != memoryMap.end(); ++iter)
	{
		if (iter->second == maxAddrPtr)
		{
			cout << "delete maxAddrPtr " << (unsigned long long)(iter->second) << endl;
		}
		delete[] iter->second;
	}
	memoryMap.clear();

	cout << "Memory Free" << endl;
}

int main()
{
	srand((unsigned)time(NULL));
	int size = 1024 * 1000;
	while (true)
	{
		cout << "Malloc Size " << size / 1024 << " MB" << endl;
		MallocMemory(size);
		size = 1024 * (1 + (rand() % 200));
		sleep(10);
	}
	return 0;
}
