//CS375 Final Project
//Ryan Geary, Thomas Gruszecki, Dylan Macejko
//All rights reserved
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <chrono>


enum ALGORITHM{
	DIJKSTRAS_MIN_HEAP = 0,
	DIJKSTRAS_FIB_HEAP = 1,
	BELLMAN_FORDS = 2
};

std::string algorithm_to_string(ALGORITHM algorithm){
	std::string result = "";
	switch(algorithm){
		case DIJKSTRAS_MIN_HEAP: result = "DIJKSTRAS_MIN_HEAP";
					 break;
		case DIJKSTRAS_FIB_HEAP: result = "DIJKSTRAS_FIB_HEAP";
					 break;
		case BELLMAN_FORDS:	 result = "BELLMAN_FORDS";	
					 break;
		default:		 result = "INVALID ALGORITHM!";
	}
	return result;
}


std::string dijkstras_min_heap(std::vector<std::vector<int>> graph){
	return "THIS FUNCTION HASN'T BEEN IMPLEMENTED!\n";
}
std::string dijkstras_fib_heap(std::vector<std::vector<int>> graph){
	return "THIS FUNCTION HASN'T BEEN IMPLEMENTED!\n";
}
std::string bellman_fords(int source, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &weight){
	std::vector<long> dist(graph.size(), std::numeric_limits<int>::max());
	dist[source] = 0;
	for(std::size_t i = 1; i < graph.size(); i++){
		for(std::size_t u = 0; u < graph.size(); u++){
			for(std::size_t v = 0; v < graph[u].size(); v++){
				if(dist[graph[u][v]] > dist[u] + weight[u][v]){
					dist[graph[u][v]] = dist[u] + weight[u][v];
				}
			}
		}
	}

	for(std::size_t u = 0; u < graph.size(); u++){
		for(std::size_t v = 0; v < graph[u].size(); v++){
			if(dist[graph[u][v]] > dist[u] + weight[u][v]){
				std::cerr << "Graph contains negative weight cycle!" << std::endl;
			}
		}
	}
	
	std::stringstream result("Result: \n");
	for(size_t i = 0; i < dist.size(); i++){
		if(dist[i] != std::numeric_limits<int>::max()){
			result << "\tDistance from vertex " << source << " to vertex " << i << " is " << dist[i] << std::endl;
		}else{
			result << "\tVertex " << i << " unreachable from vertex " << source << std::endl;
		}
	}

	return result.str();
}

int main(int argc, char **argv){
	if(argc < 4){
		std::cerr << "Usage: " << argv[0] << " <input.txt>" << " <output.txt>" << " N" << std::endl;
		return 1;
	}
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);
	
	if(!(input && output)){
		std::cerr << "Error opening files!" << std::endl
			  << "Usage: " << argv[0] << " <input.txt>" << " <output.txt>" << std::endl;
		return 1;
	}
	
	enum ALGORITHM algorithm = (ALGORITHM)(argv[3][0] - '0');

	std::size_t size;
	input >> size;

	int source;
	input >> source;

	std::vector<std::vector<int>> graph;
	std::vector<std::vector<int>> weight;
	for(std::size_t i = 0; i < size; i++){
		std::vector<int> temp;
		graph.push_back(temp);
		weight.push_back(temp);
	}

	int u, v, w;
	while(input >> u >> v >> w){
		graph[u].push_back(v);
		weight[u].push_back(w);
	}
	input.close();

	std::string result;
	
	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();
	switch(algorithm){
		case DIJKSTRAS_MIN_HEAP:	result = dijkstras_min_heap(graph);
						break;
		
		case DIJKSTRAS_FIB_HEAP:	result = dijkstras_fib_heap(graph);
						break;
		
		case BELLMAN_FORDS:		result = bellman_fords(source, graph, weight);
						break;
		
		default:			std::cerr << "Please choose N in range [0, 2]" << std::endl;
	}
	auto t2 = Clock::now();
	output << algorithm_to_string(algorithm) << std::endl << result;
	output << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << std::endl;
	output.close();
	return 0;
}

