#include <iostream>
#include <cstdlib>
#include <thread>
#include "Profiler.hpp"
using namespace std;

Profiler* gProfiler = new Profiler();

void test1(){

vector<int> unsortedVector;
gProfiler->EnterSection("interweaveTest");
for(int i = 0; i < 1000; i++){
    gProfiler->EnterSection("Array1");
    unsortedVector.push_back(rand() % 1000);
    gProfiler->ExitSection("Array1");
}
    bool swapped;
    int n = unsortedVector.size();
    
    // Outer loop: keeps iterating until the vector is sorted
    gProfiler->EnterSection("BubbleSort1");
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
        gProfiler->ExitSection("interweaveTest");
        n--;  // Reduce the range to optimize since the largest element gets placed at the end in each pass
    } while (swapped); 
    
    gProfiler->ExitSection("BubbleSort1");

};
void test2(){
gProfiler->EnterSection("interweaveTest2");

    vector<int> unsortedVector;

    for(int i = 0; i < 1000; i++){
        gProfiler->EnterSection("Array2");
        unsortedVector.push_back(rand() % 1000);
        gProfiler->ExitSection("Array2");
    }
    
    
    gProfiler->EnterSection("BubbleSort2");
    int n = unsortedVector.size();
        for (int i = 0; i < n; i++) {  // Outer loop
        for (int j = 0; j < n - 1; j++) {  // Inner loop
            gProfiler->EnterSection("InnerLoop2");
            // Compare adjacent elements and swap if out of order
            if (unsortedVector[j] > unsortedVector[j + 1]) {
                std::swap(unsortedVector[j], unsortedVector[j + 1]);
            }
            gProfiler->ExitSection("InnerLoop2");
        }
        gProfiler->ExitSection("interweaveTest2");
        // Even when sorted, this algorithm does not optimize by stopping early
    }
    gProfiler->ExitSection("BubbleSort2");
}

int main()
{

test1(); //efficient bubble sort
test2(); //ineffeicient bubble sort
    gProfiler->printStats();
    gProfiler->printStatsToCSV("ProfilerStats.csv");
    gProfiler->printStatsToJSON("ProfilerStats.json");

    return 0;
}