#!/usr/bin/env bash

make clean && make
scp epoll-tcp-server epoll-tcp-server.service install.sh uninstall.sh dark@darkone.top:~/epoll-tcp-server

