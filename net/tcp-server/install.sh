#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root!'
    exit 1
fi

rm -vrf /opt/tcp-server
mkdir -p /opt/tcp-server
cp -v tcp-server *.service /opt/tcp-server

cp -v /opt/tcp-server/tcp-server.service /etc/systemd/system
systemctl enable --now tcp-server.service

echo install done

