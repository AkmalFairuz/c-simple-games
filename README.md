# c-terminal-games

A collection of simple terminal games written in C. College project for the Algorithm and Programming course.

Executable files can be found in the [releases](https://github.com/AkmalFairuz/c-terminal-games/releases) page.

## TODO
- [x] Type Racer
    - [x] Typing & Validation
    - [x] Generate random words
    - [x] Scoring
    - [x] Don't use `system("cls")` to prevent blinking
    - [ ] Don't print the text all at once to prevent print delay
    - [ ] Add timer
    - [ ] Multiple language support
- [ ] Maze
- [ ] Math Quiz
- [ ] Leaderboard
- [x] Windows support
- [ ] MacOS support
- [ ] Linux support

## How to compile (for Windows)

- Using GCC:

```bash
gcc -std=c11 -o main.exe main.c src/*.c
```

- Using CMake:

Ninja is required to compile the project. If you don't have Ninja installed, you can install it using `choco install ninja`.
```bash
cmake -B build -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -G Ninja -S .
```

## Contributors
- [AkmalFairuz](https://github.com/AkmalFairuz)
- [Kristantowinata](https://github.com/Kristantowinata)
- [Takiyo0](https://github.com/Takiyo0)