#include "Dijkstra.hpp"
#include <unordered_set>
#include <queue>

Dijkstra::Dijkstra(const Point& start_p, const Point& end_p, Graph3D graph) : 
			graph(graph), V1(start_p), V9(end_p) {
	// auto search = graph.find(V1);
	auto vec = graph[V1].second;
	if (vec.empty()) {
		// if (!(search != graph.end())){
		std::cout << "Graph does not contain a point ";
		print_point(V1);
		std::cout << " or no edges follows from it.";
	}
}

double Dijkstra::algo() {
	Point current_pl = V1;
	double cur_dist = 0;
	std::pair<double, std::vector<Point>> tmp_var;
	int iter_count = 0; int max_iter_count = 8;
	
	std::unordered_set<Point, PointHasher> checked;

	auto Comparator = [](Dijkstra::Point_Characteristic pc1, Point_Characteristic pc2) {
		return pc1.second < pc2.second; };
	std::priority_queue<Point_Characteristic, std::deque<Point_Characteristic>, 
		decltype(Comparator)> queue(Comparator);

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

	return graph[current_pl].first;
}
