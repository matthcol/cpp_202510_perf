#include "DummyWeightedPoint.h"
#include <iostream>

DummyWeightedPoint::DummyWeightedPoint():m_buffer(new double[1000000])
{
}

DummyWeightedPoint::~DummyWeightedPoint()
{
	std::clog << "DummyWeightedPoint destroyed: " << this->to_string() << std::endl;
	delete[] m_buffer;
}
