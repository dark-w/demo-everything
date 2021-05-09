#!/usr/bin/env python3

import sys
from sysv_ipc import MessageQueue

event = sys.argv[1]
dev = sys.argv[2]

mq = MessageQueue(20200621)
mq.send("{} {}".format(event, dev))
