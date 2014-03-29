#ifndef _SA_H_
#define _SA_H_

#include <cmath>
#include "EC.h"

namespace ec {

class SAStatus {
public:

	SAStatus(double iInitialTemperature, double iMinimumTemperature, double iFactor)
		: mInitialTemperature(iInitialTemperature)
		, mMinimumTemperature(iMinimumTemperature)
		, mFactor(iFactor)
		, mCurrentTemperature(mInitialTemperature)
	{}


	bool over() {
		return (mCurrentTemperature > mMinimumTemperature);
	}

	void update() {
		mCurrentTemperature *= mFactor;
	}

	bool accept(const Solution& irOldSolution, const Solution& irNewSolution) {
		double lDelta = irNewSolution.fitness() - irOldSolution.fitness();
		if( lDelta > 0 ) {
			return true;
		}
		else if(exp(lDelta * mMinimumTemperature / mCurrentTemperature) * RAND_MAX > rand()) {
			return true;
		}
		return false;
	}

	~SAStatus() {}

	typedef std::shared_ptr<SAStatus> Ptr;

private:
	double mInitialTemperature;
	double mCurrentTemperature;
	double mMinimumTemperature;
	double mFactor;
};

class SA: public Algorithm {
public:
	SA(const Solution* ipSolution, SAStatus::Ptr ipStatus)
		: mpInitialSolution(ipSolution)
		, mpStatus(ipStatus)
	{}

	void run() {
		Solution::Ptr lCurrentSolution(mpInitialSolution->copy());
		while(!mpStatus->over()) {
			//get new solution
			Solution::Ptr lpNewSolution(lCurrentSolution->getNewSolution());

			//try to accept new solution
			if(mpStatus->accept(*lCurrentSolution, *lpNewSolution)) {
				lCurrentSolution = lpNewSolution;
			}

			if(lpNewSolution->better(mpBestSolution.get())) {
				mpBestSolution = lpNewSolution;
			}

			mpStatus->update();
		}
	}

	Solution::Ptr getBestSolution() {
		return mpBestSolution;
	}

private:
	SAStatus::Ptr mpStatus;
	const Solution* mpInitialSolution;
	Solution::Ptr mpBestSolution;
};

}
#endif