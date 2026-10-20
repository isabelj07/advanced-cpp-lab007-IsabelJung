#include "project/recursive_algorithms.h"

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {

// Largest inputs whose results still fit in a 32-bit int.
constexpr int kMaxFactorialInput = 12;  // 12! = 479001600
constexpr int kMaxFibonacciInput = 46;  // fib(46) = 1836311903

void validateFactorialInput(int n) {
    if (n < 0) {
        throw std::invalid_argument("factorial: n must be non-negative");
    }
    if (n > kMaxFactorialInput) {
        throw std::overflow_error("factorial: result does not fit in an int");
    }
}

void validateFibonacciInput(int n) {
    if (n < 0) {
        throw std::invalid_argument("fibonacci: n must be non-negative");
    }
    if (n > kMaxFibonacciInput) {
        throw std::overflow_error("fibonacci: result does not fit in an int");
    }
}

int factorialRecursive(int n) {
    // Base case: 0! = 1! = 1.
    if (n <= 1) {
        return 1;
    }
    // Recursive case: n! = n * (n - 1)!.
    return n * factorialRecursive(n - 1);
}

int fibonacciRecursive(int n) {
    // Base case: fib(0) = 0, fib(1) = 1.
    if (n <= 1) {
        return n;
    }
    // Recursive case: fib(n) = fib(n - 1) + fib(n - 2).
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Searches array left to right (inclusive) for target.
int binarySearchRange(const std::vector<int>& array, int target, int left, int right) {
    // Base case: empty range, so the target is not present.
    if (left > right) {
        return -1;
    }

    const int middle = left + (right - left) / 2;

    // Base case: target found at the middle index.
    if (array[middle] == target) {
        return middle;
    }

    // Recursive case: search the half that can still contain the target.
    if (target < array[middle]) {
        return binarySearchRange(array, target, left, middle - 1);
    }
    return binarySearchRange(array, target, middle + 1, right);
}

// Sums array index to end
int arraySumFrom(const std::vector<int>& array, std::size_t index) {
    // Base case: no elements remain.
    if (index >= array.size()) {
        return 0;
    }
    // Recursive case: current element + sum of the rest of the array.
    return array[index] + arraySumFrom(array, index + 1);
}

// Reverses array left to right (inclusive) in place.
void reverseRange(std::vector<int>& array, std::size_t left, std::size_t right) {
    // Base case: zero or one element left in the range.
    if (left >= right) {
        return;
    }
    // Recursive case: swap the outer pair, then reverse the inner range.
    std::swap(array[left], array[right]);
    reverseRange(array, left + 1, right - 1);
}

}  // namespace

// Time: O(n)  
// Space: O(n) call stack (n calls deep).
int factorial(int n) {
    validateFactorialInput(n);
    return factorialRecursive(n);
}

// Time: O(n)  Space: O(1).
int factorialIterative(int n) {
    validateFactorialInput(n);
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Time: O(2^n) (about 2 * fib(n + 1) - 1 calls)  Space: O(n) call stack depth.
int fibonacci(int n) {
    validateFibonacciInput(n);
    return fibonacciRecursive(n);
}

// Time: O(n)  Space: O(1).
int fibonacciIterative(int n) {
    validateFibonacciInput(n);
    int previous = 0;
    int current = 1;
    if (n == 0) {
        return previous;
    }
    for (int i = 2; i <= n; ++i) {
        const int next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}

// Precondition: array is sorted in ascending order. Returns the index of target or -1.
// Time: O(log n)  Space: O(log n) call stack depth.
int binarySearch(const std::vector<int>& array, int target) {
    return binarySearchRange(array, target, 0, static_cast<int>(array.size()) - 1);
}

// Precondition: array is sorted in ascending order. Returns the index of target or -1.
// Time: O(log n)  Space: O(1).
int binarySearchIterative(const std::vector<int>& array, int target) {
    int left = 0;
    int right = static_cast<int>(array.size()) - 1;
    while (left <= right) {
        const int middle = left + (right - left) / 2;
        if (array[middle] == target) {
            return middle;
        }
        if (target < array[middle]) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return -1;
}

// Time: O(n)  
// Space: O(n) call stack (n + 1 calls deep).
int arraySum(const std::vector<int>& array) {
    return arraySumFrom(array, 0);
}

// Time: O(n)  Space: O(1).
int arraySumIterative(const std::vector<int>& array) {
    int total = 0;
    for (const int value : array) {
        total += value;
    }
    return total;
}

// Reverses in place. Time: O(n)  Space: O(n) call stack (about n / 2 calls deep).
void reverseArray(std::vector<int>& array) {
    if (array.empty()) {
        return;
    }
    reverseRange(array, 0, array.size() - 1);
}

// Reverses in place. Time: O(n)  Space: O(1).
void reverseArrayIterative(std::vector<int>& array) {
    if (array.empty()) {
        return;
    }
    std::size_t left = 0;
    std::size_t right = array.size() - 1;
    while (left < right) {
        std::swap(array[left], array[right]);
        ++left;
        --right;
    }
}
