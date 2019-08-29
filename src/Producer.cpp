#include "Producer.hpp"

void Producer::produce(std::function<void()> &task)
{
    {
        std::unique_lock<std::mutex> lock(_tasks_ptr->queue_mutex);
        _tasks_ptr->full_condition.wait(lock, [this] {
            return this->_tasks_ptr->tasks_queue.size() < this->_tasks_ptr->size;
        });
        _tasks_ptr->tasks_queue.push(std::move(task));
    }
    _tasks_ptr->empty_condition.notify_one();
}
