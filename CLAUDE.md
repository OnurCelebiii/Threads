# CLAUDE.md — AI Assistant Guide for Threads

## Project Overview

This is an educational C programming repository demonstrating **POSIX threads (pthreads)** concepts. It contains standalone C programs covering fundamental multithreading patterns on Linux/UNIX systems.

## Repository Structure

```
Threads/
├── CLAUDE.md                     # This file
├── README.md                     # Project README (currently empty)
├── WelcomeThreads.c              # Basic thread creation and joining
├── MutexUsage.c                  # Mutex synchronization
├── CreateThreadsWithLoop.c       # Creating multiple threads in a loop
├── SumArrayWithThread.c          # Parallel array summation
└── ThreadSortingAlgorithm.c      # Multi-threaded bubble sort + merge
```

## Technology Stack

- **Language:** C (no specific standard version pinned, targets POSIX)
- **Threading:** POSIX threads (`pthread.h`)
- **Standard libraries:** `stdio.h`, `stdlib.h`, `unistd.h`
- **Build tool:** None (manual `gcc` compilation)
- **OS:** Linux/UNIX (POSIX-compliant systems)

## Building and Running

Each file is a standalone program compiled individually. No Makefile exists.

```bash
# General pattern
gcc -g -pthread <filename>.c -o <output>
./<output>

# Examples
gcc -g -pthread WelcomeThreads.c -o welcome && ./welcome
gcc -g -pthread MutexUsage.c -o mutex && ./mutex
gcc -g -pthread CreateThreadsWithLoop.c -o loop && ./loop
gcc -g -pthread SumArrayWithThread.c -o sum && ./sum
gcc -g -pthread ThreadSortingAlgorithm.c -o sort && ./sort
```

The `-pthread` flag is required to link the pthreads library. `-g` enables debug symbols.

## Source File Conventions

Each file follows these consistent patterns:

1. **Thread routine functions** are defined before `main()` and match the signature:
   ```c
   void *routine_name(void *arg)
   ```

2. **Thread creation** uses:
   ```c
   pthread_t thread;
   pthread_create(&thread, NULL, routine_name, arg);
   pthread_join(thread, &retval);
   ```

3. **Mutex pattern** (when shared state is modified):
   ```c
   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
   pthread_mutex_lock(&mutex);
   // critical section
   pthread_mutex_unlock(&mutex);
   pthread_mutex_destroy(&mutex);
   ```

4. **Passing data to threads:** via a single `void *arg` — cast to the appropriate type inside the routine. For multiple values, use a struct.

5. **Returning data from threads:** via `pthread_join(&thread, &retval)` — the routine returns a `void *` (often a `malloc`'d value; caller must `free` it).

## File Summaries

| File | Threads | Key Concepts |
|------|---------|--------------|
| `WelcomeThreads.c` | 2 | `pthread_create`, `pthread_join`, `sleep`, `getpid` |
| `MutexUsage.c` | 2 | Mutex lock/unlock, race condition prevention |
| `CreateThreadsWithLoop.c` | 4 | Thread creation in a loop, array of `pthread_t` |
| `SumArrayWithThread.c` | 2 | Passing struct args, returning heap-allocated values |
| `ThreadSortingAlgorithm.c` | 3 | Staged threads (sort + merge), bubble sort, array partitioning |

## Coding Conventions

- Global shared variables are declared at file scope (e.g., `int x = 0`)
- Mutex variables are declared globally alongside the data they protect
- No error checking on `pthread_*` calls (educational simplicity)
- Array sizes are hardcoded constants
- Comments are minimal; logic is demonstrated directly in code

## Development Workflow

### Adding a New Example

1. Create a new `.c` file in the repository root
2. Follow the existing structure: includes → globals → thread routines → `main()`
3. Add a compilation comment at the top of the file:
   ```c
   //gcc -g -pthread <filename>.c -o <output>
   //./<output>
   ```
4. Keep each file self-contained — no shared headers or libraries across files

### Git Workflow

- Branch for AI-driven work: `claude/add-claude-documentation-J908g`
- Commits are small and describe the specific example added (e.g., `"Create ThreadSortingAlgorithm.c"`)
- No CI/CD pipeline or automated tests

## Key Notes for AI Assistants

- **No build system:** Do not create a Makefile unless explicitly requested. Each file compiles independently.
- **No tests:** There is no test framework. Verification is done by running and observing stdout.
- **POSIX only:** Code targets Linux/UNIX. Windows-specific threading APIs (`CreateThread`, etc.) are out of scope.
- **Educational focus:** Keep examples simple and clear. Avoid over-engineering — the goal is demonstrating one concept per file.
- **No headers:** Do not create shared `.h` files unless a new example genuinely requires shared types.
- **Mutex always with global data:** If a thread routine touches a global variable, a mutex must be used.
- **Memory management:** If a thread returns a heap-allocated value, the caller in `main()` is responsible for `free()`ing it.
