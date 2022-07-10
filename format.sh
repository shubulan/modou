#!/bin/bash
find ./src -name "*.cc" | xargs clang-format -style=google -i
find ./include -name "*.h" | xargs clang-format -style=google -i
