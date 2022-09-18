//
//  LeakDetector.hpp
//  LeakDetector
//
#ifndef __LEAK_DETECTOR__
#define __LEAK_DETECTOR__

void* operator new(size_t _size, char *_file, unsigned int _line);
void* operator new[](size_t _size, char *_file, unsigned int _line);
// 此处宏的作用在 LeakDetector.cpp 中说明
#ifndef __NEW_OVERLOAD_IMPLEMENTATION__
#define new	new(__FILE__, __LINE__)
#endif

class _leak_detector
{
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

#endif