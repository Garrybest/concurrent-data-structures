/*
 * @Author: garryfang 
 * @Date: 2019-08-29 14:59:45 
 * @Last Modified by: garryfang
 * @Last Modified time: 2019-08-29 16:41:30
 */
#pragma once
#include <memory>
#include "BlockingQueue.hpp"

class Producer
{
public:
    Producer(std::shared_ptr<BlockingQueue> tasks_ptr) : _tasks_ptr(tasks_ptr) {}
    ~Producer(){}

    void produce(std::function<void()> &task);

private:
    std::shared_ptr<BlockingQueue> _tasks_ptr;
};