# Recursive Algorithms Laboratory Notes

Students should implement each required function recursively, without using loops in the recursive versions.

## Required Algorithms

1. `factorial(n)`
2. `fibonacci(n)`
3. `binarySearch(array, target)`
4. `arraySum(array)`
5. `reverseArray(array)`

## Expected Design

- Identify and comment on the base case for each implementation.
- Identify and comment on the recursive case for each implementation.
- Use clear parameter names and return values.
- Include validation for invalid or unsupported inputs.
- For comparison, also implement iterative versions.

## Comparison Requirement

For each algorithm where an iterative solution is reasonable, provide a written comparison covering:

- time complexity;
- space complexity;
- number and depth of recursive calls;
- readability and maintainability;
- advantages and disadvantages of recursion;
- stack overflow risk;
- Big-Oh analysis for both recursive and iterative forms.

## Recursive vs. Iterative Comparison

Algorithm, Recursive time, Recursive space, Iterative time, Iterative space, Calls / max depth (recursive) 

`factorial(n)` O(n), O(n) stack, O(n) , O(1) , n calls, depth n (1 call for n = 0) |
 `fibonacci(n)` O(2^n) , O(n) stack , O(n) , O(1) , 2·fib(n+1) − 1 calls, depth n |
 `binarySearch`  O(log n) , O(log n) stack , O(log n) , O(1) , ≤ ⌊log₂ n⌋ + 2 calls, depth = calls 
 `arraySum`  O(n) , O(n) stack , O(n) , O(1) , n + 1 calls, depth n + 1 
 `reverseArray`  O(n) , O(n) stack , O(n) , O(1) , ⌊n/2⌋ + 1 calls, depth ⌊n/2⌋ + 1 

### Per-algorithm notes

factorial: Both versions do n multiplications, so speed is the same. The recursive one is basically the math formula (n! = n * (n-1)!) written as code, which makes it really easy to read. The downside is that each call stays on the stack until the end. That doesn’t really matter here, though. 13! is too big for an int, so I throw an error for anything over 12 (and for negatives), which means the recursion never gets very deep.
fibonacci: This is where recursion does worst. The basic recursive version keeps recalculating the same numbers over and over, so the time grows exponentially. fib(25) alone makes 242,785 calls! The stack only gets n deep, so the problem is how slow it is, not memory. The loop version just tracks the last two numbers, so it’s O(n) time and O(1) space. Memoization could fix the recursive one and bring it down to O(n).
binarySearch: Both versions are O(log n), since every step cuts the search area in half. For the recursive one I passed left and right indexes into a helper function so I wasn’t copying parts of the vector every call. It only goes about 20 calls deep even for a million elements, so stack overflow isn’t something to worry about. Honestly both are about as easy to read, and the loop just skips the extra function calls.
arraySum: Both are O(n). I used an index instead of slicing the vector, since slicing would make it O(n^2). The problem is it uses one stack frame per element, so a really huge array (hundreds of thousands of elements) could crash it with a stack overflow. The loop version doesn’t have that problem.
reverseArray: Both swap the first and last elements and move inward until they meet in the middle, so it’s about n/2 swaps. The recursion only goes half as deep as arraySum, but it’s the same issue with really big arrays.
Advantages and disadvantages of recursion

Advantages

The code looks a lot like how the problem is defined, so once the base case and recursive case are right it’s pretty easy to see that it works.
It works well for problems that break down into smaller versions of themselves, like binary search, trees, and merge sort.
You don’t have to keep track of loop counters.

Disadvantages

Every call takes up space on the stack, so it uses more memory than a loop.
If the recursion goes n deep (factorial, arraySum, reverseArray), big inputs can cause a stack overflow. C++ doesn’t promise tail-call optimization, so you can’t count on the compiler to save you.
Function calls add overhead, so recursion is usually a little slower even with the same Big-Oh.
Recursion done the simple way (like fibonacci) can end up doing a ton of repeated work without you noticing.
Summary

For simple stuff like factorial, sum, and reverse, I’d use the loop. It’s just as fast, uses less memory, and can’t overflow the stack. Recursion makes more sense when the depth stays small, like in binary search, or when the problem is naturally recursive. If it keeps solving the same subproblems over and over like fibonacci, the plain recursive version isn’t a good choice.