#include "control.h"

void insertionSort(int* vec, size_t n) {
    for (size_t i = 1; i < n; i++) {
        size_t piv = i - 1;

        while (vec[piv] > vec[piv + 1])
        {
            std::swap(vec[piv], vec[piv + 1]);
            --piv;
        }
    }
}

void insertionSortDel(int* vec, size_t n) {
    for (size_t i = 0; i < n; i++) {
        long long binI = 0, binJ = i - 1;
        size_t elem = vec[i];

        while (binI <= binJ) {
            size_t piv = binI + (binJ - binI) / 2;

            if (vec[piv] == elem) {
                break;
            }

            if (vec[piv] <= elem) {
                binI = piv + 1;
            } else {
                binJ = piv - 1;
            }
        }

        size_t temp = vec[i];
        int cnt1 = 0, cnt2 = i - binI - 1;
        for (int j = i; j >= binI + 1; j--) {
            vec[j - cnt2] = vec[binI + 1 + cnt1];

            cnt2--;
            cnt1++;
        }
    }
}

void insertionSortBin(int* vec, size_t n) {
    for (size_t i = 0; i < n; i++) {
        long long binI = 0, binJ = i - 1;
        size_t elem = vec[i];

        while (binI <= binJ) {
            size_t piv = binI + (binJ - binI) / 2;

            if (vec[piv] == elem) {
                break;
            }

            if (vec[piv] <= elem) {
                binI = piv + 1;
            } else {
                binJ = piv - 1;
            }
        }

        for (size_t ind = i; ind > binI; ind--) {
            std::swap(vec[ind], vec[ind - 1]);
        }
    }
}

int* _mergeSort(int* arr, int* buffer, size_t l, size_t r) {

    if (l == r) {
        buffer[l] = arr[l];
        return buffer;
    }

    int middle = (l + r) / 2;
    int* lSide = _mergeSort(arr, buffer, l, middle);
    int* rSide = _mergeSort(arr, buffer, middle + 1, r);

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

// int* mergeSort(int* arr, size_t n) {
//     if (n <= SWITCH_SORT) {
//         return insertionSortBin(arr, n);
//     }

//     int* buffer = (int*) calloc(n, sizeof(int));
//     int* res    = _mergeSort(arr, buffer, 0, n - 1);
//     free(buffer);

//     return res;
// }

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
    sortMerge.open("sortMergeCmp.txt");

    std::ofstream ins;
    ins.open("insCmp.txt");

    std::ofstream del;
    del.open("delCmp.txt");

    std::ofstream bin;
    bin.open("binCmp.txt");

    srand((unsigned) time(NULL));

    for (int i = 1; i <= 100; i++) {
        int* values  = generateIntArr(i);
        int* valCopy = (int*) calloc(i, sizeof(int));
        int* buffer = (int*) calloc(i, sizeof(int));

        auto start = high_resolution_clock::now();
        for (int m = 0; m < 1000; m++) {
            valCopy      = (int*) memcpy(valCopy, values, i * sizeof(int));
            _mergeSort(valCopy, buffer, 0, i - 1);
        }
        auto end   = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start);
        sortMerge << i << ' ' << duration.count() / 100 << '\n';

        start = high_resolution_clock::now();
        for (int m = 0; m < 1000; m++) {
            valCopy      = (int*) memcpy(valCopy, values, i * sizeof(int));
            insertionSort(valCopy, i);
        }
        end   = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);
        ins << i << ' ' << duration.count() / 100 << '\n';

        start = high_resolution_clock::now();
        for (int m = 0; m < 1000; m++) {
            valCopy      = (int*) memcpy(valCopy, values, i * sizeof(int));
            insertionSortBin(valCopy, i);
        }
        end   = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);
        bin << i << ' ' << duration.count() / 100 << '\n';

        valCopy      = (int*) memcpy(valCopy, values, i * sizeof(int));
        start = high_resolution_clock::now();
        for (int m = 0; m < 1000; m++) {
            valCopy      = (int*) memcpy(valCopy, values, i * sizeof(int));
            insertionSortDel(valCopy, i);
        }
        end   = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);
        del << i << ' ' << duration.count() / 100 << '\n';


        sortMerge.flush();
        ins.flush();
        del.flush();
        bin.flush();

        free(values);
        free(buffer);
    }


    sortMerge.close();
    ins.close();
    del.close();
    bin.close();

    return 0;
}