#include "Consumer.hpp"

void Consumer::consume()
{
    std::function<void()> task;
    {
        std::unique_lock<std::mutex> lock(_tasks_ptr->queue_mutex);
        _tasks_ptr->empty_condition.wait(lock, [this] {
            return !this->_tasks_ptr->tasks_queue.empty();
        });
        task = std::move(_tasks_ptr->tasks_queue.front());
        _tasks_ptr->tasks_queue.pop();
    }
    _tasks_ptr->full_condition.notify_one();
    task();
}
