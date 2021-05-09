#!/usr/bin/env bash

for obj in `find . -name *.cc`; do
    echo clang-format -i $obj
    clang-format -i $obj
done

for obj in `find . -name *.[c,h]`; do
    echo clang-format -i $obj
    clang-format -i $obj
done

