#ifndef COORDINATES_H
#define COORDINATES_H
struct coordinates
{	coordinates(int first,int second,int third):first(first),second(second),third(third){}
	coordinates(){}
	int first;
	int second;
	int third;
	bool operator>=(const coordinates& rhs)
	{
		if (first >= rhs.first && second >= rhs.second
			&& third >= rhs.third)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<=(const coordinates& rhs)
	{
		if (first <= rhs.first && second <= rhs.second
			&& third <= rhs.third)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	coordinates operator+(const int& rhs)
	{
		return coordinates(first + rhs, second + rhs, third + rhs);
	}
	coordinates operator-(const int& rhs)
	{
		return coordinates(first - rhs, second - rhs, third - rhs);
	}
	coordinates operator+(const coordinates& rhs)
	{
		return coordinates(first + rhs.first, second + rhs.second, third + rhs.third);
	}
	coordinates operator-(const coordinates& rhs)
	{
		return coordinates(first - rhs.first, second - rhs.second, third - rhs.third);
	}
};
#endif COORDINATES