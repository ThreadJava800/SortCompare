#include "control.h"

int mask = 255;

void lsdSort(int* arr, int* buffer, int* cntArr, int size) {
    for (int i = 0; i < 8; i++) {
       for (int j = 0;  j < 256; j++) {
            cntArr[j] = 0;
       }

       for (int j = 0; j < size; j++) {
            int val = ((arr[j] & mask) >> (8 * i));
            cntArr[val]++;
       }

       int count = 0;
       for (int j = 0; j < 256; j++) {
            int tmp = cntArr[j];
            cntArr[j] = count;
            count += tmp;
       }
       for (int j = 0; j < size; j++) {
            int val = ((arr[j] & mask) >> (8 * i));
            buffer[cntArr[val]] = arr[j];
            cntArr[val]++;
       }

       mask *= 256;
       for (int j = 0; j < size; j++) {
             arr[j] = buffer[j];
       }
    }
}

int* generateIntArr(int amount) {
    srand((unsigned) time(NULL));

    int* result = (int*) calloc(amount, sizeof(int));

    for (int i = 0; i < amount; i++) {
        int random = rand() % 150000;                // generating ramdom value
        result[i] = random;
    }

    return result;
}

using namespace std::chrono;

int main() {
    std::ofstream sortLsd;
    sortLsd.open("sortLsd.txt");

    srand((unsigned) time(NULL));

    int* values = generateIntArr(10);
    int* buffer = (int*) calloc(10, sizeof(int));
    int* cntArr = (int*) calloc(256, sizeof(int));

    for (int i = 1000; i <= 10000000; i += 100000) {
        int* values = generateIntArr(i);
        int* buffer = (int*) calloc(i, sizeof(int));
        int* cntArr = (int*) calloc(256, sizeof(int));

        auto start = high_resolution_clock::now();
        lsdSort(values, buffer, cntArr, i);
        auto end   = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        sortLsd << i << ' ' << duration.count() << '\n';

        sortLsd.flush();

        free(values);
        free(buffer);
        free(cntArr);
    }


    sortLsd.close();

    return 0;
}