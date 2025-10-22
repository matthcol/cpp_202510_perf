#include <thread>
#include <iostream>
#include <vector>
#include <future>
#include <numeric>
#include <execution>

void compute1(double x, double y) {
	double res = x + y;
	std::cout << "Computing 1 finished: " << res << std::endl;
}


void scenario_mono_thread() {
	// Heap shared, 1 stack by thread

	std::cout << "**** Scenario 1 : 1 thread ****" << std::endl << std::endl;

	std::thread t1(compute1, 12, 13); 
	std::cout << "Job started: computing 1" << std::endl;
	t1.join();

	std::cout << std::endl << std::endl;
}

void computing_vector(std::vector<double>::iterator first, std::vector<double>::iterator last, std::vector<double>::iterator out) {
	double total = 0.0;
	for (; first != last; ++first) {
		total += *first;
	}
	*out = total; // store result in shared memory (heap)
	// std::cout << "Computing vector finished: " << total << std::endl;
}


void scenario_multi_thread() {
	std::cout << "**** Scenario 2 : multi thread ****" << std::endl << std::endl;

	std::vector<double>* data_ptr = new std::vector<double>(1000000);
	double seed = 0.11;
	for (auto& d : *data_ptr) {
		d = seed;
		seed += 0.11;
	}


	std::vector<std::thread> threads;
	size_t n = 10;

	// allocate future result data
	std::vector<double>* results_ptr = new std::vector<double>(n);

	size_t chunck = data_ptr->size() / n;
	for (size_t i = 0; i < n; i++) {
		threads.push_back(std::thread(
			computing_vector, 
			data_ptr->begin() + i * chunck, 
			data_ptr->begin() + (i + 1) * chunck,
			results_ptr->begin() + i
		));
	}
	std::cout << "Jobs started" << std::endl;
	for (auto& t : threads) {
		t.join();
	}
	std::cout << "Results ready: ";
	for (double d : *results_ptr) {
		std::cout << d << " ";
	}
	std::cout << std::endl << std::endl;
}

double computing_vector2(std::vector<double>::iterator first, std::vector<double>::iterator last) {
	double total = 0.0;
	for (; first != last; ++first) {
		total += *first;
	}
	return total; // return result in the stack
}

void scenario_multi_thread_future() {
	std::cout << "**** Scenario 3 : multi thread + future ****" << std::endl << std::endl;

	std::vector<double>* data_ptr = new std::vector<double>(1000000);
	double seed = 0.11;
	for (auto& d : *data_ptr) {
		d = seed;
		seed += 0.11;
	}


	std::vector<std::future<double>> futures;
	std::vector<double> results;
	size_t n = 10;
	

	size_t chunck = data_ptr->size() / n;
	for (size_t i = 0; i < n; i++) {
		futures.push_back(
			std::async(
				computing_vector2,
				data_ptr->begin() + i * chunck,
				data_ptr->begin() + (i + 1) * chunck
		));
	}
	std::cout << "Jobs started" << std::endl;
	
	// atente des resultats
	for (auto& f : futures) {
		results.push_back(f.get());
	}

	std::cout << "Results ready: ";
	for (double d : results) {
		std::cout << d << " ";
	}
	std::cout << std::endl << std::endl;
}

void scenario_multi_thread_algorithme() {
	std::cout << "**** Scenario 4 : parallel algorithm ****" << std::endl << std::endl;

	std::vector<double> data(1000000);
	double seed = 0.11;
	for (auto& d : data) {
		d = seed;
		seed += 0.11;
	}

	double total1 = std::reduce(std::execution::seq, data.begin(), data.end());
	double total2 = std::reduce(std::execution::par, data.begin(), data.end());
	double total3 = std::reduce(std::execution::par_unseq, data.begin(), data.end());
	double total4 = std::reduce(std::execution::unseq, data.begin(), data.end());

	std::cout << "Results ready (SEQ, PAR, PAR_UNSEQ, UNSEQ): ";
	for (double d : {total1, total2, total3, total4}) {
		std::cout << d << " ";
	}
	std::cout << std::endl << std::endl;
}


int main() {
	scenario_mono_thread();
	scenario_multi_thread();
	scenario_multi_thread_future();
	scenario_multi_thread_algorithme();
}