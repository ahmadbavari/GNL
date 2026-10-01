*This activity has been created as part of the 42 curriculum by ahobeida.*

# get_next_line

## Description
The **get_next_line** project is a custom C function that reads and returns a single line from a given file descriptor (fd). 

**Goal:** The primary objective of this project is to learn how to handle file descriptors, memory allocation, and data manipulation in C. It introduces the concept of static variables, which are essential for retaining state across multiple function calls.

**Overview:** By calling `get_next_line` in a loop, you can read the contents of a file (or standard input) one line at a time until the end of the file (EOF) is reached. The function correctly handles varying buffer sizes and ensures no memory leaks occur during the process.

## Instructions

### Integration
To use `get_next_line` in your own projects, simply include the header file in your C source code:
```c
#include "get_next_line.h"
```

### Compilation
You must compile the function along with your main program. The project requires the `BUFFER_SIZE` flag to define how many bytes `read()` will fetch at a time.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```
*(Note: You can change the `42` to any positive integer value to test different buffer sizes).*

### Execution
Run the compiled executable:
```bash
./gnl
```
If you are testing memory leaks, you can run it through Valgrind:
```bash
valgrind --leak-check=full ./gnl
```

## Algorithm Selection & Justification

**Algorithm:** Buffered Reading with a State-Preserving Static Variable.

**Explanation:**
The function operates in three distinct phases:
1. **Reading and Accumulating (`read_and_stash`):** It reads from the file descriptor in chunks of `BUFFER_SIZE` using the `read()` system call. The read bytes are appended to a `static char *stash` variable. This loop continues until a newline character (`\n`) is detected in the stash, or `read()` returns 0 (EOF).
2. **Line Extraction (`extract_line`):** It iterates through the accumulated `stash` until it finds the `\n` or the null terminator. It allocates just enough memory for the exact line (including the `\n` and `\0`) and extracts it to be returned to the caller.
3. **Stash Cleanup (`clean_stash`):** It takes whatever characters remain in the `stash` *after* the `\n` and saves them in a freshly allocated string. The old `stash` is freed, and the static variable is updated to hold only these remaining characters for the next time the function is called.

**Justification:**
This algorithm was selected because system calls like `read()` are computationally expensive; reading character-by-character (BUFFER_SIZE=1) is inefficient. By reading in chunks (e.g., BUFFER_SIZE=42 or 10000), performance is drastically improved. However, reading in chunks means we will inevitably read past the `\n` into the next line. Using a **static variable** is the most optimal and required way to cache these "overflow" characters so they are not lost between consecutive calls to `get_next_line`. Furthermore, optimizing the string concatenation process ensures the time complexity remains $O(N)$ rather than $O(N^2)$, preventing CPU timeouts on extremely long lines.

## Resources

**Classic References:**
* [Linux Programmer's Manual: read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
* [Linux Programmer's Manual: malloc(3) / free(3)](https://man7.org/linux/man-pages/man3/malloc.3.html)
* [Understanding Static Variables in C](https://en.wikipedia.org/wiki/Static_variable)

**AI Usage:**
Artificial Intelligence (LLM) was utilized during the development of this activity for the following tasks:
* **Algorithm Optimization:** AI was used to identify a performance bottleneck (an $O(N^2)$ time complexity issue causing a `TIMEOUT` on large strings when `BUFFER_SIZE=1`) and provided a strategy to rewrite the string concatenation (`join` function) to execute in linear time.
* **Memory Management Debugging:** AI assisted in tracing and fixing memory leaks and heap buffer overflows, specifically by correctly calculating the exact mathematical size needed for the leftover stash (`ft_strlen(stash) - j`) and preventing the allocation of empty strings at the EOF.
