#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include "primechecker.h"

using thread_t = std::jthread;
int main()
{

    const size_t nThreads = 4;
    if (nThreads > thread_t::hardware_concurrency())
    {
        std::cerr << "Atencion: Numero de hilos superior a los hilos de hardware\n";
    }
    
    PrimeChecker g;

    thread_t read(&PrimeChecker::read_commands, std::ref(g));

    std::vector<thread_t> consumers(nThreads);
    for (thread_t& t: consumers)
    {
    	//Si quisiera usar stop_toke:
    	//t = thread_t([&](std::stop_token st){ g.check_prime(std::move(st)); });
    	//Y anadir como argumento a check_prime un stop_token
        t = thread_t(&PrimeChecker::check_prime, std::ref(g));
    }
	read.join();
	std::cout << "Saliendo..." << std::endl;
	/*for (thread_t& t: consumers)
	{
		t.request_stop();
	}*/
    return 0;
}
