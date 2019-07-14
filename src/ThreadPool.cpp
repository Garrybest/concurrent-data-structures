#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t pool_size) : stop(false)
{
    for (size_t i = 0; i < pool_size; ++i)
    {
        pool.emplace_back([this]() {
            while (true)
            {
                std::function<void()> task;
                {
                    // 临界区，获取队列数据
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->empty_condition.wait(lock, [this] {
                        return this->stop || !this->tasks.empty();
                    });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    empty_condition.notify_all();
    for (auto &&t : pool)
        t.join();
}