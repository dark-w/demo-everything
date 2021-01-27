#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root'
    exit 1
fi

systemctl stop epoll-tcp-server.service
rm -vf /etc/systemd/system/epoll-tcp-server.service
rm -vrf /opt/epoll-tcp-server
systemctl daemon-reload

echo uninstall done

