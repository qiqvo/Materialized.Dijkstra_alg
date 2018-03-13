#include <string>
#include <stdexcept> // out_of_range
#include <fstream>   
#include <iostream>

#include "parse_stl/parse_stl.h"
#include "Graph3D.hpp"
#include "Point.hpp"
#include "Dijkstra.hpp"

int main(int argc, char* argv[]){
	std::string stl_file_name = std::string(argv[1]); // testcube_20mm.stl
	
	auto info = parse_stl::parse_stl(stl_file_name);
	
	std::vector<parse_stl::triangle> triangles = info.triangles;
	std::cout << "STL HEADER = " << info.name << std::endl;
	std::cout << "# triangles = " << triangles.size() << std::endl;

	Graph3D graph;

	for (const auto& t : info.triangles){
		graph.add_triangle(t.v1, t.v2, t.v3);
	}

	// get starting point:
	// get V1

	// Point V1 = (std::next(begin(graph),1))->first;
	// Point V9 = (std::next(begin(graph),2))->first;
	Point V1{10, 10, 10};
	Point V9{-10, -10, 5};

	std::cout << V1 << '\n';
	std::cout << V9 << '\n';
	
	try{
		Dijkstra da(V1, V9, graph);
		std::cout << "End point has been found: " << da.algo() << '\n';
		std::cout << "distance in R3: " << Point::distance(V1, V9) << '\n';
		std::cout << "distance over triangles: " << da.result().second << '\n';
	
		da.show_route();
	}catch(const std::out_of_range& oor){
		std::cerr << "Error in Dijkstra algo. Maybe the point does not belong to graph.\n"; 
		std::cerr << oor.what() << '\n';
	}

	std::cout << '\n' << '\n';
 	// graph.print();
 	
	// std::cin.get();
	return 0;
}