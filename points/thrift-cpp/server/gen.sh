#!/usr/bin/env bash

thrift -r --gen cpp -o ./ worker.thrift
