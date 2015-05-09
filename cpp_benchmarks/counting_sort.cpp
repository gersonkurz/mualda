// cpp_benchmarks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define COUNTING_SORT_NR_ELEMENTS 1000000
#define COUNTING_SORT_MAX_ITEM 10000

const char* TIMEIT_PATTERN_INT = "%30s %10d %10d %10d\n";
const char* TIMEIT_PATTERN_STR = "%30s %10s %10s %10s\n";

bool IsSorted(const std::vector<int>& a) {
    
    int expected = a[0];
    for (size_t i = 1, imax = a.size(); i < imax; ++i) {
        if (a[i] < expected) {
            return false;
        }
        expected = a[i];
    }
    return true;
}

void RandomizeArray(std::vector<int>& a) {
    for (size_t i = 0, imax = a.size(); i < imax; ++i) {
        a[i] = rand() % COUNTING_SORT_MAX_ITEM;
    }
}

void CreateEmptyArrayOfLength(std::vector<int>& a, size_t size)
{
    a.resize(size);
    memset(&a[0], 0, sizeof(int) * size);
}


void CreateArrayWithRandomNumbers(std::vector<int>& a, size_t size)
{
    a.resize(size);
    memset(&a[0], 0, sizeof(int) * size);
}

int __cdecl cstyle_cmpfunc(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void CStyleQSort(std::vector<int>& A) {
    qsort(&A[0], A.size(), sizeof(int), &cstyle_cmpfunc);
}

void CountingSort(std::vector<int>& a) {
    std::vector<int> frequencies;
    CreateEmptyArrayOfLength(frequencies, COUNTING_SORT_MAX_ITEM);

    for (size_t i = 0, imax = a.size(); i < imax; ++i) {
        frequencies[a[i]]++;
    }

    // repopulate array
    int writepos = 0;
    for (size_t i = 0, imax = frequencies.size(); i < imax; ++i) {
        for (size_t j = 0, jmax = frequencies[i]; j < jmax; ++j) {
            a[writepos++] = i;
        }
    }

}

void TestSortMethod(std::vector<int>& A, void(*SortMethod)(std::vector<int>&), const char* name, int repeatCount = 10) {

    DWORD totalTime = 0;
    DWORD maxTime = 0;
    DWORD minTime = 0;

    for (int r = 0; r < repeatCount; ++r) {
        RandomizeArray(A);
        assert(!IsSorted(A));
        DWORD startTime = GetTickCount();
        (*SortMethod)(A);
        DWORD elapsedTime = GetTickCount() - startTime;
        assert(IsSorted(A));
        if (r == 0) {
            totalTime = maxTime = minTime = elapsedTime;
        }
        else {
            totalTime += elapsedTime;
            if (elapsedTime < minTime)
                minTime = elapsedTime;
            if (elapsedTime > maxTime)
                maxTime = elapsedTime;
        }
    }

    DWORD averageTime = totalTime / repeatCount;
    printf(TIMEIT_PATTERN_INT, name, averageTime, maxTime, minTime);
}

void TestCountingSort()
{
    printf("--- Counting Sort in C++ ---\n");
    printf("- Sample size: %d integers in the range [0..9999]\n", COUNTING_SORT_NR_ELEMENTS, COUNTING_SORT_MAX_ITEM-1);
    printf("\n");
    printf(TIMEIT_PATTERN_STR, "Method", "Average", "Max", "Min");
    printf("----------------------------------------------------------------------------------------------------\n");

    std::vector<int> A;
    CreateEmptyArrayOfLength(A, COUNTING_SORT_NR_ELEMENTS);
    srand((unsigned int)time(0));

    TestSortMethod(A, &CStyleQSort, "builtin sort");
    TestSortMethod(A, &CountingSort, "c-style qsort");
}