#!/usr/bin/env bash

make clean && make
scp thpool-tcp-server thpool-tcp-server.service install.sh uninstall.sh dark@darkone.top:~/thpool-tcp-server

