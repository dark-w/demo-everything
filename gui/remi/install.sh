#!/usr/bin/env bash

if [ $UID != 0 ]; then
    echo 'pls run as root'
    exit 1
fi

rm -vrf /opt/front/
mkdir -p /opt/front/
cp -v *.py index.service /opt/front/
cd /opt/front/

apt update
apt install -y virtualenv
virtualenv --creator venv python-venv
source python-venv/bin/activate
pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple remi

cp -v /opt/front/index.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable index.service
systemctl restart index.service

deactivate

