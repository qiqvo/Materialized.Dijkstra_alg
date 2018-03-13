#include <string>
#include <stdexcept> // out_of_range
#include <fstream>   
#include <iostream>

#include "parse_stl/parse_stl.h"
#include "Graph3D.hpp"
#include "Point.hpp"
#include "Dijkstra.hpp"

#define DEBUG

// _ _   copied from parse_stl.cpp
float parse_float(char buf[]) {
	float* fptr = (float*) buf;
	return float(*fptr);
}

Point parse_point(char buf1[], char buf2[], char buf3[]){
	return{parse_float(buf1), parse_float(buf2), parse_float(buf3)};
}
// _end_ copied from parse_stl.cpp


int main(int argc, char* argv[]){
	std::string stl_file_name = "./";
	stl_file_name += std::string(argv[1]); // testcube_20mm.stl
	std::vector<Point> V_end;
	Point V1;

#ifndef DEBUG
	V1 = parse_point(argv[2],argv[3],argv[4]);
	for (int i = 5; i < argc; i+=3){
		V_end.push_back(parse_point(argv[i],argv[i+1],argv[i+2]));
	}
#endif
	// parse stl:
	auto info = parse_stl::parse_stl(stl_file_name);
	std::vector<parse_stl::triangle> triangles = info.triangles;

	Graph3D graph;
	for (const auto& t : info.triangles){
		graph.add_triangle(t.v1, t.v2, t.v3);
	}

	// Point V1 = (std::next(begin(graph),1))->first;
	// Point V9 = (std::next(begin(graph),2))->first;
#ifdef DEBUG
	V1 = Point{10, 10, 10};
	V_end.push_back(Point{-10, -10, -10});
#endif

	for (const auto& V9 : V_end){
#ifdef DEBUG
		std::cout << V1 << '\n';
		std::cout << V9 << '\n';
#endif
		try{
			Dijkstra da(V1, V9, graph);
			if (da.algo()){
				std::cout << "route has been found.\n";
				std::cout << "distance in R3: " << Point::distance(V1, V9) << '\n';
				std::cout << "distance over triangles: " << da.result().second << '\n';
				da.show_route();
			}
			else{
				std::cout << "route has not been found.\n";
			}
		}catch(const std::out_of_range& oor){
			std::cerr << "Error in Dijkstra algo. Maybe the point does not belong to the graph.\n"; 
			std::cerr << oor.what() << '\n';
		}
	}

	std::cout << '\n' ;
	return 0;
}