#ifndef _GRAPH3D_H_
#define _GRAPH3D_H_

#include <unordered_map>
#include <utility>
#include <vector>
#include "Point.hpp"

class Graph3D : public std::unordered_map<Point, std::pair<double, std::vector<Point>>, PointHasher> {
private:
	void PlaceEdge(const Point& p1, const Point& p2);
public:
	Graph3D() : std::unordered_map<Point, std::pair<double, std::vector<Point>>, PointHasher>() {};

	void add_triangle(const Point& p1, const Point& p2, const Point& p3);

	void print();

	static const double INFTY;
};

#endif // _GRAPH3D_H_