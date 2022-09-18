//
// Created by lhc456 on 2022/9/18.
//

#ifndef PLAY_WITH_ALGO_LEAKDETECTOR_H
#define PLAY_WITH_ALGO_LEAKDETECTOR_H

#include <iostream>
#include <inttypes.h>


void *operator new(size_t _size, char *_file, unsigned int _line);

void *operator new[](size_t _size, char *_file, unsigned int _line);
// 此处宏的作用下一节实现 LeakDetector.cpp 时说明
#ifndef __NEW_OVERLOAD_IMPLEMENTATION__
#define new    new(__FILE__, __LINE__)
#endif

class _leak_detector {
public:
    static unsigned int callCount;

    _leak_detector() noexcept {
        ++callCount;
    }

    ~_leak_detector() noexcept {
        if (--callCount == 0)
            LeakDetector();
    }

private:
    static unsigned int LeakDetector() noexcept;
};

static _leak_detector _exit_counter;
#endif //PLAY_WITH_ALGO_LEAKDETECTOR_H
