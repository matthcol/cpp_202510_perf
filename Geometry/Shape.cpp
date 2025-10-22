#include "Shape.h"
#include <iostream>

//Shape::Shape()
//{
//	// m_name: default constructor => empty string
//}

Shape::Shape(const std::string& name): m_name(name) // copie 1 fois (et pas 2)
{
}

Shape::~Shape()
{
	std::clog << "Shape destroyed: " << this->to_string() << std::endl;
}

std::string Shape::to_string() const
{
	return m_name; // copie
}

const std::string& Shape::name() const
{
	return m_name; // by constant ref 
}

void Shape::set_name(const std::string& value)
{
	m_name = value;
}
