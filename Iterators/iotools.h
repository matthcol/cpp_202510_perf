#pragma once
// equivalent #ifndef  #define ... #endif

#include <string>
#include <iostream>
#include <iterator>


//template<class Iterable>
//void print_iterable(Iterable iterable);

template<class Iterator>
void print_iterable(
	Iterator first, 
	Iterator last, 
	std::string intro = "", 
	std::string sep = " ", 
	std::string conclusion = "\n",
	typename std::iterator_traits<Iterator>::difference_type max_display = 10
) {
	std::cout << intro;
	auto dist = std::distance(first, last);
	if (dist <= max_display) {
		if (first != last) {
			std::cout << *first;
			++first;
		}
		for (; first != last; ++first) {
			std::cout << sep << *first;
		}
	}
	else {
		auto delta = max_display / 2;
		print_iterable(first, std::next(first, delta), "", sep, " ... ");
		print_iterable(std::next(first, dist - delta), last, "", sep);
	}
	std::cout << conclusion;
}
