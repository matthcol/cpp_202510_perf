#include "demo_stack_heap.h"

#include <iostream>
#include <format>
#include <vector>


double& wrong_function(double x) {
	double d = 3.24 + x;
	return d; // wrong: return ref on local var
}

double* wrong_function2(double x) {
	double d = 3.24 + x;
	return &d; // wrong: return @ of local var
}

double* ok_function3(double x) {
	double* d = new double;
	*d = 3.24 + x;
	return d;
}

void demo_stack_heap() {
	std::cout << "*** DEMO Stack and Heap ***" << std::endl << std::endl;
	double a = 12.2;
	double& b = wrong_function(a);
	double* c = wrong_function2(a);
	double* e = ok_function3(a);
	std::vector<double> temperatures{ 12.5, 35.3 };
	std::vector<double> temperatures2(125000000);
	std::vector<double>* temperatures3 = new std::vector<double>(125000000);

	std::cout << a << " "
		<< b << " "
		<< *c << " "
		<< *e << " "
		<< temperatures2[temperatures2.size() - 1] << " "
		<< std::endl << std::endl;
	std::cout << std::format(
		"@a = {}, a = {}\n@e = {}, e = {}, *e = {}\n@temperatures = {}\n@temperatures2 = {}\n@temperatures3 = {}, temperatures3 = {}\n",
		reinterpret_cast<void*>(&a), a,
		reinterpret_cast<void*>(&e), reinterpret_cast<void*>(e), *e,
		reinterpret_cast<void*>(&temperatures), 
		reinterpret_cast<void*>(&temperatures2),
		reinterpret_cast<void*>(&temperatures3), reinterpret_cast<void*>(temperatures3)
	);
	delete e;
	e = nullptr;
	delete temperatures3; // => call destructor de vector
	temperatures3 = nullptr;
	std::cout << std::endl << std::endl;
} // depilement des variables
  // - vecteur temperatures => call destructor de vector (auto)
  // - vecteur temperatures2 => call destructor de vector (auto)