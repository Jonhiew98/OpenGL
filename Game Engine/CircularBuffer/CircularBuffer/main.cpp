// CircularBuffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CircularBuffer.h"

using namespace std;

int main()
{
	CircularBuffer cb;
	MyType value = 3;

	cout << "Size of buffer: " << cb.getSize() << endl;
	cout << cb.getAt(value) << endl;

	/*for (int i = 0; i < 10; i++)
	{

	}*/
	
	system("PAUSE");
	return 0;
}

