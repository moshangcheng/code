#ifndef _EC_H_
#define _EC_H_

#include <memory>

namespace ec {

class Solution {
public:
	virtual double fitness() const = 0;

	virtual bool better(const Solution * ipSolution) const = 0;

	virtual Solution* copy() const = 0;

	virtual Solution* getNewSolution() const = 0;

	virtual ~Solution() {}

	typedef std::shared_ptr<Solution> Ptr;
};

class Algorithm {
public:
	virtual void run() = 0;

	virtual Solution::Ptr getBestSolution() = 0;

	~Algorithm() {}

	typedef std::shared_ptr<Algorithm> Ptr;
};

}

#endif