#!/usr/bin/env bash

if [ $UID != 0 ]; then
	echo "pls run as root!"
	exit 1
fi

# XLAB_USER=xlab

if [ -z "$XLAB_USER" ]; then
	XLAB_USER="root"
fi

if [ $XLAB_USER == root ]; then
	XLAB_HOME="/root"
else
	XLAB_HOME="/var/lib/$XLAB_USER"
	useradd -m -d $XLAB_HOME -G dialout,disk $XLAB_USER || exit 1
	XLAB_SUDO="sudo -u $XLAB_USER"
fi

$XLAB_SUDO mkdir $XLAB_HOME/.pip
$XLAB_SUDO cp -v pip.conf $XLAB_HOME/.pip/ || exit 1
$XLAB_SUDO python3 -m venv $XLAB_HOME/env || exit 1
$XLAB_SUDO $XLAB_HOME/env/bin/python -m pip install -r requirements.txt || exit 1
$XLAB_SUDO cp -v xlab-core.py $XLAB_HOME || exit 1

mkdir /var/log/xlab
echo > /var/log/xlab/core.log
chown $XLAB_USER:$XLAB_USER -R /var/log/xlab

cat > /lib/systemd/system/xlab-device.service << __EOF__
[Unit]
Description=XLabDevice
After=syslog.target

[Service]
ExecStart=$XLAB_HOME/env/bin/python $XLAB_HOME/xlab-core.py
User=$XLAB_USER
Restart=always

[Install]
WantedBy=multi-user.target
__EOF__

systemctl enable --now xlab-device
systemctl daemon-reload

cp -v board.py $XLAB_HOME # FIXME
cat > /etc/udev/rules.d/80-board.rules << __EOF__
SUBSYSTEM=="tty|block", ACTION=="add", RUN+="$XLAB_HOME/env/bin/python $XLAB_HOME/board.py add \$devnode"
SUBSYSTEM=="tty|block", ACTION=="remove", RUN+="$XLAB_HOME/env/bin/python $XLAB_HOME/board.py remove \$devnode"
__EOF__

systemctl restart udev
