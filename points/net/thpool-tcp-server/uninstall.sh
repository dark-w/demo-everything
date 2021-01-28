#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root'
    exit 1
fi

systemctl stop thpool-tcp-server.service
rm -vf /etc/systemd/system/thpool-tcp-server.service
rm -vrf /opt/thpool-tcp-server
systemctl daemon-reload

echo uninstall done

