#pragma once
#include "Point.h"

class WeightedPoint: public Point
{
private:
	double m_weight;

public:
	WeightedPoint();
	WeightedPoint(const std::string& name, double x, double y, double weight);
	virtual ~WeightedPoint();

	// TODO: getter/setter

	virtual std::string to_string() const override;
};

