#include <iostream>
#include <thread>

int main()
{
    std::thread t([]() { std::cout << "t1" << std::endl; });
    t.join();
    return 0;
}