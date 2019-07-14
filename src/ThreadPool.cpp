#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t pool_size) : stop(false)
{
    for (size_t i = 0; i < pool_size; ++i)
    {
        pool.emplace_back([this]() {
            {
                std::unique_lock<std::mutex> lock(this->queue_mutex);
                this->empty_condition.wait(lock, [this] {
                    return this->stop || this->tasks.empty();
                })
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
}