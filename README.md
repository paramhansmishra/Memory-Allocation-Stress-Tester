# Memory Exhaustion Test in C

This program is a controlled experiment to observe how a system behaves when memory is continuously allocated until exhaustion. It demonstrates the difference between graceful allocation failure (malloc() returning NULL) and forced termination by the operating system or sandbox (OOM killer).

## 🔧 How It Works

  Allocates 1 MB chunks in a loop.

  Touches each allocated block using memset() to force real physical memory usage (prevents Linux from faking allocations using lazy overcommit).

  Stores all allocated pointers to prevent the memory from being freed or optimized away.

  Prints progress every 10 MB so the terminal output stays readable.

  When allocation fails, it prints the total memory successfully allocated.

  Intentionally does not free memory at the end — this allows inspection with tools like top, htop, or pmap.

## 🗂️ Use Cases

  Visualize heap growth over time

  Test malloc() failure scenarios

  Observe OS-level memory limits and OOM killing behavior

  Demonstrate difference between soft failure (NULL pointer) vs hard kill

## 🚀 Compilation & Execution
  gcc -O2 -o mem_test mem_test.c
  ./mem_test

## ⚠️ Safety & Environment Notes
  Environment	Expected Behavior
  Online IDE / Sandbox	Likely terminated automatically before malloc fails
  Linux Terminal	May hit malloc() failure or be OOM-killed
  With ulimit	Allows controlled failure at desired memory limit

  To force a clean failure instead of OS kill:

  ulimit -v 500000   # Limit process to ~500 MB
  ./mem_test

## ✅ Expected Output Example
  Allocated ~10 MB
  Allocated ~20 MB
  ...
  Allocated ~880 MB
  === Session Ended. Please Run the code again ===

  or

  malloc() failed after allocating ~512 MB
  Stopped at ~512 MB

## 📌 Notes

  The program uses pause() at the end so that the allocated memory remains in use. You can inspect the process from another terminal while it’s frozen.

  To stop execution manually: press Ctrl + C.
