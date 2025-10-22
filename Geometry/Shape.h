#pragma once
#include <utility>
#include <string>

class Shape // abstract class car elle a au moins une méthode virtual pure
{
private:
	std::string m_name;

protected:
	Shape();
	Shape(const std::string& name);

public:
	virtual void translate(double delta_x, double delta_y) =0;
	virtual void translate(const std::pair<double, double>& delta_vector) =0;
	virtual void translate(std::pair<double, double>&& delta_vector) = 0;

	virtual std::string to_string() const;
	
	const std::string& name() const;
	void set_name(const std::string& value);

};

