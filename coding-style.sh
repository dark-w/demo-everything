#!/usr/bin/env bash

for obj in `find . -name *.[c,h]`; do
    clang-format -i $obj;
done

