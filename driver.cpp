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

#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include "fibHeap.hpp"


typedef std::chrono::high_resolution_clock Clock;

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



std::string dijkstras_min_heap(int SOURCE, std::vector<std::vector<int>> graph, std::vector<std::vector<int>> &edgeWeight){
	std::stringstream result("Result: \n");

	auto t1 = Clock::now();

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
	int node1 = SOURCE;
	int node2 = minHeap[0].node;
	pair tempPair = minHeap[heapLocation[node1]];
	minHeap[heapLocation[node1]] = minHeap[heapLocation[node2]];
	minHeap[heapLocation[node2]] = tempPair;
	int tempLocation = heapLocation[node1];
	heapLocation[node1] = heapLocation[node2];
	heapLocation[node2] = tempLocation;
	

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
			if(leftChildLocation<itemsRemain && (minHeap[parentLocation].weight==-1 || minHeap[leftChildLocation].weight < minHeap[parentLocation].weight)){
				smallestLocation = leftChildLocation;
			}else{
				smallestLocation = parentLocation;
			}
			if(rightChildLocation<itemsRemain && (minHeap[parentLocation].weight==-1 || minHeap[rightChildLocation].weight < minHeap[smallestLocation].weight)){
				smallestLocation = rightChildLocation;
			}
			if(smallestLocation != parentLocation){
				int node1 = minHeap[parentLocation].node;
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

		for(int i = 0; i<graph[extractedNode.node].size(); i++){
			int adjNode = graph[extractedNode.node][i];
			if(minHeap[heapLocation[adjNode]].weight > extractedNode.weight + edgeWeight[extractedNode.node][i] || minHeap[heapLocation[adjNode]].weight == -1){
				minHeap[heapLocation[adjNode]].weight = extractedNode.weight + edgeWeight[extractedNode.node][i];
				minHeap[heapLocation[adjNode]].predecessor = extractedNode.node;
				while((heapLocation[adjNode]-1)/2 >=0 && (minHeap[(heapLocation[adjNode]-1)/2].weight == -1 || minHeap[heapLocation[adjNode]].weight < minHeap[(heapLocation[adjNode]-1)/2].weight)){
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

	auto t2 = Clock::now();

	for(int i=0; i<graph.size(); i++){
		if(i!=SOURCE){
			result << "\tDistance from vertex " << SOURCE << " to vertex " << i << " is " << minHeap[heapLocation[i]].weight << std::endl;
			int node = i;
			result << "\t\tPath: ";
			while(node != SOURCE){
				result << node << " <- ";
				node = minHeap[heapLocation[node]].predecessor;
			}
			result << SOURCE << std::endl;
		}
	}



	result << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << std::endl;
	
	return result.str();

}

std::string dijkstras_fib_heap(int source, std::vector<std::vector<int>> graph, std::vector<std::vector<int>> weight){
	auto t1 = Clock::now();
	std::vector<node *> result(graph.size());
	std::vector<bool> spt(graph.size(), false);
	std::vector<std::vector<int>> parent(graph.size());
    
	FibHeap * heap = new FibHeap();

	//cout << "Size: " << graph.size()<<endl;
	for(uint i = 0; i < graph.size(); i++){
		result[i] = heap->insertion(INT32_MAX, i);
	}
	heap->Decrease_key(result[source], 0);
	
	while(heap->no_of_nodes > 0){
		node * vert = heap->Extract_min();
		spt[vert->id] = true;
		for(uint j = 0; j < graph[vert->id].size(); j++){
			if(weight[vert->id][j] > 0){
					int newWeight = vert->key + weight[vert->id][j];
					int currWeight = result[graph[vert->id][j]]->key;
					if(newWeight < currWeight || currWeight < 0){
						heap->Decrease_key(result[graph[vert->id][j]], newWeight);
						parent[graph[vert->id][j]] = parent[vert->id];
						parent[graph[vert->id][j]].push_back(vert->id);
					}	
			}
		}
	}
	auto t2 = Clock::now();
	std::stringstream ret("Result: \n");
	for(uint i = 0; i < result.size(); i++){
		ret << "The Distance from node " << source << " to " << i << " is " << result[i]->key << endl;
		ret << "\tPath: " << i;
		for(int j = parent[i].size() - 1; j >= 0; j--){
			ret <<  " <- " << parent[i][j];
		}
		ret << endl;
	}
	ret << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << std::endl;
	return ret.str();
}

std::string bellman_fords(int source, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &weight){
	auto t1 = Clock::now();
	std::vector<long> dist(graph.size(), std::numeric_limits<int>::max());
	std::vector<long> prev(graph.size(), -1);
	dist[source] = 0;
	for(std::size_t i = 1; i < graph.size(); i++){
		for(std::size_t u = 0; u < graph.size(); u++){
			for(std::size_t v = 0; v < graph[u].size(); v++){
				if(dist[graph[u][v]] > dist[u] + weight[u][v]){
					dist[graph[u][v]] = dist[u] + weight[u][v];
					prev[graph[u][v]] = u;
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
	auto t2 = Clock::now();
	
	std::stringstream result("Result: \n");
	for(size_t i = 0; i < dist.size(); i++){
		if(dist[i] != std::numeric_limits<int>::max()){
			if(i == (size_t)source){
				continue;
			}
			result << "\tDistance from vertex " << source << " to vertex " << i << " is " << dist[i] << std::endl;
			int v = i;
			result << "\t\tPath: ";
			while(v != source){
				result << v << " <- ";
				v = prev[v];
			}
			result << source << std::endl;
		}else{
			result << "\tVertex " << i << " unreachable from vertex " << source << std::endl;
		}
	}
	result << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << std::endl;
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



	/*debug
	for(int u = 0; u < graph.size(); u++){
		std::cout << u << " -> ";
		for(int v = 0; v < graph[u].size(); v++){
			std::cout << graph[u][v] << ", ";
		}
		std::cout << std::endl;
	}
	*/


	std::string result;
	

	switch(algorithm){
		case DIJKSTRAS_MIN_HEAP:	result = dijkstras_min_heap(source, graph, weight);
						break;
		
		case DIJKSTRAS_FIB_HEAP:	result = dijkstras_fib_heap(source, graph, weight);
						break;
		
		case BELLMAN_FORDS:		result = bellman_fords(source, graph, weight);
						break;
		
		default:			std::cerr << "Please choose N in range [0, 2]" << std::endl;
	}
	auto t2 = Clock::now();
	output << algorithm_to_string(algorithm) << std::endl << result;

	output.close();
	return 0;
}

