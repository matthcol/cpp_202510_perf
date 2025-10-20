#include <vector>
#include <iostream>
#include <set>
#include "iotools.h"

void scenario1_iteration_historic() {
	std::vector<int> data{ 12, 15, 20, 2, 99, 1, 54, 27, 33, 12 , 20};
	//std::vector<int> data = { 12, 15, 20, 2, 99, 1, 54, 27, 33, 12 , 20};

	// iteration C with index
	std::cout << "data [index loop]: ";
	for (size_t i = 0; i < data.size(); i++) {
		std::cout << data[i] << ' ';
	}
	std::cout << std::endl;

	// iterators de C++98
	std::cout << "data [iterator loop]: ";
	for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it) {
		int value = *it;
		std::cout << value << ' ';
	}
	std::cout << std::endl;

	// simplification de C++11: auto (type inference)
	std::cout << "data [iterator auto loop]: ";
	for (auto it = data.begin(); it != data.end(); ++it) {
		int value = *it;
		std::cout << value << ' ';
	}
	std::cout << std::endl;

	// simplification de C++11: range-for ("for-each")
	std::cout << "data [range-for]: ";
	for (auto value : data) { // iterator implicit
		std::cout << value << ' ';
	}
	std::cout << std::endl;

	// type int is not iterable
	/*for (auto digit : 123) {

	}*/

	std::set<int> dataset0; // default constructor
	std::cout << "empty data set [range-for loop]: ";
	for (auto value : dataset0) {
		std::cout << "never reached";
	}
	std::cout << std::endl;

	//std::set<int> dataset... /*reverser le contenu de data*/
	std::set<int> dataset1;
	dataset1.insert(data.begin(), data.end()); // InputIt=std::vector<int>::iterator

	// code equivalent à insert(iterators): 
	std::set<int> dataset2;
	auto first = data.begin();
	auto last = data.end();
	for (auto it = first; it != last; ++it) dataset1.insert(*it); // add 1 element

	std::set<int> dataset3(data.begin(), data.end()); // InputIt=std::vector<int>::iterator

	std::set<int> dataset4(dataset1); // copy set<int> => set<int>

	std::cout << "set [explicit iterator loop]: ";
	for (auto it = dataset1.begin(); it != dataset1.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

void scenario2_print_iterable() {
	std::vector<int> data{ 12, 15, 20, 2, 99, 1, 54, 27, 33, 12 , 20 };
	std::set<int> dataset(data.begin(), data.end());
	std::vector<std::string> cities{"Toulouse", "Nice", "Pau"};

	// parcours complets
	print_iterable(data.begin(), data.end()); // Iterator = std::vector<int>::iterator (1)
	print_iterable(data.begin(), data.end(), "Data: ", ", "); // Iterator = std::vector<int>::iterator (idem que (1))
	print_iterable(dataset.begin(), dataset.end(), "Dataset: ", ", "); // Iterator = std::set<int>::iterator (2)
	print_iterable(cities.cbegin(), cities.cend(), "Cities: "); // Iterator = std::vector<std::string>:const_iterator (3)


	// parcours partiels
	print_iterable(data.begin(), data.begin() + 3, "Data[0:3]: ");
}

int main() {
	//scenario1_iteration_historic();
	scenario2_print_iterable();
	return 0;
}