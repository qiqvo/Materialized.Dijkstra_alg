#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph3D.hpp"
#include "Point.hpp"

#include <functional>
#include <map>
#include <ostream>

class Dijkstra {
	// a copy of graph
	Graph3D graph;
	Point V1, V9;

	Point result_point;
	float result_len;
	bool end_point_found, V1_bad, V9_bad; 

	using direction_map = std::unordered_map<Point, Point, PointHasher>;
	direction_map route;

	using Point_Characteristic = std::pair<Point, float>;
	// used in priority queue
	static std::function<bool(const Point_Characteristic&,
			const Point_Characteristic& )> Comparator;
public:
	Dijkstra(const Point& start_p, const Point& end_p, Graph3D graph);
	bool algo();

	std::pair<Point, float> result() const{
		return {result_point, result_len};
	}
	
	// prints point by point how to get to an V9 point backwards
	// ie from the point V9 up to the V1
	void show_route(std::ostream& os = std::cout) const;
};

#endif // _DIJKSTRA_H_