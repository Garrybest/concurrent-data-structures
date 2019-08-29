#pragma once
#include <memory>
#include "BlockingQueue.hpp"

class Consumer
{
public:
    Consumer(std::shared_ptr<BlockingQueue> tasks_ptr) : _tasks_ptr(tasks_ptr){}
    ~Consumer(){}

    void consume();

private:
    std::shared_ptr<BlockingQueue> _tasks_ptr;
};