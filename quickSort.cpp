#include "control.h"

void _bubbleSort(std::vector<int>* vec, size_t start, size_t end, size_t blockCount) {
    for (size_t i = 0; i < end - start + 1; i += blockCount) {
        for (size_t j = start + blockCount; j < end - i; j += blockCount) {
            if ((*vec)[j] > (*vec)[j + 1]) {
                std::swap((*vec)[j], (*vec)[j - blockCount]);
            }
        }
    }
}

void mqSort(std::vector<int>* vec, size_t l, size_t r, 
            int (*func)(std::vector<int>* vec, size_t, size_t)) {

    int i = l, j = r;
    int pivot = func(vec, l, r);

    while (i <= j) {

        while ((*vec)[i] < pivot) {
            i++;
        }
        while ((*vec)[j] > pivot) {
            if (j != 0) j--;
        }

        if (i <= j) {
            std::swap((*vec)[i], (*vec)[j]);

            i++;
            if (j != 0) j--;
        }
    }

    if (l < j) mqSort(vec, l, j, func);
    if (i < r) mqSort(vec, i, r, func);
}

int med3(std::vector<int>* vec, size_t val1, size_t val2) {
    size_t centerInd = (val1 + val2) / 2;

    // a > b > c
    if ((*vec)[val1] > (*vec)[centerInd]) {
        if ((*vec)[centerInd] > (*vec)[val2]) {
            return (*vec)[centerInd];
        }
        return (*vec)[val2 - 1];
    }

    // b > a > c
    if ((*vec)[centerInd] > (*vec)[val1]) {
        if ((*vec)[val1] > (*vec)[val2]) {
            return (*vec)[val1];
        }
        return (*vec)[val2 - 1];
    }

    // c > a > b
    if ((*vec)[val2] > (*vec)[val1]) {
        if ((*vec)[val1] > (*vec)[centerInd]) {
            return (*vec)[val1];
        }
    }
    return (*vec)[centerInd];
}

int center(std::vector<int>* vec, size_t val1, size_t val2) {
    return (*vec)[(val1 + val2) / 2];
}

int randInd(std::vector<int>* vec, size_t val1, size_t val2) {
    size_t randomIndex = (rand() % (val2 - val1)) + val1;
    if (randomIndex == val2) randomIndex--;

    return (*vec)[randomIndex];
}

int medMedHelper(std::vector<int>* vec, size_t val1, size_t val2, size_t blockCount) {
    for (size_t i = val1 + blockCount * 5; i <= val2; i += blockCount * 5) {
        if (i + blockCount * 5 - 1 >= val2) {
            _bubbleSort(vec, i, val2, blockCount);
        } else {
            _bubbleSort(vec, i, i + blockCount * 5, blockCount);
        }
    }

    if ((val2 - val1) / (blockCount * 5) <= 1) {
        if (val1 + (val2 - val1) / 2 == val2) {
            return (*vec)[val1 + (val2 - val1) / 2 - 1];
        }
        return (*vec)[val1 + (val2 - val1) / 2];
    }

    return medMedHelper(vec, val1, val2, blockCount * 5);
}

int medMed(std::vector<int>* vec, size_t val1, size_t val2) {
    return medMedHelper(vec, val1, val2, 1);
}

using namespace std::chrono;

int main() {
    std::ofstream sortMed3;
    sortMed3.open("sortMed3.txt");

    std::ofstream sortCent;
    sortCent.open("sortCent.txt");

    std::ofstream sortRand;
    sortRand.open("sortRand.txt");

    std::ofstream sortMedMed;
    sortMedMed.open("sortMedMed.txt");

    srand((unsigned) time(NULL));

    // std::vector<int> values = generateArr(1000);
    // for (int i = 0; i < values.size(); i++) {
    //     fprintf(stderr, "%d ", values[i]);
    // }
    // fprintf(stderr, "\nHEY: %d \n", medMed(&values, 0, values.size() - 1));
    // mqSort(&values, 0, values.size() - 1, medMed);
    // for (int i = 0; i < values.size(); i++) {
    //     fprintf(stderr, "%d ", values[i]);
    // }

    for (int i = 1000; i <= 10000000; i += 100000) {
        std::vector<int> values = generateArr(i);
        std::vector<int> toSort = values;

        // MEDIAN OF 3
        auto start = high_resolution_clock::now();
        mqSort(&toSort, 0, values.size() - 1, med3);
        auto end   = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        sortMed3 << i << ' ' << duration.count() << '\n';

        // CENTER
        toSort = values;
        start = high_resolution_clock::now();
        mqSort(&toSort, 0, values.size() - 1, center);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        sortCent << i << ' ' << duration.count() << '\n';

        // RANDOM
        toSort = values;
        start = high_resolution_clock::now();
        mqSort(&toSort, 0, values.size() - 1, randInd);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        sortRand << i << ' ' << duration.count() << '\n';

        sortMed3.flush();
        sortCent.flush();
        sortRand.flush();

        toSort = values;
        start = high_resolution_clock::now();
        mqSort(&toSort, 0, values.size() - 1, medMed);
        end   = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(end - start);
        sortMedMed << i << ' ' << duration.count() << '\n';
        sortMedMed.flush();
    }


    sortMed3.close();
    sortCent.close();
    sortRand.close();
    sortMedMed.close();

    return 0;
}