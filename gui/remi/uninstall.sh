#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root'
    exit 1
fi

systemctl stop index.service
rm -vrf /opt/front
rm -vf /etc/systemd/system/index.service
systemctl daemon-reload

