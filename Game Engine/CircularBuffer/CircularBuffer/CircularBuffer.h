#pragma once
#ifndef _CIRCULAR_BUFFER_

#include <vector>

#define BUFFER_CAPACITY 5
typedef int MyType;

class CircularBuffer
{
private:
	MyType m_buffer[BUFFER_CAPACITY];
	int m_head;
	int m_tail;
	bool full;

public:
	CircularBuffer();

	void pushBack(MyType& value);
	void clear(void);
	MyType getAt(int index);
	int getSize(void) const;
	void Display();
	
};

#endif
