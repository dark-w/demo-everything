#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root'
    exit 1
fi

systemctl stop tcp-server.service
rm -vf /etc/systemd/system/tcp-server.service
rm -vrf /opt/tcp-server
systemctl daemon-reload

echo uninstall done

