#ifndef CONTROL_H
#define CONTROL_H

#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

std::vector<int> generateArr(int amount);

//-------------QUADRATIC SORTS----------------//
void insertionSort(std::vector<int>* vec);
void bubbleSort   (std::vector<int>* vec);
void selectionSort(std::vector<int>* vec);

//-------------QUICK SORT--------------------//
void mqSort(std::vector<int>* vec, size_t l, size_t r, 
            int (*func)(std::vector<int>* vec, size_t, size_t));

//-------------MERGE SORT--------------------//
int* mergeSort(int* arr, int* buffer, size_t l, size_t r);

//------------- LSD SORT --------------------//
void lsdSort(int* arr, int* buffer, int* cntArr, int size);

std::vector<int> generateArr(int amount) {
    std::vector<int> vec;

    srand((unsigned) time(NULL));

    for (int i = 0; i < amount; i++) {
        int random = rand() % 150000;                // generating ramdom value
        vec.push_back(random);
    }

    return vec;
}

#endif