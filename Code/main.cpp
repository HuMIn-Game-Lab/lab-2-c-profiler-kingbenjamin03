#include <iostream>
#include <cstdlib>
#include <thread>
#include "Profiler.hpp"
using namespace std;

Profiler* gProfiler = new Profiler();

void test1(){

vector<int> unsortedVector;
gProfiler->EnterSection("intervweaveTest");
for(int i = 0; i < 1000; i++){
    unsortedVector.push_back(rand() % 1000);
}
    bool swapped;
    int n = unsortedVector.size();
    
    // Outer loop: keeps iterating until the vector is sorted
    gProfiler->EnterSection("BubbleSort");
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            gProfiler->EnterSection("InnerLoop");
            if (unsortedVector[i] > unsortedVector[i + 1]) {
                // Swap adjacent elements if they are in the wrong order
                std::swap(unsortedVector[i], unsortedVector[i + 1]);
                swapped = true;
            }
            gProfiler->ExitSection("InnerLoop");
        }
        n--;  // Reduce the range to optimize since the largest element gets placed at the end in each pass
    } while (swapped); 
    gProfiler->ExitSection("interweaveTest");
    gProfiler->ExitSection("BubbleSort");

};


int main()
{

    // Profiler* p = new Profiler();
    // p->EnterSection("mTest");
    // p->EnterSection("interweaveTest");
    // vector<int> test;
    // for(int i = 0; i < 5; i++){
    //     p->EnterSection("iTest");
    //     test.push_back(i);
    //     for(int j = 0; j <3; j++){
    //         p->EnterSection("jTest");
    //         test.push_back(j);
    //         p->ExitSection("jTest");
    //     }
    //     p->ExitSection("interweaveTest");
    //     p->ExitSection("iTest");
    // }
    
    // p->ExitSection("mTest");
    // p->printStats();
    // delete p;
    for(int i = 0; i < 10; i++){
        test1();
    }
    gProfiler->printStats();




    return 0;
}