#!/usr/bin/env python3

from sys import argv
from random import randint
import os

N = 10
INT_LIMIT = 1000
MAX_LENGTH = 1000


def main():
    test_map = {
        '0': run_general_test,
        '1': run_quicksort_test,
        '2': run_heapsort_test
    }
    test_num = argv[1]
    for i in range(1, N+1):
        test_func = test_map.get(test_num, lambda: None)
        test_func()
        print(f'test {test_num} pass {i} OK')


def run_general_test():
    test_array = [
        randint(-INT_LIMIT, INT_LIMIT)
        for _ in range(randint(1, MAX_LENGTH))]
    test_input = '{n}\\n{array}'.format(
        n=len(test_array),
        array=' '.join(str(x) for x in test_array))
    cmd = 'echo -e "{test_input}" | ./a.out'.format(test_input=test_input)
    user_out = os.popen(cmd).read().strip()
    user_array = [int(x) for x in user_out.split()]
    expected_array = sorted(test_array)

    assert user_array == expected_array, 'expected {}, got {}'.format(
            expected_array, user_array)


def run_quicksort_test():

    def partition(arr, low, high):
        i = low - 1
        pivot = arr[(high-low)//2]
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        return i + 1

    def quicksort(arr, low, high):
        expected_iterations.append(test_array.copy())
        if low < high:
            pi = partition(arr, low, high)
            quicksort(arr, low, pi-1)
            quicksort(arr, pi + 1, high)


    test_array = [
        randint(-INT_LIMIT, INT_LIMIT)
        for _ in range(randint(1, MAX_LENGTH))]   
    test_input = '{n}\\n{array}'.format(
        n=len(test_array),
        array=' '.join(str(x) for x in test_array))
    cmd = 'echo -e "{test_input}" | ./a.out'.format(test_input=test_input)
    os.popen(cmd).read()
    
    expected_iterations = list()
    quicksort(test_array, 0, len(test_array)-1)

    with open('quicksort.log') as f:
        user_iterations = [[int(x) for x in line.split()] for line in f.readlines()]

    assert user_iterations == expected_iterations, 'quicksort mismatch'


def run_heapsort_test():

    def heapify(arr, n, i):
        largest = i
        l = 2 * i + 1
        r = 2 * i + 2
        if l < n and arr[i] < arr[l]:
            largest = l
        if r < n and arr[largest] < arr[r]:
            largest = r
        if largest != i:
            arr[i],arr[largest] = arr[largest],arr[i]
            expected_iterations.append(test_array.copy())
            heapify(arr, n, largest)

    def heapsort(arr):
        expected_iterations.append(test_array.copy())
        n = len(arr)
        for i in range(n, -1, -1):
            heapify(arr, n, i)
        for i in range(n-1, 0, -1):
            arr[i], arr[0] = arr[0], arr[i]
            expected_iterations.append(test_array.copy())
            heapify(arr, i, 0)


    test_array = [
        randint(-INT_LIMIT, INT_LIMIT)
        for _ in range(randint(1, MAX_LENGTH))]
    
    test_input = '{n}\\n{array}'.format(
        n=len(test_array),
        array=' '.join(str(x) for x in test_array))

    cmd = 'echo -e "{test_input}" | ./a.out'.format(test_input=test_input)
    os.popen(cmd).read()

    expected_iterations = list()
    heapsort(test_array)

    with open('heapsort.log') as f:
        user_iterations = [[int(x) for x in line.split()] for line in f.readlines()]

    assert user_iterations == expected_iterations, 'heapsort mismatch'


if __name__ == "__main__":
    main()
    
