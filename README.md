# About <a href="https://cmake.org/cmake/help/v3.15"><img align="right" src="https://img.shields.io/badge/CMake-3.15-BA1F28?logo=CMake" alt="CMake 3.15" /></a><a href="https://en.wikipedia.org/wiki/C_(programming_language)"><img align="right" src="https://img.shields.io/badge/C-99-A5B4C6?logo=data:image/svg+xml;base64,PHN2ZyByb2xlPSJpbWciIHZpZXdCb3g9IjAgMCAyNCAyNCIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+QysrIGljb248L3RpdGxlPjxwYXRoIGZpbGw9IiNmZmZmZmYiIGQ9Ik0yMi4zOTMgNmMtLjE2Ny0uMjktLjM5OC0uNTQzLS42NTItLjY5TDEyLjkyNS4yMmMtLjUwOC0uMjkzLTEuMzM5LS4yOTMtMS44NDcgMEwyLjI2IDUuMzFjLS41MDguMjkzLS45MjMgMS4wMTMtLjkyMyAxLjZ2MTAuMThjMCAuMjk0LjEwNC42Mi4yNzEuOTEuMTY3LjI5LjM5OC41NDMuNjUyLjY4OWw4LjgxNiA1LjA5MWMuNTA4LjI5MyAxLjMzOS4yOTMgMS44NDcgMGw4LjgxNi01LjA5MWMuMjU0LS4xNDYuNDg1LS4zOTkuNjUyLS42ODlzLjI3MS0uNjE2LjI3MS0uOTFWNi45MWMuMDAyLS4yOTQtLjEwMi0uNjItLjI2OS0uOTF6TTEyIDE5LjEwOWMtMy45MiAwLTcuMTA5LTMuMTg5LTcuMTA5LTcuMTA5UzguMDggNC44OTEgMTIgNC44OTFhNy4xMzMgNy4xMzMgMCAwIDEgNi4xNTYgMy41NTJsLTMuMDc2IDEuNzgxQTMuNTY3IDMuNTY3IDAgMCAwIDEyIDguNDQ1Yy0xLjk2IDAtMy41NTQgMS41OTUtMy41NTQgMy41NTVTMTAuMDQgMTUuNTU1IDEyIDE1LjU1NWEzLjU3IDMuNTcgMCAwIDAgMy4wOC0xLjc3OGwzLjA3NyAxLjc4QTcuMTM1IDcuMTM1IDAgMCAxIDEyIDE5LjEwOXoiLz48L3N2Zz4=" alt="C 99" /></a>

**zero** is a cross-platform (Windows/UNIX) C program that can be used to overwrite files with zeros. It supports 32-bit and 64-bit platforms.

# Usage

```shell
zero [-f, --force] <FILE>
```

You will be prompted to confirm that you want to overwrite the file.

###### Options:

- `-f` - skips the prompt and immediately starts overwriting the file

After the overwriting process is done, the file will be automatically deleted. For large files, use the 64-bit version of the program included in the release, **zero64**.

# Releases

[1.1R](https://github.com/exom-dev/zero/releases/tag/v1.1R) - December 26th, 2020

[1.0R](https://github.com/exom-dev/zero/releases/tag/v1.0R) - December 25th, 2020

# License <a href="https://github.com/exom-dev/zero/blob/master/LICENSE"><img align="right" src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT"></a>

This project was created by [The Exom Developers](https://github.com/exom-dev).

The zero project is licensed under the [MIT](https://github.com/exom-dev/zero/blob/master/LICENSE) license.

