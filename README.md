# Sortings comparison
> I tested the most popular sortings to see which one is faster:
1) [Bubble sort    O(n^2)](https://github.com/ThreadJava800/SortCompare/blob/main/quadratics.cpp#L15)
2) [Selection sort O(n^2)](https://github.com/ThreadJava800/SortCompare/blob/main/quadratics.cpp#L26)
3) [Insertion sort O(n^2)](https://github.com/ThreadJava800/SortCompare/blob/main/quadratics.cpp#L3)
4) [QSort (with different pivots) ~O(n*log(n))](https://github.com/ThreadJava800/SortCompare/blob/main/quickSort.cpp#L13)
5) [Merge sort O(n * log(n))](https://github.com/ThreadJava800/SortCompare/blob/main/mergeSort.cpp#L3)
6) [LSD sort O(n)](https://github.com/ThreadJava800/SortCompare/blob/main/lsd.cpp)

> I used g++ without any optimisations (such as -o3 and etc.)

Here are some charts:

> Insertion (2) = insertion sort with binary search and [optimisation without swappings](https://github.com/ThreadJava800/SortCompare/blob/main/quadratics.cpp#L15).

![Fast sortings](https://github.com/ThreadJava800/SortCompare/blob/main/fastSorts.png)

![Quick sortings](https://github.com/ThreadJava800/SortCompare/blob/main/qsortCmp.png)

![Quadratic sorts](https://github.com/ThreadJava800/SortCompare/blob/main/quadrSort.png)

![Merge vs insertion](https://github.com/ThreadJava800/SortCompare/blob/main/insMerge.png)

So, as we can see insertion (2) works faster with arrays (<= 20 elems) than merge. 

On the graph below you can see comparison of all sortings (quadratic sorts has amount of elements in range [1000, 10^5] and other sortings have [10000, 10^7] elements). It shows us how quadratic sortings unefficient.

![alt text](https://github.com/ThreadJava800/SortCompare/blob/main/allSort.png)



So as we can see, [LSD](https://github.com/ThreadJava800/SortCompare/blob/main/lsd.cpp) has the best time asymptotics, but mind that it uses a lot of extra memory. And [merge sort](https://github.com/ThreadJava800/SortCompare/blob/main/mergeSort.cpp) is more or less faster that [quickSort](https://github.com/ThreadJava800/SortCompare/blob/main/quickSort.cpp) but still uses extra memory (but less than lsd).

I personally was surprised to figure out that quickSort is not as 'quick' as it is considered to be, it is just the fastet sorting algorithm that doesn't use additional memory. So I think, I will look forward to using it in most events.