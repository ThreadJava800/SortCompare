# Sortings comparison
> I tested the most popular sortings to see which one is faster:
1) Bubble sort    O(n^2)
2) Selection sort O(n^2)
3) Insertion sort O(n^2)
4) QSort (with different pivots) ~O(n*log(n))
5) Merge sort O(n * log(n))
6) LSD sort O(n)

> I used g++ without any optimisations (such as -o3 and etc.)

Here are some charts:

![alt text](https://github.com/ThreadJava800/SortCompare/blob/main/fastSortCmp.png)

![alt text](https://github.com/ThreadJava800/SortCompare/blob/main/qsortCmp.png)

So as we can see, [LSD](https://github.com/ThreadJava800/SortCompare/blob/main/lsd.cpp) has the best time asymptotics, but mind that it uses a lot of extra memory. And [merge sort](https://github.com/ThreadJava800/SortCompare/blob/main/mergeSort.cpp) is more or less faster that [quickSort](https://github.com/ThreadJava800/SortCompare/blob/main/quickSort.cpp).

I personally was surprised to figure out that quickSort is not as 'quick' as it is considered to be, so I would definetely use merge sort in my future projects.