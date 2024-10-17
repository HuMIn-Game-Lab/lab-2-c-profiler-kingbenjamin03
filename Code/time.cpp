#include "time.hpp"
#include <chrono>
using namespace std;



double GetCurrentTimeSecond()
{
    static auto start = chrono::high_resolution_clock::now();
    auto now = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::duration<double>>(now-start).count();
}