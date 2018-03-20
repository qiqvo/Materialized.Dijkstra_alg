#include <string>
#include <stdexcept> // out_of_range
#include <fstream>   
#include <iostream>

#include "parse_stl/parse_stl.h"
#include "Graph3D.hpp"
#include "Point.hpp"
#include "Dijkstra.hpp"

// _ _   copied from parse_stl.cpp
float parse_float(char buf[]) {
	float* fptr = (float*) buf;
	return float(*fptr);
}

Point parse_point(char buf1[], char buf2[], char buf3[]){
	return{parse_float(buf1), parse_float(buf2), parse_float(buf3)};
}
// _end_ copied from parse_stl.cpp

/* to create file with the points of an obj
   So that py script can plot them
*/
#define PY_Visual

// #define DEBUG

int main(int argc, char* argv[]) {
	std::string stl_file_name = "";
	stl_file_name += std::string(argv[1]);
	std::vector<Point> V_end;
	Point V1;

	/* get points with cmd input */
// 	V1 = parse_point(argv[2], argv[3], argv[4]);
// 	for (int i = 5; i < argc; i += 3) {
// 		V_end.push_back(parse_point(argv[i], argv[i + 1], argv[i + 2]));
// 	}

	// parse stl:
	auto info = parse_stl::parse_stl(stl_file_name);
	std::vector<parse_stl::triangle> triangles = info.triangles;

	Graph3D graph;
	for (const auto& t : info.triangles) {
		graph.add_triangle(t.v1, t.v2, t.v3);
	}

#ifndef DEBUG
	/* graph is a map {point , vector<point>} so:
	   `std::begin(graph)` -- "first" element
	   `std::next(... , 20)` -- 20 elements after first
	   `...->first` -- returns a point in graph
	*/
	V1 = (std::next(std::begin(graph), 10))->first;
	V_end.push_back((std::next(std::begin(graph), 20))->first);
	V_end.push_back((std::next(std::begin(graph), 22148))->first);
	V_end.push_back((std::next(std::begin(graph), 139))->first);
	V_end.push_back((std::next(std::begin(graph), 33))->first);
	V_end.push_back((std::next(std::begin(graph), 13124))->first);
#else
	/* case of cube20mm */
	V1 = Point{10, 10, 10};
	V_end.push_back(Point{-10, -10, -10});

	std::cout << "start at " << V1 << '\n';
	std::cout << "end at " << V_end.at(0) << '\n';
#endif
	
	try{
		Dijkstra dij(graph, V1, V_end);

#ifdef PY_Visual
		std::ofstream points_file("points");
		for (const auto& p : graph) {
			points_file << p.first << '\n';
		}
		points_file.close();
#endif

		bool status = dij.algo();
		if (status){
			std::cout << "route has been found for every point, "
					"with non-empty edge's set, inputed.\n";
			
			std::cout << "From point (" << V1 << ")\n";
			/* print out the route from V_end to V1 in different files */
			std::string path_file_name = "path";
			for (std::size_t i = 0; i < V_end.size(); ++i) {
				std::ofstream path_file(path_file_name + std::to_string(i));
				dij.show_route(V_end[i], path_file);
				std::cout << "Distance to point (" << V_end[i] << ") is \t" << 
					dij.distance(V_end[i]) << '\n';
				std::cout << "Distance in R3 : " << Point::distance(V1, V_end[i]) << "\n\n";
				path_file.close();
			}
		}
		else{
			std::cout << "route has not been found.\n";
		}
	}catch (const std::out_of_range& oor) {
		std::cerr << "Error in Dijkstra algo." 
					"Maybe the point does not belong to the graph.\n";
		std::cerr << oor.what() << '\n';
	}
	
	std::cin.get();
	return 0;
}