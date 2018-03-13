#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>

#include "parse_stl/parse_stl.h"
#include "Graph3D.hpp"
#include "Point.hpp"
#include "Dijkstra.hpp"

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << '\n';

	std::string stl_file_name = "./Copernicuscrater3Xv.stl";
	
	auto info = parse_stl::parse_stl(stl_file_name);
	
	std::vector<parse_stl::triangle> triangles = info.triangles;
	std::cout << "STL HEADER = " << info.name << std::endl;
	std::cout << "# triangles = " << triangles.size() << std::endl;

	Graph3D graph;

	for (const auto& t : info.triangles){
		graph.add_triangle(static_cast<Point>(t.v1), 
			static_cast<Point>(t.v2), static_cast<Point>(t.v3));
	}

	// graph.print();

	// get starting point:
	// get V1

	Point V1 = (std::next(begin(graph),5)) ->first;
	Point V9 = (std::next(begin(graph),30))->first;

	print_point(V1);
	std::cout << '\n';
	print_point(V9);
	std::cout << '\n';
	
	Dijkstra da(V1, V9, graph);
	std::cout << da.algo() << '\n';
	std::cout << '\n';
 	
 	// graph.print();
	// std::cin.get();
	return 0;
}