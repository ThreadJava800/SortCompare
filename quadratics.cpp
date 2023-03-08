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

    // std::vector<int> values = generateArr(10);
    // for (int i = 0; i < values.size(); i++) {
    //     printf("%d ", values[i]);
    // }
    // printf("\n");
    // bubbleSort(&values);
    // for (int i = 0; i < values.size(); i++) {
    //     printf("%d ", values[i]);
    // }
 
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

        // WRITING DATA
        insertion.flush();
        bubble.flush();
        selection.flush();
    }


    insertion.close();
    bubble.close();
    selection.close();

    return 0;
}