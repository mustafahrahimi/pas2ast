# pas2ast

A simple Pascal lexer/parser implemented in C for the DVGC01 lab.

## Prerequisites
- C compiler (gcc/clang) or Make
- Git

## Clone
```bash
git clone https://github.com/mustafahrahimi/pas2ast.git
cd "pas2ast"
```

## Build
```bash
make
```
Or build manually:
```bash
gcc -Wall -std=c99 -g -o parser driver.c keytoktab.c lexer.c optab.c parser.c symtab.c
```

## Run
Run the parser with a Pascal source file:
```bash
./parser < path/to/program.pas      # Unix
parser.exe < path\to\program.pas    # Windows
```

## Test
Run tests using Make:

Test a specific file by name:
```bash
make test TEST=testok1
```

Test with full file path:
```bash
make test-single FILE=TestSuite/testok1.pas
```

Run all tests:
```bash
make test-all
```

## Clean
Remove build artifacts:
```bash
make clean
```

## Notes
- The parser reads from stdin, so use input redirection (<)
- Test files are located in the TestSuite/ directory


