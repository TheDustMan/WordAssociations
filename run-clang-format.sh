#!/usr/bin/env bash

find . -iname \*.cpp -o -iname \*.h -exec clang-format -style=file -i {} \;
