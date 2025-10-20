#include <vector>
#include <iostream>
#include <set>
#include <forward_list>
#include <list>
#include <iterator>

#include "iotools.h"
#include "ittools.h"

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

void scenario3_const_not_const_reverse_iteration(){
	// 2 iterations pour tous les containers:
	// - dans l'ordre de rangement, en lecture/ecriture : begin()/end() => iterator
	// - dans l'ordre de rangement, en lecture seule (constness) : 
	//			* cbegin()/cend() => const_iterator
	//			* begin()/end() sur un const container => const_iterator
	// 
	// 2 autres bonus pour certains containers (ok: vector, set ; ko: forward_list)
	// - dans l'ordre inverse de rangement, en lecture/ecriture : rbegin()/rend() => reverse_iterator
	// - dans l'ordre inverse de rangement, en lecture seule (constness) : 
	//			* crbegin()/crend() => const_reverse_iterator
	//			* rbegin()/rend() sur un const container => const_reverse_iterator

	std::vector<double> temperatures{ 12.5, 23.1, 35.5, -2.5, 11.25, 13.75, 28.3 };
	const std::vector<double> temperatures_cst(temperatures);
	std::forward_list<double> temperatures_fwl(temperatures.cbegin(), temperatures.cend());
	std::list<double> temperatures_l(temperatures.cbegin(), temperatures.cend());
	std::set<double> temperatures_set(temperatures.cbegin(), temperatures.cend());

	print_iterable(temperatures.begin(), temperatures.end(), "temperatures originelles: ");
	for (auto it = temperatures.begin(), end = temperatures.end(); it != end; ++it) {
		*it *= 0.95;
	}
	print_iterable(temperatures.begin(), temperatures.end(), "temperatures corrigées: ");


	std::cout << temperatures.size() << " / "
		<< temperatures_cst.size()
		<< std::endl;

	/*for (auto it = temperatures_cst.begin(), end = temperatures_cst.end(); it != end; ++it) {
		*it *= 0.95;  // error
	}*/

	for (auto it = temperatures.cbegin(), end = temperatures.cend(); it != end; ++it) {
		std::cout << "Lecture: " << *it << std::endl;
		// *it *= 0.95; // error
	}

	for (auto it = temperatures_cst.cbegin(), end = temperatures_cst.cend(); it != end; ++it) {
		std::cout << "Lecture: " << *it << std::endl;
		// *it *= 0.95; // error
	}

	for (auto it = temperatures_cst.begin(), end = temperatures_cst.end(); it != end; ++it) {
		std::cout << "Lecture: " << *it << std::endl;
		// *it *= 0.95; // error
	}

	print_iterable(temperatures.crbegin(), temperatures.crend(), "temperatures [reversed vector]: ");
	print_iterable(temperatures_l.crbegin(), temperatures_l.crend(), "temperatures [reversed list]: ");
	
	// NB: forward_list a des iterateurs UniDirectional
	//print_iterable(temperatures_fwl.crbegin(), temperatures_fwl.crend(), "temperatures [reversed vector]: ");

	// le reverse fait l'equivalent du code suivant
	auto it = temperatures_l.end();
	--it;
	std::cout << "dernier : " << *it << std::endl;
	--it;
	std::cout << "avant dernier : " << *it << std::endl;

	print_iterable(temperatures_set.crbegin(), temperatures_set.crend(), "temperatures [reversed set]: ");
	auto it_set = temperatures_set.begin();
	++it_set; ++it_set; ++it_set; // forward
	// it_set += 4;
	--it_set;	// backward

	auto it_vector = temperatures.begin();
	++it_vector; 
	it_vector += 3;
	it_vector--;
	it_vector -= 3;

	// Random  access: OK pour vector, array, deque
	print_iterable(temperatures.cbegin(), temperatures.cbegin() + 4, "temperatures [4 premieres]: ");
	
	// Random : KO
	//print_iterable(temperatures_l.cbegin(), temperatures_l.cbegin() + 4, "temperatures [4 premieres]: ");
	//print_iterable(temperatures_set.cbegin(), temperatures_set.cbegin() + 4, "temperatures [4 premieres]: ");
	//print_iterable(temperatures_fwl.cbegin(), temperatures_fwl.cbegin() + 4, "temperatures [4 premieres]: ");

	// Equivalent du random access: n fois ++
	auto it_first_l = temperatures_l.cbegin();
	auto it_last_l = it_first_l; // copy
	for (int i = 0; i < 4; i++) ++it_last_l; // j'avance 4 fois de 1 position
	print_iterable(it_first_l, it_last_l, "temperatures [4 premieres, list]: ");

	// shortcut: header <iterator> => next, prev, advance, distance
	print_iterable(temperatures_l.begin(), std::next(temperatures_l.begin(), 4), "temperatures [4 premieres, list]: ");
}

