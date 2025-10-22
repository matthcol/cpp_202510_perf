#include "Shape.h"
#include "Point.h"
#include "WeightedPoint.h"
#include "Dummy.h"
#include "DummyWeightedPoint.h"

#include <iostream>
#include <vector>
#include "main.h"


void scenario1() {
	// interdit d'instancier une classe abstraite
	// Shape shape; 
	// Shape* shape_ptr = new Shape();
	Point p0;
	Point pA("A", 3.5, 12.25);
	WeightedPoint wpB("B", 4.6, 6.4, 10.0);

	std::cout << "Init: " << p0.to_string() 
		<< " ; " << pA.to_string() 
		<< " ; " << wpB.to_string()
		<< std::endl;

	Point& ref_pt = wpB;
	std::cout << ref_pt.to_string() << std::endl;

	Shape& ref_shape = wpB;
	std::cout << ref_shape.to_string() << std::endl;

	Point* point_ptr = &wpB;
	std::cout << point_ptr->to_string() << std::endl;

	Shape* shape_ptr = &wpB;
	std::cout << shape_ptr->to_string() << std::endl;

	double total_x = 0.0;
	for (auto& p : { p0, pA }) { //  { p0, pA } = initializer_list
		total_x += p.x();
	}

	std::vector<Point*> point_ptr_list{ &p0, &pA };
	for (auto point_ptr: point_ptr_list) {
		point_ptr->translate(1.0, -1.0);
	}
	std::cout << "After translate 1: " << p0.to_string() << " ; " << pA.to_string() << std::endl;

	std::vector<Point> points{ p0, pA }; // vecteur de copies
	
	// The C++ Standard forbids allocators for reference elements because of [allocator.requirements].
	// std::vector<Point&> point_ref_list;  // illegal
	// Detail: 
	//     Point&* ptr_ref; // illegal en C++
	//     std::reference_wrapper<Point>* ptr_ref; //legal (contournement)
	std::vector<std::reference_wrapper<Point>> point_ref_list;
	point_ref_list.push_back(p0); // ajout par ref
	point_ref_list.push_back(pA);
	for (auto p : point_ref_list) {
		p.get().translate(1.5, -1.5); // dereferencer le reference_wrapper (manuel)
	}
	for (Point& p: point_ref_list) { // dereferencer auto le reference_wrapper (.get())
		p.translate(10.0, -10.0);
	}

	Point& pt = point_ref_list[0];

	std::pair<double, double> vector1{ 12.3, 25.2 };
	pA.translate(vector1); // call overload with lvalue ref (const Point&)
	pA.translate({ 22.22, 11.11 }); // call overload with rvalue ref (Point&&) after converting initializer list into std::pair
}

void scenario2_dummy() {
	Dummy dummy; // default constructor
	Dummy dummy2(dummy); // copy constructor
	dummy2 = dummy; // copy operator
	Dummy dummy3 = Dummy(); // move constructor if exists
	dummy2 = Dummy(); // move operator
} // call destructor

void scenario3_destruction() {
	WeightedPoint wp("W", 12.5, 25.4, 10.0);
	Point* point_ptr = new WeightedPoint("X", 12.5, 25.4, 10.0);

	// TODO: use data

	delete point_ptr;
} // wp is destroyed here (depilement => destructor)

void scenario4_destruction2() {
	DummyWeightedPoint dwp;
	dwp.set_name("A");
	Shape* s_ptr = new DummyWeightedPoint();
	s_ptr->set_name("B");


	delete s_ptr; // call destructor B
} // call destructor A

// smart pointers: https://en.cppreference.com/w/cpp/memory.html
// - shared_ptr: compteur de 0 à n (multi-threading ou appels emboités)
// - unique_ptr : compteur de 0 à 1

// version oldschool
Point* sc5_init() {
	Point* res =  new Point("A", 1.0, 2.5);
	std::cout << "Init Point: " << res->to_string() << std::endl;
	return res;
}

void sc5_play_with_point(Point* point_ptr) {
	std::cout << "Play with point: " << point_ptr->to_string() << std::endl;
	//delete point_ptr;
}

void scenario5_smart_ptr() {
	Point* point_ptr = sc5_init();
	std::cout << "Main scenario after init: " << point_ptr->to_string() << std::endl;
	point_ptr->translate(1, -1);
	std::cout << "Main scenario after translate: " << point_ptr->to_string() << std::endl;
	sc5_play_with_point(point_ptr);
	std::cout << "Main scenario after play: " << point_ptr->to_string() << std::endl;
	delete point_ptr;
}

// version smart
std::shared_ptr<Point> sc6_init() {
	std::shared_ptr<Point> res(new Point("A", 1.0, 2.5));  // shared_ptr: counter = 1
	std::cout << "Init Point: " << res->to_string() << std::endl;
	return res; // copie => shared_ptr: counter = 2
} // depilement => shared_ptr: counter = 1

void sc6_play_with_point(std::shared_ptr<Point> point_ptr) { // shared_ptr: counter = 2
	std::cout << "Play with point: " << point_ptr->to_string() << std::endl;
} // depilement: shared_ptr: counter = 1

void scenario6_smart_ptr() {
	std::shared_ptr<Point> point_ptr = sc6_init(); // shared_ptr: counter = 1
	std::cout << "Main scenario after init: " << point_ptr->to_string() << std::endl;
	point_ptr->translate(1, -1);
	std::cout << "Main scenario after translate: " << point_ptr->to_string() << std::endl;
	sc6_play_with_point(point_ptr); // passage de parametre par copie
	std::cout << "Main scenario after play: " << point_ptr->to_string() << std::endl;
} // depilement => shared_ptr: counter = 0 => delete Point

// TODO: faire le scenario 6 en unique_ptr (penser à retourner le ptr en fin de play)

int main() {
	//scenario1();
	//scenario2_dummy();
	//scenario3_destruction();
	//scenario4_destruction2();
	//scenario5_smart_ptr();
	scenario6_smart_ptr();
	return 0;
}