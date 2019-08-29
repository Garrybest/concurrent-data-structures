/*
 * @Author: garryfang 
 * @Date: 2019-08-29 15:25:04 
 * @Last Modified by: garryfang
 * @Last Modified time: 2019-08-29 15:26:28
 */
#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

struct BlockingQueue
{
    size_t size;
    std::queue<std::function<void()>> tasks_queue;
    std::mutex queue_mutex;
    std::condition_variable full_condition;
    std::condition_variable empty_condition;
};
