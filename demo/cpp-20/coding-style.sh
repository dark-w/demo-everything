#!/usr/bin/env bash

for obj in `find . -name "*.cc"`; do
    clang-format -i $obj;
done

