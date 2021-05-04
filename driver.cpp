//CS375 Final Project
//Ryan Geary, Thomas Gruszecki, Dylan Macejko
//All rights reserved
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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
std::string bellman_fords(std::vector<std::vector<int>> graph){
	return "THIS FUNCTION HASN'T BEEN IMPLEMENTED!\n";
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

	std::vector<std::vector<int>> graph;
	std::string result;
	switch(algorithm){
		case DIJKSTRAS_MIN_HEAP:	result = dijkstras_min_heap(graph);
						break;
		
		case DIJKSTRAS_FIB_HEAP:	result = dijkstras_fib_heap(graph);
						break;
		
		case BELLMAN_FORDS:		result = bellman_fords(graph);
						break;
		
		default:			std::cerr << "Please choose N in range [0, 2]" << std::endl;
	}
	output << algorithm_to_string(algorithm) << std::endl << result;
	return 0;
}

