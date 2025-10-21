#include "iotools.h"

// containers
#include <vector>
#include <list>
#include <set>
#include <forward_list>

// io
#include <iostream>

// toolbox: iterator, functional, algorithm, random
#include <iterator>
#include <functional>
#include <algorithm>
#include <random>


// pour les versions de MSVC qui definissent mal la variables __cplusplus
#if defined(_MSVC_LANG)
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif

#if CPP_VERSION >= 202002L

#include <ranges> // C++20

#endif


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
		for (int i = 0; i < 3; i++, ++it_search) {
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

	print_iterable(temperatures_big.cbegin(), temperatures_big.cend(), "big: ", ", ");
}

bool is_hot(double temperature) {
	return temperature >= 20.0;
}

void scenario_6_iterator_algorithm() {
	std::vector<double> temperatures{ 12.5, 15.0, 20.3, -2.1, 0, 9.9, -1.5, 5.4 , 22, 1.3 };
	std::vector<double> temperatures_big(1000000);
	std::vector<double> hot_temperatures;
	std::vector<double> extract_temperatures;

	for (size_t i = 0; i < 100000; ++i) {
		std::copy(temperatures.begin(), temperatures.end(), temperatures_big.begin() + i * 10);
	}

	print_iterable(temperatures_big.begin(), temperatures_big.begin() + 20, "Big temperatures first 20: ", ", ");
	print_iterable(temperatures_big.end() - 20, temperatures_big.end(), "Big temperatures  last 20: ", ", ");

	std::copy_if(temperatures_big.begin(), temperatures_big.end(), std::back_inserter(hot_temperatures), is_hot);

	print_iterable(hot_temperatures.begin(), hot_temperatures.begin() + 20, "hot temperatures first: ", ", ");
	print_iterable(hot_temperatures.end() - 20, hot_temperatures.end(), "hot_temperatures last: ", ", ");
	double threshold = 0;
	std::copy_if(
		temperatures_big.begin(),
		temperatures_big.end(),
		std::back_inserter(extract_temperatures),
		[threshold](double temperature) {return temperature < threshold; }
	);
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "extracted temperature : ", ", ");
	std::random_device rd;  // Source de vraie entropie
	std::mt19937 gen(rd()); // Mersenne Twister
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<double> corrected_temperatures(extract_temperatures.size());
	auto correct_temp = [&](double temperature) {return dist(gen) * temperature; };
	// using transform
	std::transform(
		extract_temperatures.begin(),
		extract_temperatures.end(),
		extract_temperatures.begin(), // inplace
		//corrected_temperatures.begin(), // new vector
		correct_temp
	);

	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "corrected temperature : ", ", ");

	// sorting a vector
	std::sort(extract_temperatures.begin(), extract_temperatures.end());
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "sorted temperature ASC: ", ", ");
	std::sort(extract_temperatures.begin(), extract_temperatures.end(), std::greater<double>());
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "sorted temperature DESC: ", ", ");
	std::cout << "fin" << std::endl;
}

#if CPP_VERSION >= 202002L 
void scenario_7_range_algorithm() {
	std::vector<double> temperatures{ 12.5, 15.0, 20.3, -2.1, 0, 9.9, -1.5, 5.4 , 22, 1.3 };
	std::vector<double> temperatures_big(1000000);
	std::vector<double> hot_temperatures;
	std::vector<double> extract_temperatures;

	for (size_t i = 0; i < 100000; ++i) {
		// compatibilité range vs 2 iterateurs
		//std::ranges::copy(temperatures.begin(), temperatures.end(), temperatures_big.begin() + i * 10);
		// 
		// utiliser la surcharge R&& : conteneur std::vector correspond au concept des ranges
		std::ranges::copy(temperatures, temperatures_big.begin() + i * 10);
	}

	print_iterable(temperatures_big.begin(), temperatures_big.begin() + 20, "Big temperatures first 20: ", ", ");
	print_iterable(temperatures_big.end() - 20, temperatures_big.end(), "Big temperatures  last 20: ", ", ");

	std::ranges::copy_if(temperatures_big, std::back_inserter(hot_temperatures), is_hot);

	print_iterable(hot_temperatures.begin(), hot_temperatures.begin() + 20, "hot temperatures first: ", ", ");
	print_iterable(hot_temperatures.end() - 20, hot_temperatures.end(), "hot_temperatures last: ", ", ");
	double threshold = 0;
	std::ranges::copy_if(
		temperatures_big,
		std::back_inserter(extract_temperatures),
		[threshold](double temperature) {return temperature < threshold; }
	);
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "extracted temperature : ", ", ");
	std::random_device rd;  // Source de vraie entropie
	std::mt19937 gen(rd()); // Mersenne Twister
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<double> corrected_temperatures(extract_temperatures.size());
	auto correct_temp = [&](double temperature) {return dist(gen) * temperature; };
	// using transform
	std::ranges::transform(
		extract_temperatures,
		extract_temperatures.begin(), // inplace
		correct_temp
	);

	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "corrected temperature : ", ", ");

	// sorting a vector
	std::ranges::sort(extract_temperatures);
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "sorted temperature : ", ", ");
	std::ranges::sort(extract_temperatures, std::greater<double>());
	print_iterable(extract_temperatures.begin(), extract_temperatures.end(), "sorted temperature : ", ", ");
	std::cout << "fin" << std::endl;
}

void scenario_8_range_pipeline() {
	std::vector<double> temperatures(1000000);
	std::random_device rd;  // Source de vraie entropie
	std::mt19937 gen(rd()); // Mersenne Twister
	std::uniform_real_distribution<double> dist(-10.0, 40.0);

	for (auto& t : temperatures) {
		t = dist(gen);
	}
	print_range(temperatures.begin(), temperatures.end());
	print_range(temperatures);

	double threshold = 25;
	auto result_lazy = temperatures
		| std::views::filter([threshold](double t) {return t >= threshold; })
		| std::views::transform([](double t) {return t * 0.95; })
		| std::views::drop(200) // sauter 200 valeurs
		| std::views::take(100) // prendre 100 valeurs uniquement
		;
	
	// Consommation 1 : print
	// print_range(result_lazy); // consomme l'objet Lazy du pipeline

	// Consommation 2 : resultat final dans le conteneur
	
#if CPP_VERSION >= 202302L
	// C++23
	auto results = result_lazy | std::ranges::to<std::vector<double>>();
#else
	// C++20
	std::vector<double> results;
	for (auto t : result_lazy) {
		results.push_back(t);
	}
#endif
	
	print_range(results);
}

#else
// C++ anterieur a C++20

void scenario_7_range_algorithm() {
	std::cout << "Scenario non disponible avant C++20" << std::endl;
}

void scenario_8_range_pipeline() {
	std::cout << "Scenario non disponible avant C++20" << std::endl;
}
#endif

int main() {
	scenario1_iteration_historic();
	scenario2_print_iterable();
	scenario3_const_not_const_reverse_iteration();
	scenario4_range_for_loop();
	scenario5_algorithms();
	scenario_6_iterator_algorithm();
	scenario_7_range_algorithm();
	scenario_8_range_pipeline();
	return 0;
}