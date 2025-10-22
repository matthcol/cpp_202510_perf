#pragma once
#include "Shape.h"

class Point: public Shape
{
private:
	double m_x;
	double m_y;

public:
	Point(); // celui par defaut ne me convient pas (x, y aleatoire)
	Point(const std::string& name, double x, double y);
	virtual ~Point();

	double x() const;
	void set_x(double value);

	double y() const;
	void set_y(double value);

	virtual void translate(double delta_x, double delta_y) override;
	virtual void translate(const std::pair<double, double>& delta_vector) override;
	virtual void translate(std::pair<double, double>&& delta_vector) override;

	virtual std::string to_string() const override;
};

