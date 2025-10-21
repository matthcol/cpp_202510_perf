#pragma once
// equivalent #ifndef  #define ... #endif

#include <string>
#include <iostream>
#include <iterator>

#if defined(_MSVC_LANG)
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif



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
		print_iterable(std::next(first, dist - delta), last, "", sep, "");
	}
	std::cout << conclusion;
}

#if CPP_VERSION >= 202002L

template<std::input_iterator I, std::sentinel_for<I> S>
void print_range(
	I first,
	S last,
	std::string intro = "",
	std::string sep = " ",
	std::string conclusion = "\n",
	std::iter_difference_t<I> max_display = 10
) {
	std::cout << intro;
	auto dist = std::ranges::distance(first, last);
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
		print_range(first, std::ranges::next(first, delta), "", sep, " ... ");
		print_range(std::ranges::next(first, dist - delta), last, "", sep, "");
	}
	std::cout << conclusion;
}

template<std::ranges::input_range R> // TODO: ajouter concept printable
void print_range(
	R&& r,
	std::string intro = "",
	std::string sep = " ",
	std::string conclusion = "\n",
	std::ranges::range_difference_t<R> max_display = 10
) {
	print_range(std::ranges::begin(r), std::ranges::end(r), intro, sep, conclusion, max_display);
}

#endif