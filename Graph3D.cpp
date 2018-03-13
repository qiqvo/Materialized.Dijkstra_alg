#include "Graph3D.hpp"

const double Graph3D::INFTY = 20E10;

void Graph3D::PlaceEdge(const Point& p1, const Point& p2) {
	auto search = find(p1);
	if (search != end()) {
		auto found_vec = search->second.second;
		bool found_point = false;
		for (std::size_t i = 0; i < found_vec.size(); ++i) {
			if (found_vec[i] == p2) {
				found_point = true; break;
			}
		}
		if (!found_point){
			search->second.second.push_back(p2);
		}
	}
	else {
		insert({ p1, {INFTY, {p2}} });
	}
}

void Graph3D::add_triangle(const Point& p1, const Point& p2, const Point& p3) {
	PlaceEdge(p1, p2); PlaceEdge(p2, p1);
	PlaceEdge(p1, p3); PlaceEdge(p3, p1);
	PlaceEdge(p2, p3); PlaceEdge(p3, p2);
}

void Graph3D::print() {
	for (auto i : *this) {
		std::cout << i.first << '\n';
		for (auto j : i.second.second) {
			std::cout << '\t' << j << '\n';
		}
	}
}
