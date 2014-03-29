#include <ctime>
#include "SA.h"
#include "HWSWPartition.h"

int main() {
	srand(time(NULL));
	//create HW-SW Partition problem
	HWSWPartitionConfig lHWSWPartitionConfig = {
		//used to generate random HW-SW Partition problem
		20,	//node count
		40,		//max hardware price cost
		20,		//min hardware price cost
		10,		//max software price cost
		5,		//min software price cost
		10,		//max hardeare time cost
		5,		//min hardeare time cost
		20,		//max software time cost
		10,		//mix software time cost
		// constraint conditions
		200,	//time upper bound
		800,	//cost upper bound
		//used to generate DAG
		5		//max hardeare time cost
	};
	HWSWPartition lHWSWPartition;
	lHWSWPartition.initialize(lHWSWPartitionConfig);

	//create a initial solution
	HWSWPartitionSolution lSolution(&lHWSWPartition);

	//set initial status of Simulated Annealing algorithm
	ec::SAStatus::Ptr lpStatus(new ec::SAStatus(100, 10, 0.9));

	//create Simulated Annealing algorithm instance
	ec::SA lSA(&lSolution, lpStatus);

	//run Simulated Annealing algorithm
	lSA.run();

	ec::Solution::Ptr lpBestSolution = lSA.getBestSolution();

	return 0;
}