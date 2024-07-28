#ifndef _PAIR_H_
#define _PAIR_H_

#include "Vector2.h"

struct Pair
{
	int x, y;
	Pair() :x(0), y(0) {}
	Pair(int x, int y) :x(x), y(y) {}
	Pair(Vector2 vec) :x(int(vec.x)), y(int(vec.y)) {}
	bool operator==(const Pair& another) const
	{
		return x == another.x && y == another.y;
	}
	bool operator!=(const Pair& another) const
	{
		return x != another.x || y != another.y;
	}
};

#endif // !_PAIR_H_

