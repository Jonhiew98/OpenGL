#include "pch.h"
#include <iostream>
#include "CircularBuffer.h"

using namespace std;

CircularBuffer::CircularBuffer()
{
	m_tail = 0;
	m_head = 0;
	full = false;
}

void CircularBuffer::pushBack(MyType& value)
{
	m_buffer[m_head] = value;

	if (full)
	{
		m_tail = (m_tail + 1) % BUFFER_CAPACITY;
	}

	m_head = (m_head + 1) % BUFFER_CAPACITY;

	full = m_head == m_tail;
}

void CircularBuffer::clear()
{
	m_head = m_tail;
	full = false;
}

int CircularBuffer::getAt(int value)
{
	int temp = m_head - value;
	if (temp < 0)
	{
		temp += BUFFER_CAPACITY;
	}
	return m_buffer[temp];
}

int CircularBuffer::getSize(void) const
{
	int fullSize = BUFFER_CAPACITY;
	if (!full)
	{
		if (m_head >= m_tail)
		{
			fullSize = m_head - m_tail;
		}
		else
		{
			fullSize= BUFFER_CAPACITY + m_head - m_tail;
		}
	}
	return fullSize;
}

void CircularBuffer::Display()
{

}

