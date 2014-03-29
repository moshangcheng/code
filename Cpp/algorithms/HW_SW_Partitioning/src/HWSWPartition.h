#ifndef _HWSWPARTITION_H
#define _HWSWPARTITION_H

#include "EC.h"

struct HWSWPartitionNode {
	double mHWPriceCost;
	double mSWPriceCost;
	double mHWTimeCost;
	double mSWTimeCost;
};

//the data used to generate a random HW-SW Paritition problem
struct HWSWPartitionConfig {
	int mNodeCount;

	double mMinHWPriceCost;
	double mMaxHWPriceCost;
	double mMinSWPriceCost;
	double mMaxSWPriceCost;
	
	double mMinHWTimeCost;
	double mMaxHWTimeCost;
	double mMinSWTimeCost;
	double mMaxSWTimeCost;

	//constraint conditions
	double mTimeUpperBound;
	double mPriceUpperBound;

	int mProbability;	// the probability of node i is the parent of node j when i > j
};

class HWSWPartition {
public:
	HWSWPartition();

	//TODO: read a HW-SW Partition problem from TGFF
	void parseTGFF(const char* ipTGFFFile);

	//generate a random  HW-SW Partition problem
	//ref: http://mathematica.stackexchange.com/questions/608/how-to-generate-random-directed-acyclic-graphs
	void initialize(const HWSWPartitionConfig& irConfig);

	double getRandom(double lower, double upper);

	~HWSWPartition();

	int mNodeCount;
	HWSWPartitionNode* mpNode;
	bool* mRelation;

	//constraint conditions
	double mTimeUpperBound;
	double mPriceUpperBound;
};

class HWSWPartitionSolution: public ec::Solution {
public:
	HWSWPartitionSolution(const HWSWPartition* ipHWSWPartition);

	HWSWPartitionSolution(const HWSWPartitionSolution& irHWSWPartitionSolution);

	~HWSWPartitionSolution();

	ec::Solution* getNewSolution() const;

	ec::Solution* copy() const;

	double fitness() const;

	bool better(const ec::Solution* ipHWSWPartitionSolution) const;

private:
	//generate a random solution
	void initialize();

	//satisfy constraint
	bool good() const;

	double getTimeCost() const;
	double getPriceCost() const;

	const HWSWPartition* mpHWSWPartition;
	bool* mPartition;
};

#endif