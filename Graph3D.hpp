#ifndef _GRAPH3D_H_
#define _GRAPH3D_H_

#include <unordered_map>
#include <utility>
#include <vector>
#include "Point.hpp"


// Graph specialized for Dijkstra algorithm and stl input data
/*
	maintain vertexes that are found in stl file
	to every point assigned to <length from the begin_point, 
								array of points connected with it>

	At the beginning all length are INFTY
*/
class Graph3D : public std::unordered_map<Point, std::pair<float, std::vector<Point>>, PointHasher> {
private:
	void PlaceEdge(const Point& p1, const Point& p2);
public:
	Graph3D() : std::unordered_map<Point, std::pair<float, std::vector<Point>>, PointHasher>() {};

	void add_triangle(const Point& p1, const Point& p2, const Point& p3);

	void print();

	static const float INFTY;
};

#endif // _GRAPH3D_H_