#include "Dijkstra.hpp"
#include <queue>


std::function<bool(const Dijkstra::Point_Characteristic&,
		const Dijkstra::Point_Characteristic& )> 
	Dijkstra::Comparator = 
			[](Dijkstra::Point_Characteristic pc1, Dijkstra::Point_Characteristic pc2) {
		return pc1.second < pc2.second; };

Dijkstra::Dijkstra(const Point& start_p, const std::vector<Point>& end_ps, Graph3D graph) : 
			graph(graph), V1(start_p), end_point_found(false), 
			V1_bad(false) 
{
	if (graph.at(V1).second.empty()) {
		std::cout << "No edges follows from start-point " << V1 << '\n';
		V1_bad = true;
	}
	for (const auto& p : end_ps) {
		if (!graph.at(p).second.empty()) {
			V_end.insert(p);
		}
		else {
			std::cout << "No edges follows from end-point " << p << '\n';
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
	std::pair<float, std::vector<Point>> tmp_var;
	
	std::size_t iter_count = 0; 
	std::size_t max_iter_count = graph.size();
	
	std::unordered_set<Point, PointHasher> checked;

	// queue of points to be visited 
	// with static Comparator 
	// Comparator may be optimized for A* algo
	std::priority_queue<Point_Characteristic, std::deque<Point_Characteristic>, 
		decltype(Dijkstra::Comparator)> queue(Dijkstra::Comparator);



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
			tmp_var = graph.at(current_pl);
			if (iter_count != 0) {
				cur_dist = tmp_var.first;
			}
			for (auto& pl : tmp_var.second) {
				if (checked.find(pl) == checked.end()) {
					auto dist = Point::distance(current_pl, pl);
					auto _dist = graph.at(pl).first;
					if (_dist > dist + cur_dist) {
						_dist = dist + cur_dist;
						graph.at(pl).first = _dist;
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

	return end_point_found;
}

void Dijkstra::show_route(const Point& V9, std::ostream& os) const{
	if (!(V1_bad || !end_point_found)){
		Point V = V9;
		while(V != V1){
			os << V << '\n';
			V = route.at(V);
		}
		os << V1 << '\n';
	}
}