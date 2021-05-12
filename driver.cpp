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
	int SOURCE = 0;
	std::string result = "";

	typedef struct pair{
		int node;
		int weight;
		int predecessor;
	}pair;

	std::vector<pair> minHeap;
	std::vector<int> heapLocation;
	
	for(int i=0; i<graph.size(); i++){
		pair n;
		n.node = i;
		n.weight = -1;
		n.predecessor = -1;
		minHeap.push_back(n);
		heapLocation.push_back(i);
	}
	minHeap[heapLocation[SOURCE]].weight = 0;
	int itemsRemain = ((int)minHeap.size());
	while((heapLocation[SOURCE]-1)/2 >=0 && minHeap[heapLocation[SOURCE]].weight < minHeap[(heapLocation[SOURCE]-1)/2].weight){
		int node1 = SOURCE;
		int node2 = minHeap[(heapLocation[SOURCE]-1)/2].node;
		pair tempPair = minHeap[heapLocation[node1]];
		minHeap[heapLocation[node1]] = minHeap[heapLocation[node2]];
		minHeap[heapLocation[node2]] = tempPair;
		int tempLocation = heapLocation[node1];
		heapLocation[node1] = heapLocation[node2];
		heapLocation[node2] = tempLocation;
	}

	while(itemsRemain>0){
		pair extractedNode = minHeap[0];
		int node1 = minHeap[0].node;
		int node2 = minHeap[itemsRemain-1].node;
		pair tempPair = minHeap[heapLocation[node1]];
		minHeap[heapLocation[node1]] = minHeap[heapLocation[node2]];
		minHeap[heapLocation[node2]] = tempPair;
		int tempLocation = heapLocation[node1];
		heapLocation[node1] = heapLocation[node2];
		heapLocation[node2] = tempLocation;
		itemsRemain--;
		int parentLocation;
		int leftChildLocation;
		int rightChildLocation;
		int smallestLocation;
		bool repeat = true;
		int nodeSwappingDown = minHeap[0].node;
		while(repeat){
			parentLocation = heapLocation[nodeSwappingDown];
		        leftChildLocation = heapLocation[nodeSwappingDown]*2+1;
			rightChildLocation = heapLocation[nodeSwappingDown]*2+2;
			repeat = false;
			if(leftChildLocation<itemsRemain && minHeap[leftChildLocation].weight < minHeap[parentLocation].weight){
				smallestLocation = leftChildLocation;
			}else{
				smallestLocation = parentLocation;
			}
			if(rightChildLocation<itemsRemain && minHeap[rightChildLocation].weight < minHeap[smallestLocation].weight){
				smallestLocation = rightChildLocation;
			}
			if(smallestLocation != parentLocation){
				int node1 = minHeap[heapLocation[nodeSwappingDown]].node;
				int node2 = minHeap[smallestLocation].node;
				pair tempPair = minHeap[heapLocation[node1]];
				minHeap[heapLocation[node1]] = minHeap[heapLocation[node2]];
				minHeap[heapLocation[node2]] = tempPair;
				int tempLocation = heapLocation[node1];
				heapLocation[node1] = heapLocation[node2];
				heapLocation[node2] = tempLocation;
				repeat = true;
			}
		}

		result += std::to_string(extractedNode.node) + " ";
		for(int i = 0; i<graph[extractedNode.node].size(); i++){
			int adjNode = graph[extractedNode.node][i];
			if(minHeap[heapLocation[adjNode]].weight > extractedNode.weight + 1 || minHeap[heapLocation[adjNode]].weight == -1){
				minHeap[heapLocation[adjNode]].weight = extractedNode.weight + 1;
				minHeap[heapLocation[adjNode]].predecessor = extractedNode.node;
				while((heapLocation[adjNode]-1)/2 >=0 && minHeap[heapLocation[adjNode]].weight < minHeap[(heapLocation[adjNode]-1)/2].weight){
					int node1 = adjNode;
					int node2 = minHeap[(heapLocation[adjNode]-1)/2].node;
					pair tempPair = minHeap[heapLocation[node1]];
					minHeap[heapLocation[node1]] = minHeap[heapLocation[node2]];
					minHeap[heapLocation[node2]] = tempPair;
					int tempLocation = heapLocation[node1];
					heapLocation[node1] = heapLocation[node2];
					heapLocation[node2] = tempLocation;
				}
			}
		}
	}

	
	return result;
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

