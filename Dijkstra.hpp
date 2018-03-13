#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph3D.hpp"
#include "Point.hpp"

#include <functional>

class Dijkstra {
	// a copy of graph
	Graph3D graph;
	Point V1, V9;

	using Point_Characteristic = std::pair<Point, double>;
	static std::function<bool(const Point_Characteristic&,
			const Point_Characteristic& )> Comparator;
public:
	Dijkstra(const Point& start_p, const Point& end_p, Graph3D graph);
	double algo();
};

#endif // _DIJKSTRA_H_