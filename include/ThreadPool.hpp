#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool
{

public:
    ThreadPool(size_t);
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop)
                throw std::runtime_error("Enqueue on stopped pool");
            tasks.emplace([task]() { (*task)(); });
        }
        empty_condition.notify_one(); // 唤醒一个线程进行计算
        return res;
    }
    ~ThreadPool();

private:
    std::vector<std::thread> pool;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable empty_condition;
    bool stop;
};