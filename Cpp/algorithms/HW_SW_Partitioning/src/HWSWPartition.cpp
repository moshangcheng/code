#include <iostream>
#include <ctime>
#include "HWSWPartition.h"

HWSWPartition::HWSWPartition()
	: mNodeCount(0)
	, mpNode(NULL)
	, mRelation(NULL)
{
}

//TODO: read a HW-SW Partition problem from TGFF
void HWSWPartition::parseTGFF(const char* ipTGFFFile) {
	return;
}

double HWSWPartition::getRandom(double lower, double upper) {
	return lower + (upper - lower) * (rand() / RAND_MAX);
}

//generate a random  HW-SW Partition problem
//ref: http://mathematica.stackexchange.com/questions/608/how-to-generate-random-directed-acyclic-graphs
void HWSWPartition::initialize(const HWSWPartitionConfig& irConfig) {
	mNodeCount = irConfig.mNodeCount;
	mTimeUpperBound = irConfig.mTimeUpperBound;
	mPriceUpperBound = irConfig.mPriceUpperBound;

	mpNode = new HWSWPartitionNode[mNodeCount];
	mRelation = new bool[mNodeCount * mNodeCount];

	for(int i = 0; i < mNodeCount; i++) {
		mpNode[i].mHWPriceCost = getRandom(irConfig.mMinHWPriceCost, irConfig.mMaxHWPriceCost);
		mpNode[i].mSWPriceCost = getRandom(irConfig.mMinSWPriceCost, irConfig.mMaxSWPriceCost);
		mpNode[i].mHWTimeCost = getRandom(irConfig.mMinHWTimeCost, irConfig.mMaxHWTimeCost);
		mpNode[i].mSWTimeCost = getRandom(irConfig.mMinSWTimeCost, irConfig.mMaxSWTimeCost);
	}

	//the generated DAG is already sorted by topological order
	//that's to say, node i cannot be the parent of node j if i < j
	for(int i = 0; i < mNodeCount; i++) {
		for(int j = 0; j < mNodeCount; j++) {
			if(j < i && (rand() % irConfig.mProbability == 0)) {
				mRelation[i * mNodeCount + j] = 1;	//now node i is the parent of node j
			} else {
				mRelation[i * mNodeCount + j] = 0;
			}
		}
	}
}

HWSWPartition::~HWSWPartition() {
	if(mNodeCount > 0) {
		if(mpNode != NULL) {
			delete [] mpNode;
			mpNode = NULL;
		}

		if(mRelation != NULL) {
			delete [] mRelation;
			mRelation = NULL;
		}
	}
}

HWSWPartitionSolution::HWSWPartitionSolution(const HWSWPartition* ipHWSWPartition)
	: mPartition(NULL)
	, mpHWSWPartition(ipHWSWPartition)
{
	initialize();
}

HWSWPartitionSolution::HWSWPartitionSolution(const HWSWPartitionSolution& irHWSWPartitionSolution) {
	mpHWSWPartition = irHWSWPartitionSolution.mpHWSWPartition;

	int lNodeCount = mpHWSWPartition->mNodeCount;
	mPartition = new bool[lNodeCount];
	for(int i = 0; i < lNodeCount; i++) {
		mPartition[i] = irHWSWPartitionSolution.mPartition[i];
	}
}

HWSWPartitionSolution::~HWSWPartitionSolution() {
	if(mPartition != NULL) {
		delete [] mPartition;
		mPartition = NULL;
	}
}

//use greedy algorithm to generate a intial solution
void HWSWPartitionSolution::initialize() {
	mPartition = new bool[mpHWSWPartition->mNodeCount];
	//try to use hardware first
	double lTotalHWTime = 0;
	double lTotalSWTime = 0;
	for(int i = 0; i < mpHWSWPartition->mNodeCount; i++) {
		if(lTotalHWTime < lTotalSWTime) {
			//use hardware to execute this task
			mPartition[i] = 1;
			lTotalHWTime += mpHWSWPartition->mpNode[i].mHWTimeCost;
		} else {
			//use software to execute this task
			mPartition[i] = 0;
			lTotalSWTime += mpHWSWPartition->mpNode[i].mSWTimeCost;
		}
	}
}

ec::Solution* HWSWPartitionSolution::getNewSolution() const {
	HWSWPartitionSolution* lpSolution = new HWSWPartitionSolution(*this);
	int lNodeID = rand() % lpSolution->mpHWSWPartition->mNodeCount;
	lpSolution->mPartition[lNodeID] = !(lpSolution->mPartition[lNodeID]);
	return lpSolution;
}

ec::Solution* HWSWPartitionSolution::copy() const {
	return new HWSWPartitionSolution(*this);
}

double HWSWPartitionSolution::fitness() const {
	//get total time cost and price cost
	double lTimeCost = 0;
	double lPriceCost = 0;
	for(int i = 0; i < mpHWSWPartition->mNodeCount; i++) {
		lTimeCost += mPartition[i] ? mpHWSWPartition->mpNode[i].mHWTimeCost: mpHWSWPartition->mpNode[i];
		lPriceCost += mPartition[i] ? mpHWSWPartition->mpNode[i]: mpHWSWPartition->mpNode[i];
	}
	return lPriceCost;
}

bool HWSWPartitionSolution::better(const ec::Solution* ipSolution) const {
	return fitness() > ipSolution->fitness();
}

bool HWSWPartitionSolution::good() const {
	//get total time cost and price cost
	double lTimeCost = 0;
	double lPriceCost = 0;
	for(int i = 0; i < mpHWSWPartition->mNodeCount; i++) {
		lTimeCost += mPartition[i] ? mpHWSWPartition->mpHWTimeCost[i]: mpHWSWPartition->mpSWTimeCost[i];
		lPriceCost += mPartition[i] ? mpHWSWPartition->mpHWPriceCost[i]: mpHWSWPartition->mpSWPriceCost[i];
	}

	std::cout << "check solution:\n";
	for(int i = 0; i < mpHWSWPartition->mNodeCount; i++) {
		std::cout << mPartition[i] << " ";
	}
	std::cout << std::endl;

	//check whether current solution satisfies constraint conditions
	if(lTimeCost < mpHWSWPartition->mTimeUpperBound && lPriceCost < mpHWSWPartition->mPriceUpperBound) {
		return true;
	} else {
		return false;
	}
}

//get the time cost
double HWSWPartitionSolution::getTimeCost() const {
	double lTotalHWTime = 0;
	double lTotalSWTime = 0;
	for(int i = 0; i < mpHWSWPartition->mNodeCount; i++) {
		if(lTotalHWTime < lTotalSWTime) {
			//use hardware to execute this task
			mPartition[i] = 1;
			lTotalHWTime += mpHWSWPartition->mpNode[i].mHWTimeCost;
		} else {
			//use software to execute this task
			mPartition[i] = 0;
			lTotalSWTime += mpHWSWPartition->mpNode[i].mSWTimeCost;
		}
	}
}

double HWSWPartitionSolution::getPriceCost() const {

}