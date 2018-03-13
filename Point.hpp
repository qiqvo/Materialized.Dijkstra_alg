#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <ostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include "parse_stl/parse_stl.h"

struct Point;

struct PointHasher {
	std::size_t operator()(const Point& p) const;
};

struct Point : parse_stl::point {
	Point(double xp = 0, double yp = 0, double zp = 0) : parse_stl::point(xp, yp, zp) {}
	Point(parse_stl::point p) : Point(p.x, p.y, p.z) {}

	bool operator==(const Point& p2) const;
	bool operator!=(const Point& p2) const;

	friend std::ostream & operator<<(std::ostream& os, const Point& p);

	static double distance(const Point& p1, const Point& p2);

	static const double EPS;
};

#endif // _POINT_H_