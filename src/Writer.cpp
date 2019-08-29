#include "Writer.hpp"
#include <climits>

void Writer::write()
{
    int expected = 0;
    while (!_cnt_ptr->compare_exchange_weak(expected, INT_MIN));
    do_write();
    *_cnt_ptr = 0;
}