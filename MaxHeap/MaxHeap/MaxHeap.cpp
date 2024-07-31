// MaxHeap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>  /*this will allow us to use the built in heap functions for a heap class*/
#include <vector>
#include <time.h>


using namespace std;

int main() {
    
    /*array implementation*/
    srand(time(NULL));
    int myints[100] = {};
    int secondArray[50] = {}; /*second array to hold first removed ints*/
    int thirdArray[50] = {};  /*third array to hold second set of ints*/
    
    
    for (int x = 0; x < 100; x++)
    {
        myints[x] = rand() % 10000;
        
    }  

    printf("\nElements of the array::");
    for (int x = 0; x < 100; x++)
    {
        printf("\nElement number %d::%d", x + 1, myints[x]);
    }
    for (int x = 0; x < 50; x++)
    {
        secondArray[x] = myints[x];
    }
    for (int x = 0; x < 50; x++)
    {
        thirdArray[x] = myints[x+50];
    }
    
    printf("\nElements of the new array::");
    for (int x = 0; x < 50; x++)
    {
        printf("\nElement number %d::%d", x + 1, thirdArray[x]);
    }

    /*heap creation utilizing built in heap creation tools in C++ algorithm*/
    vector<int> v(myints, myints + 100);

    make_heap(v.begin(), v.end());
    cout << "\nInitial max heap: " << v.front() << '\n';

    cout << "\nInitial unsorted heap: \n";
    for (unsigned x = 0; x < v.size(); x++)
        cout << ' ' << v[x];

    sort_heap(v.begin(), v.end());
    cout << "\nFinal sorted range:";
    for (unsigned x = 0; x < v.size(); x++)
        cout << ' ' << v[x];
    cout << "\n";
    
    vector<int> y(thirdArray, thirdArray + 50);
    make_heap(y.begin(), y.end());
    cout << "\nInitial unsorted heap with 50 ints removed from beginning: \n";
    for (unsigned x = 0; x < y.size(); x++)
        cout << ' ' << y[x];

    sort_heap(y.begin(), y.end());

    cout << "\nFinal sorted range with first 50 ints removed:";
    for (unsigned x = 0; x < 50; x++)
        cout << ' ' << y[x];

    cout << '\n';
     
}

/*between the two implementations, the array version was far simpler to create and make.  However, the C++ algorithm heap creation was incredibly useful and made heap creation much easier*/