#!/usr/bin/env bash

make clean && make
scp tcp-server tcp-server.service install.sh uninstall.sh dark@darkone.top:~/tcp-server

