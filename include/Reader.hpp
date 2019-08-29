#pragma once
#include <memory>
#include <atomic>

class Reader
{
public:
    Reader(std::shared_ptr<std::atomic<int>> cnt_ptr) : _cnt_ptr(cnt_ptr) {}
    ~Reader() {}

    virtual void do_read() = 0;
    void read();

private:
    std::shared_ptr<std::atomic<int>> _cnt_ptr;
};