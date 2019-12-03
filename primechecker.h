#ifndef PRIMECHECKER_H
#define PRIMECHECKER_H

#include <atomic>
#include <cmath>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <jthread>

class PrimeChecker
{
private:
    std::atomic<bool> exit = false;
    std::queue<size_t> q{};

    std::mutex q_acces;
    std::mutex out_mut;
    std::condition_variable cv;

public:
    std::atomic<size_t> available_threads = 0;
    static bool is_prime(size_t p);

    //Producer Method
    void read_commands();

    //Consumer Method
    void check_prime();

private:
    void manage_input(const std::string& inp);

    size_t n_prime(size_t n) const;

};

#endif // PRIMECHECKER_H
