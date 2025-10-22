Multi threading: C++11
- class std::thread: objet bas niveau (start, atttente de resultat = join)
- std::async + std::future: meilleure gestion du resultat
- + plein d'objets de synchronisations: mutex, condition_variable, semaphore (c++20), barrier (c++20)

Gestion semi/full-auto
- en c++20: jthread (gestion automatique)
- en c++17/20: algorithmes parallélisables grâce à une policy: std::execution::par, std::execution::par_unseq
- en C++20: coroutine (prog async) => generateur, code lazy

- scheduler = biblio externe (boost, openMP, intel tbb, ...)

Multi processing:
- fork de C
- boost Process
- api os
- communication: mémoire partagée C, pipe C, messenging externe (MQ)