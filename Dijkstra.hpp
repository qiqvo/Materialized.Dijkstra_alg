#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph3D.hpp"
#include "Point.hpp"

#include <functional>
#include <unordered_set>
#include <map>
#include <ostream>

class Dijkstra {
	// a copy of graph
	Graph3D graph;
	Point V1;
	std::unordered_set<Point, PointHasher> V_end;

	bool end_point_found, V1_bad; 

	using direction_map = std::unordered_map<Point, Point, PointHasher>;
	direction_map route;

	struct Point_Characteristic{
		Point p;
		float ch;

		bool operator<(const Point_Characteristic& pc2) const{
			return ch < pc2.ch;
		}

		bool operator==(const Point_Characteristic& pc2) const{
			return p == pc2.p;
		}
	};

public:
	Dijkstra(Graph3D, const Point& , const std::vector<Point>& );
	bool algo();
	
	// prints point by point how to get to an V9 point backwards
	// ie from the point V9 up to the V1
	void show_route(const Point&, std::ostream& os = std::cout) const;

	float distance(const Point& p) const{
		return graph.at(p).first;
	}
};

#endif // _DIJKSTRA_H_