void scenario4_range_for_loop() {
	std::vector<double> temperatures{ 12.5, 23.1, 35.5, -2.5, 11.25, 13.75, 28.3 };
	print_iterable(temperatures.cbegin(), temperatures.cend(), "before copy: ");

	// 1 - copie (lecture)
	for (auto temperature : temperatures) std::cout << temperature << " ";
	std::cout << std::endl;
	// code equivalent avec iterateur:
	for (auto it = temperatures.cbegin(); it != temperatures.cend(); ++it) {
		double temperature = *it; // copie
		// ...
	}



	// 1bis - copie (modif)
	for (auto temperature : temperatures) temperature *= 0.95; // modifie 1 copie, pas le tableau
	print_iterable(temperatures.cbegin(), temperatures.cend(), "after modif copy: ");

	// 2 - par ref constante (utile pour les objets complexes => evite la copie)
	for (const auto& temperature: temperatures)  std::cout << temperature << " ";
	std::cout << std::endl;

	std::vector<std::string> cities{ "Toulouse", "Pau", "Nice" };
	for (const auto& city : cities)  std::cout << city << " "; // efficace
	std::cout << std::endl;
	for (auto city : cities)  std::cout << city << " "; // pas efficace
	std::cout << std::endl;
	// code equivalent avec iterateur:
	for (auto it = cities.cbegin(); it != cities.cend(); ++it) {
		const std::string& city = *it; // 1 ref constante
		// ...
	}

	// 3 - par ref modifiable (le conteneur ne doit pas etre modifiable
	for (auto& temperature : temperatures) temperature *= 0.95;
	print_iterable(temperatures.cbegin(), temperatures.cend(), "after modif par ref: ");
	// code equivalent avec iterateur:
	for (auto it = cities.begin(); it != cities.end(); ++it) {
		std::string& city = *it; // 1 ref constante
		// ... modif possible ici
	}
}

// algorithmes avec les iterateurs
void scenario5_helper_search(
	std::vector<double>::const_iterator first, 
	std::vector<double>::const_iterator last, 
	double value
) {
	std::cout << "Search value: " << value 
		<< " among "
		<< std::distance(first, last)
		<< " values"
		<< std::endl;
	auto it_search = std::find(first, last, value);
	if (it_search != last) {
		std::cout << "Found: " << *it_search << std::endl;
		++it_search;
		// print 3 following elements if exists
		for (int i = 0; i < 3; i++) {
			if (it_search == last) break;
			std::cout << "After: " << *it_search << std::endl;
		}
	}
	std::cout << std::endl;
}

void scenario5_algorithms() {
	std::vector<double> temperatures{ 12.5, 23.1, 35.5, -2.5, 11.25, 13.75, 28.3 };
	std::vector<double> temperatures_big(1000000);

	print_iterable(temperatures.cbegin(), temperatures.cend());
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), 277.0);
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), 28.3);
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), 13.75);
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), 11.25);
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), -2.5);
	scenario5_helper_search(temperatures.cbegin(), temperatures.cend(), 35.5);
	scenario5_helper_search(temperatures.cbegin() + 3, temperatures.cend(), 35.5);
	scenario5_helper_search(temperatures.cbegin() + 2, temperatures.cend() -4, 35.5);
}

int main() {
	//scenario1_iteration_historic();
	//scenario2_print_iterable();
	//scenario3_const_not_const_reverse_iteration();
	//scenario4_range_for_loop();
	scenario5_algorithms();
	return 0;
}