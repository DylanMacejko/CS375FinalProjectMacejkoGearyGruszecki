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
#include <iostream>
#include <malloc.h>

 using namespace std;
// Creating a structure to represent a node in the heap
struct node {
    node* parent; // Parent pointer
    node* child; // Child pointer
    node* left; // Pointer to the node on the left
    node* right; // Pointer to the node on the right
    int key; // Value of the node
	int id;
    int degree; // Degree of the node
    char mark; // Black or white mark of the node
    char c; // Flag for assisting in the Find node function
};
 
// Creating min pointer as "mini"
struct node* mini = NULL;
 
// Declare an integer for number of nodes in the heap
int no_of_nodes = 0;
 
// Function to insert a node in heap
node * insertion(int val, int i)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->key = val;
    new_node->degree = 0;
    new_node->mark = 'W';
    new_node->c = 'N';
	new_node->id = i;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->left = new_node;
    new_node->right = new_node;
    if (mini != NULL) {
        (mini->left)->right = new_node;
        new_node->right = mini;
        new_node->left = mini->left;
        mini->left = new_node;
        if (new_node->key < mini->key)
            mini = new_node;
    }
    else {
        mini = new_node;
    }
    no_of_nodes++;
	return new_node;
}
// Linking the heap nodes in parent child relationship
void Fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        mini = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}
// Consolidating the heap
void Consolidate()
{
    int temp1;
    float temp2 = (log(no_of_nodes)) / (log(2));
    int temp3 = temp2;
    struct node* arr[temp3];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    node* ptr1 = mini;
    node* ptr2;
    node* ptr3;
    node* ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL) {
            ptr2 = arr[temp1];
            if (ptr1->key > ptr2->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = NULL;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL) {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}
 
// Function to extract minimum node in the heap
node * Extract_min()
{
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else {
        node* temp = mini;
		node * tempee = mini;
        node* pntr;
        pntr = temp;
        node* x = NULL;
        if (temp->child != NULL) {
 
            x = temp->child;
            do {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        mini = temp->right;
        if (temp == temp->right && temp->child == NULL)
            mini = NULL;
        else {
            mini = temp->right;
            Consolidate();
        }
        no_of_nodes--;
		return tempee;
    }

}
 
// Cutting a node in the heap to be placed in the root list
void Cut(struct node* found, struct node* temp)
{
    if (found == found->right)
        temp->child = NULL;
 
    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;
 
    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}
 
// Recursive cascade cutting function
void Cascase_cut(struct node* temp)
{
    node* ptr5 = temp->parent;
    if (ptr5 != NULL) {
        if (temp->mark == 'W') {
            temp->mark = 'B';
        }
        else {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}
 
// Function to decrease the value of a node in the heap
void Decrease_key(struct node* found, int val)
{
    if (mini == NULL)
        cout << "The Heap is Empty" << endl;
 
    if (found == NULL)
        cout << "Node not found in the Heap" << endl;
 
    found->key = val;
 	//cout << "d" << endl;
    struct node* temp = found->parent;
    if (temp != NULL && found->key < temp->key) {
        //cout << "hi" << endl;
		Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key){
		//cout << "x" << endl;
        mini = found;
	}
}
 
// Function to find the given node
void Find(struct node* mini, int old_val, int val)
{
    struct node* found = NULL;
    node* temp5 = mini;
    temp5->c = 'Y';
    node* found_ptr = NULL;
    if (temp5->key == old_val) {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == NULL) {
        if (temp5->child != NULL)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}
 
// Deleting a node from the heap
void Deletion(int val)
{
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else {
 
        // Decreasing the value of the node to 0
        Find(mini, val, 0);
 
        // Calling Extract_min function to
        // delete minimum value node, which is 0
        Extract_min();
        cout << "Key Deleted" << endl;
    }
}


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

std::string dijkstras_fib_heap(int source, std::vector<std::vector<int>> graph, std::vector<std::vector<int>> weight){
	std::vector<node *> result(graph.size());
	std::vector<bool> spt(graph.size(), false);
	//cout << "Size: " << graph.size()<<endl;
	for(uint i = 0; i < graph.size(); i++){
		result[i] = insertion(5000, i);
	}
	Decrease_key(result[source], 0);
	
	while(no_of_nodes > 0){
		for(uint i = 0; i < graph.size(); i++){
			//cout << result[i]->id << " " << result[i]->key << ", ";
		}
        //display();
		node * vert = Extract_min();
		spt[vert->id] = true;
        
		for(uint j = 0; j < graph[vert->id].size(); j++){
			//cout << endl << j << endl;
			if(weight[vert->id][j] > 0){
					uint newWeight = vert->key + weight[vert->id][j];
					//cout <<"NW: " << newWeight << endl;
					uint currWeight = result[graph[vert->id][j]]->key;
                    //cout <<"CW: " << currWeight << endl;
					if(newWeight < currWeight){
                        //cout << "hi" << endl;
						Decrease_key(result[graph[vert->id][j]], newWeight);
					}	
			}
		}
	}
	std::stringstream ret("Result: \n");
	for(uint i = 0; i < result.size(); i++){
		ret << "The Distance from node " << source << " to " << i << " is " << result[i]->key << endl;
	}
	return ret.str();
}
std::string bellman_fords(int source, std::vector<std::vector<int>> graph, std::vector<std::vector<int>> weight){
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
		
		case DIJKSTRAS_FIB_HEAP:	result = dijkstras_fib_heap(source, graph, weight);
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

