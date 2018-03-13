#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph3D.hpp"
#include "Point.hpp"

#include <functional>
#include <map>

class Dijkstra {
	// a copy of graph
	Graph3D graph;
	Point V1, V9;

	Point result_point;
	double result_len;

	using direction_map = std::unordered_map<Point, Point, PointHasher>;
	direction_map route;

	using Point_Characteristic = std::pair<Point, double>;
	static std::function<bool(const Point_Characteristic&,
			const Point_Characteristic& )> Comparator;
public:
	Dijkstra(const Point& start_p, const Point& end_p, Graph3D graph);
	bool algo();

	Point_Characteristic result() const{
		return {result_point, result_len};
	}

	void show_route() const;
};

#endif // _DIJKSTRA_H_