#include <fstream>
#include <iostream>

#include <random>
#include <chrono>

const int max_weight = 25;

int main(int argc, char *argv[]){
	if(argc != 4){
		std::cerr << "USAGE: " << argv[0] << " output vertex_num density" << std::endl;
		return 1;
	}

	std::ofstream output(argv[1]);
		
	std::size_t vertex_num = atoi(argv[2]);
	double density = atof(argv[3]);
	output << vertex_num << std::endl << "0" << std::endl;

	/*https://stackoverflow.com/questions/9878965/rand-between-0-and-1*/
	/*Above code used as reference for generating random numbers between 0 and 1*/
	std::mt19937_64 rng;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{uint32_t(timeSeed & 0xFFFFFFFF), uint32_t(timeSeed>>32)};
	rng.seed(ss);
	std::uniform_real_distribution<double> unif(0, 1);
	
	for(std::size_t u = 0; u < vertex_num; u++){
		for(std::size_t v = 0; v < vertex_num; v++){
			if(u != v && unif(rng) <= density){
				output << u << " " << v << " " << (int)(unif(rng)*max_weight+1) << std::endl;
			}
		}
	}

	return 0;
}
