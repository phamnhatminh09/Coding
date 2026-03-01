## Cursor Cloud specific instructions

This is a personal competitive programming (CP) repository containing standalone C++ solution files.

### Project structure

- `C++/template.cpp` / `C++/template_short.cpp` — boilerplate templates for new solutions
- `C++/2024/`, `C++/2025/` — solutions organized by year
- `.in` / `.ans` files alongside solutions are test inputs and expected outputs

### Compile and run

Each `.cpp` file is independent. Compile and run with:

```
g++ -std=c++17 -O2 -o solution problem.cpp
./solution < problem_1.in
```

All solutions use `#include <bits/stdc++.h>` (GCC extension). The environment's system `g++` (13.x) is sufficient — no additional dependencies are needed.

### Testing a solution

Compare output against the `.ans` file:

```
diff <(./solution < problem_1.in) problem_1.ans
```

### Notes

- There is no build system, linter, package manager, or test framework — this is a collection of standalone competitive programming files.
- No services need to run.
