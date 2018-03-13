#include "Dijkstra.hpp"
#include <unordered_set>
#include <queue>


std::function<bool(const Dijkstra::Point_Characteristic&,
		const Dijkstra::Point_Characteristic& )> 
	Dijkstra::Comparator = 
			[](Dijkstra::Point_Characteristic pc1, Dijkstra::Point_Characteristic pc2) {
		return pc1.second < pc2.second; };

Dijkstra::Dijkstra(const Point& start_p, const Point& end_p, Graph3D graph) : 
			graph(graph), V1(start_p), V9(end_p) 
{
	if (graph.at(V1).second.empty()) {
		std::cout << "No edges follows from point " << V1 << '\n';
	}
}

bool Dijkstra::algo() {
	Point current_pl = V1;
	double cur_dist = 0;
	std::pair<double, std::vector<Point>> tmp_var;
	
	std::size_t iter_count = 0; 
	std::size_t max_iter_count = graph.size();
	
	std::unordered_set<Point, PointHasher> checked;

	// queue of points to be visited 
	// with static Comparator 
	// Comparator may be optimized for A* algo
	std::priority_queue<Point_Characteristic, std::deque<Point_Characteristic>, 
		decltype(Dijkstra::Comparator)> queue(Dijkstra::Comparator);

	while (current_pl != V9 && iter_count < max_iter_count
				&& cur_dist != Graph3D::INFTY) 
	{
		if (checked.find(current_pl) == checked.end()) {
			tmp_var = graph[current_pl];
			if (iter_count != 0) {
				cur_dist = tmp_var.first;
			}
			for (auto& pl : tmp_var.second) {
				if (checked.find(pl) == checked.end()) {
					auto dist = Point::distance(V1, pl);
					auto _dist = graph[pl].first;
					if (_dist > dist + cur_dist) {
						_dist = dist + cur_dist;
						graph[pl].first = _dist;
						route[pl] = current_pl;
					}
					queue.push({ pl, _dist });
				}
			}
			checked.insert(current_pl);
		}
		current_pl = (queue.top().first);
		if (queue.empty()) {
			break;
		}
		queue.pop();
		++iter_count;
	}

	result_point = current_pl;
	result_len   = graph[current_pl].first;

	return result_point == V9;
}

void Dijkstra::show_route() const{
	Point V = V9;
	while(V != V1){
		std::cout << V << '\n';
		V = route.at(V);
	}
	std::cout << V1 << '\n';
}