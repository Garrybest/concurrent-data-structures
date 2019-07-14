#include <iostream>
#include <thread>
#include <ctime>
#include "ThreadPool.hpp"

int main()
{
    ThreadPool pool(4);
    std::vector<std::future<std::string>> res;
    for (size_t i = 0; i < 10; ++i)
    {
        res.emplace_back(
            pool.enqueue([i]() {
                std::this_thread::sleep_for(std::chrono::seconds(i / 2));
                time_t now = time(0);
                const char *dt = ctime(&now);
                return std::string(dt);
            }));
    }
    for (auto &&f : res)
        std::cout << f.get() << std::endl;

    return 0;
}