#include "Point.h"

#include <format>
#include <iostream>

Point::Point(): Shape(), m_x(0.0), m_y(0.0)
{
}

Point::Point(const std::string& name, double x, double y): Shape(name), m_x(x), m_y(y)
{
}

Point::~Point()
{
	std::clog << "Point destroyed: " << this->to_string() << std::endl;
}

double Point::x() const
{
	return m_x;
}

void Point::set_x(double value)
{
	m_x = value;
}

double Point::y() const
{
	return m_y;
}

void Point::set_y(double value)
{
	m_y = value;
}

void Point::translate(double delta_x, double delta_y)
{
	m_x += delta_x;
	m_y += delta_y;
}

void Point::translate(const std::pair<double, double>& delta_vector)
{
	translate(delta_vector.first, delta_vector.second);
}

void Point::translate(std::pair<double, double>&& delta_vector)
{
	translate(delta_vector.first, delta_vector.second);
}

std::string Point::to_string() const
{
	return std::format("{}({}, {})", name(), m_x, m_y);
}
