#! -*- Encoding: Latin-1 -*-

import random
import time

COUNTING_SORT_NR_ELEMENTS = 1000000
COUNTING_SORT_MAX_ITEM = 10000

TIMEIT_PATTERN_INT = "%30s %10d %10d %10d"
TIMEIT_PATTERN_STR = "%30s %10s %10s %10s"

def IsSorted(A):
    for index, item in enumerate(A):
        if index == 0:
            expected = item
        elif item < expected:
            return False

    return True

def TestSortMethod(array, closure, name, repeat = 10):
    total_time = 0
    max_time = 0
    min_time = 0

    for r in range(repeat):
        random.shuffle(array)
        assert not IsSorted(array)
        elapsed_time = time.time()
        closure(array)
        elapsed_time = time.time() - elapsed_time
        assert IsSorted(array)
        if r == 0:
            total_time = min_time = max_time = elapsed_time
        
        else:
            total_time += elapsed_time
            if elapsed_time < min_time:
                min_time = elapsed_time

            if elapsed_time > max_time:
                max_time = elapsed_time

    average_time = total_time / repeat

    as_ms = lambda x: int(round(x*1000))

    print(TIMEIT_PATTERN_INT % (name, as_ms(average_time), as_ms(max_time), as_ms(min_time), ))

def counting_sort(A, n):

    # create counters initialized to zero
    frequencies = [0] * n

    # count each item</em>
    for value in A:
        frequencies[value] += 1

    # recreate sorted array</em>
    writepos = 0
    for value, count in enumerate(frequencies):
        for i in range(count):
            A[writepos] = value
            writepos += 1

    return A

def test_counting_sort():
    print("--- Counting Sort in Python ---")
    print("- Sample size: %r integers in the range [0..%r]" % (COUNTING_SORT_NR_ELEMENTS, COUNTING_SORT_MAX_ITEM-1, ))
    print("")
    print(TIMEIT_PATTERN_STR % ("Method", "Average", "Max", "Min", ))
    print("-" * 100)

    array = [random.randrange(0, COUNTING_SORT_MAX_ITEM) for i in range(COUNTING_SORT_NR_ELEMENTS)]

    TestSortMethod(array, lambda a: a.sort(), "builtin sort")
    TestSortMethod(array, lambda a: counting_sort(a, len(a)), "counting sort")

if __name__ == "__main__":
    test_counting_sort()