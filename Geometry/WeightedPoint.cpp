#include "WeightedPoint.h"

#include <format>
#include <iostream>

WeightedPoint::WeightedPoint(): Point(), m_weight(1.0)
{
}

WeightedPoint::WeightedPoint(const std::string& name, double x, double y, double weight): Point(name, x, y), m_weight(weight)
{
}

WeightedPoint::~WeightedPoint()
{
	std::clog << "WeightedPoint destroyed: " << this->to_string() << std::endl;
}

std::string WeightedPoint::to_string() const
{
	return std::format("{}#{}", Point::to_string(), m_weight);
}
