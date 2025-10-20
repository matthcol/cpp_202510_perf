#pragma once
// equivalent #ifndef  #define ... #endif

#include <string>
#include <iostream>


//template<class Iterable>
//void print_iterable(Iterable iterable);

template<class Iterator>
void print_iterable(Iterator first, Iterator last, std::string intro = "", std::string sep = " ") {
	std::cout << intro;
	for (auto it = first; it != last; ++it) {
		std::cout << *it << sep; // TODO: do not print separator after last element
	}
	std::cout << std::endl; // TODO: add an optional parameter
}
