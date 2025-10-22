#pragma once
#include "WeightedPoint.h"

class DummyWeightedPoint: public WeightedPoint
{
private:
	double* m_buffer;

public:
	DummyWeightedPoint();
	virtual ~DummyWeightedPoint();
};

