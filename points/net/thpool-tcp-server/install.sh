#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root!'
    exit 1
fi

rm -vrf /opt/thpool-tcp-server
mkdir -p /opt/thpool-tcp-server
cp -v thpool-tcp-server *.service /opt/thpool-tcp-server

cp -v /opt/thpool-tcp-server/thpool-tcp-server.service /etc/systemd/system
systemctl enable --now thpool-tcp-server.service

echo install done

