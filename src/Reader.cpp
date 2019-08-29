#include "Reader.hpp"

void Reader::read()
{
    bool done = false;
    while (!done)
    {
        if (*_cnt_ptr >= 0)
        {
            ++(*_cnt_ptr);
            if (*_cnt_ptr > 0)
            {
                do_read();
                done = true;
                --(*_cnt_ptr);
            }
        }
    }
}