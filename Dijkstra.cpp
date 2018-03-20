#include "Dijkstra.hpp"
#include <queue>
#include <functional>
#include <vector>

#include "UpdatePriorityQueue.hpp"

Dijkstra::Dijkstra(Graph3D graph, const Point& start_p, 
			const std::vector<Point>& end_ps) : 
			graph(graph), V1(start_p), end_point_found(false), 
			V1_bad(false) 
{
	if (graph.at(V1).second.empty()) {
		std::cout << "No edges follows from start-point " << V1 << '\n';
		V1_bad = true;
	}
	for (auto it = std::begin(end_ps); it != std::end(end_ps); ++it) {
		if (!graph.at(*it).second.empty()) {
			V_end.insert(*it);
		}
		else {
			std::cout << "No edges follows from end-point " << *it << '\n';
			std::cout << "So skip it." << '\n';
		}
	}
}

bool Dijkstra::algo() {
	if (V1_bad || V_end.empty()){
		return false;
	}

	Point current_pl = V1;
	float cur_dist = 0;
	std::vector<Point> neighbour_points;
	
	std::size_t iter_count = 0; 
	std::size_t max_iter_count = graph.size();
	
	std::unordered_set<Point, PointHasher> checked;

	// queue of points to be visited 
	UpdatePriorityQueue<Point_Characteristic> queue;

	while (iter_count < max_iter_count) 
	{
		auto end_elem = V_end.find(current_pl);
		if (end_elem != V_end.end()) {
			V_end.erase(end_elem);
			if (V_end.empty()) {
				end_point_found = true;
				break;
			}
		}
		if (checked.find(current_pl) == checked.end()) {
			neighbour_points = graph.at(current_pl).second;
			for (const auto& pl : neighbour_points) {
				if (checked.find(pl) == checked.end()) {
					auto dist = Point::distance(current_pl, pl);
					auto _dist = graph.at(pl).first;
					if (_dist > dist + cur_dist) {
						_dist = dist + cur_dist;
						graph[pl].first = _dist;
						route[pl] = current_pl;
						queue.push({ pl, _dist });
					}
				}
			}
			checked.insert(current_pl);
			++iter_count;
		}

		if (queue.empty()) {
			break;
		}

		current_pl = queue.top().p;
		cur_dist = queue.top().ch;
		queue.pop();
	}

	return end_point_found;
}

void Dijkstra::show_route(const Point& V9, std::ostream& os) const{
	if (!V1_bad && V_end.find(V9) != V_end.end()){
		Point V = V9;
		while(V != V1){
			os << V << '\n';
			V = route.at(V);
		}
		os << V1 << '\n';
	}
}