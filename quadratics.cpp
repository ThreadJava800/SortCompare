#include "control.h"

void insertionSort(std::vector<int>* vec) {
    for (size_t i = 1; i < vec->size(); i++) {
        size_t piv = i - 1;

        while ((*vec)[piv] > (*vec)[piv + 1])
        {
            std::swap((*vec)[piv], (*vec)[piv + 1]);
            --piv;
        }
    }
}

void insertionSortDel(std::vector<int>* vec) {
    size_t  vecSize = vec->size();

    for (size_t i = 0; i < vecSize; i++) {
        long long binI = 0, binJ = i - 1;
        size_t elem = (*vec)[i];

        while (binI <= binJ) {
            size_t piv = binI + (binJ - binI) / 2;

            if ((*vec)[piv] == elem) {
                break;
            }

            if ((*vec)[piv] <= elem) {
                binI = piv + 1;
            } else {
                binJ = piv - 1;
            }
        }

        size_t temp = (*vec)[i];
        int cnt1 = 0, cnt2 = i - binI - 1;
        for (int j = i; j >= binI + 1; j--) {
            (*vec)[j - cnt2] = (*vec)[binI + 1 + cnt1];

            cnt2--;
            cnt1++;
        }
    }
}

void insertionSortBin(std::vector<int>* vec) {
    size_t vecSize = vec->size();
    for (size_t i = 0; i < vecSize; i++) {
        long long binI = 0, binJ = i - 1;
        size_t elem = (*vec)[i];

        while (binI <= binJ) {
            size_t piv = binI + (binJ - binI) / 2;

            if ((*vec)[piv] == elem) {
                break;
            }

            if ((*vec)[piv] <= elem) {
                binI = piv + 1;
            } else {
                binJ = piv - 1;
            }
        }

        for (size_t ind = i; ind > binI; ind--) {
            std::swap((*vec)[ind], (*vec)[ind - 1]);
        }
    }
}

void bubbleSort   (std::vector<int>* vec) {
    size_t n = vec->size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if ((*vec)[j] > (*vec)[j + 1]) {
                std::swap((*vec)[j], (*vec)[j + 1]);
            }
        }
    }
}

void selectionSort(std::vector<int>* vec) {
    size_t n = vec->size();
    for (size_t i = 0; i < n; i++) {
        size_t mini = i;

        for (size_t j = i + 1; j < n; j++) {
            if ((*vec)[j] < (*vec)[mini]) {
                mini = j;
            }
        }
        if (mini != i) {
            std::swap((*vec)[i], (*vec)[mini]);
        }
    }
}

using namespace std::chrono;

int main() {
    std::ofstream insertion;
    insertion.open("insertion.txt");

    std::ofstream bubble;
    bubble.open("bubble.txt");

    std::ofstream selection;
    selection.open("selection.txt");

    std::ofstream bin;
    bin.open("insertionBin.txt");

    std::ofstream del;
    del.open("insertionDel.txt");
 
    for (int i = 1000; i <= 100000; i += 1000) {
        std::vector<int> values = generateArr(i);
        std::vector<int> toSort = values;

        // INSERTION
        auto start = high_resolution_clock::now();
        insertionSort(&toSort);
        auto end   = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        insertion << i << ' ' << duration.count() << '\n';

        // BUBBLE
        toSort = values;
        start = high_resolution_clock::now();
        bubbleSort(&toSort);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        bubble << i << ' ' << duration.count() << '\n';

        // SELECTION
        toSort = values;
        start = high_resolution_clock::now();
        selectionSort(&toSort);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        selection << i << ' ' << duration.count() << '\n';

        // INSERTION (BIN)
        toSort = values;
        start = high_resolution_clock::now();
        insertionSortBin(&toSort);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        bin << i << ' ' << duration.count() << '\n';

        // INSERTION (DEL)
        toSort = values;
        start = high_resolution_clock::now();
        insertionSortDel(&toSort);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        del << i << ' ' << duration.count() << '\n';

        // WRITING DATA
        insertion.flush();
        bubble.flush();
        selection.flush();
        bin.flush();
        del.flush();
    }


    insertion.close();
    bubble.close();
    selection.close();
    bin.close();
    del.close();

    return 0;
}