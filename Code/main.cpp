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
    enterSection("Array1");
    unsortedVector.push_back(rand() % 1000);
    exitSection("Array1");
}
    bool swapped;
    int n = unsortedVector.size();
    
    // Outer loop: keeps iterating until the vector is sorted
    enterSection("BubbleSort1");
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            enterSection("InnerLoop");
            if (unsortedVector[i] > unsortedVector[i + 1]) {
                // Swap adjacent elements if they are in the wrong order
                std::swap(unsortedVector[i], unsortedVector[i + 1]);
                swapped = true;
            }
            exitSection("InnerLoop");
            
        }
        exitSection("interweaveTest");
        n--;  // Reduce the range to optimize since the largest element gets placed at the end in each pass
    } while (swapped); 
    
    exitSection("BubbleSort1");

};
void test2(){
enterSection("interweaveTest2");

    vector<int> unsortedVector;

    for(int i = 0; i < 1000; i++){
        enterSection("Array2");
        unsortedVector.push_back(rand() % 1000);
        exitSection("Array2");
    }
    
    
    enterSection("BubbleSort2");
    int n = unsortedVector.size();
        for (int i = 0; i < n; i++) {  // Outer loop
        for (int j = 0; j < n - 1; j++) {  // Inner loop
            enterSection("InnerLoop2");
            // Compare adjacent elements and swap if out of order
            if (unsortedVector[j] > unsortedVector[j + 1]) {
                std::swap(unsortedVector[j], unsortedVector[j + 1]);
            }
            exitSection("InnerLoop2");
        }
        exitSection("interweaveTest2");
        // Even when sorted, this algorithm does not optimize by stopping early
    }
    exitSection("BubbleSort2");
}
void test3(){
    for(int i = 0; i<10; i++){
        enterSection("Test3");
        //cout<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        exitSection("Test3");
    }
    
}
void test4()
{
    enterSection("Test4");
    enterSection("Test4.1");
    int x = 2;
    if (x == 23) {
        exitSection("Test4");
    }
    else {
        exitSection("Test4.1");
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    exitSection("Test4");
    exitSection("Test4.1");
}

int main()
{

test1(); //efficient bubble sort
test2(); //ineffeicient bubble sort
test3(); //test3 runs for 1 second
test4(); //test4 interweaving test
PrintStats();
PrintStatsToCSV("ProfilerStats.csv");
//PrintStatsToJSON("ProfilerStats.json");

    return 0;
}