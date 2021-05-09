#!/usr/bin/env bash

if [ $UID != 0 ]; then
	echo "pls run as root!"
	exit 1
fi

rm -v /etc/udev/rules.d/80-board.rules
systemctl restart udev

systemctl disable --now xlab-device
rm -vf /lib/systemd/system/xlab-device.service
userdel -r xlab
rm -rf /var/log/xlab

ipcrm --queue-key 20200621
