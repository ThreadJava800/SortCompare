#include "control.h"

int* mergeSort(int* arr, int* buffer, size_t l, size_t r) {
    if (l == r) {
        buffer[l] = arr[l];
        return buffer;
    }

    int middle = (l + r) / 2;
    int* lSide = mergeSort(arr, buffer, l, middle);
    int* rSide = mergeSort(arr, buffer, middle + 1, r);

    int* target = NULL;
    if (lSide == arr) {
        target = buffer;
    } else {
        target = arr;
    }

    int curR = middle + 1, curL = l;
    for (int i = l; i <= r; i++) {
        if (curL <= middle && curR <= r) {

            if (lSide[curL] <= rSide[curR]) {
                target[i] = lSide[curL++];
            } else {
                target[i] = rSide[curR++];
            }

        } else if (curL <= middle) {
            target[i] = lSide[curL++];
        } else {
            target[i] = rSide[curR++];
        }
    }

    return target;
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
    std::ofstream sortMerge;
    sortMerge.open("sortMerge.txt");

    srand((unsigned) time(NULL));

    for (int i = 1000; i <= 10000000; i += 100000) {
        int* values = generateIntArr(i);
        int* buffer = (int*) calloc(i, sizeof(int));

        auto start = high_resolution_clock::now();
        mergeSort(values, buffer, 0, i - 1);
        auto end   = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        sortMerge << i << ' ' << duration.count() << '\n';

        sortMerge.flush();

        free(values);
        free(buffer);
    }


    sortMerge.close();

    return 0;
}