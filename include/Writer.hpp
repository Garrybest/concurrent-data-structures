#pragma once
#include <memory>
#include <atomic>
#include <mutex>

class Writer
{
public:
    Writer(std::shared_ptr<std::atomic<int>> cnt_ptr) : _cnt_ptr(cnt_ptr) {}
    ~Writer() {}

    virtual void do_write() = 0;
    void write();

private:
    std::shared_ptr<std::atomic<int>> _cnt_ptr;
};