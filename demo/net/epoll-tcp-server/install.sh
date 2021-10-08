#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root!'
    exit 1
fi

rm -vrf /opt/epoll-tcp-server
mkdir -p /opt/epoll-tcp-server
cp -v epoll-tcp-server *.service /opt/epoll-tcp-server

cp -v /opt/epoll-tcp-server/epoll-tcp-server.service /etc/systemd/system
systemctl enable --now epoll-tcp-server.service

echo install done

