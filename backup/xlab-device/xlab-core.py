from sysv_ipc import MessageQueue, IPC_CREAT
import requests
import logging
import time
from datetime import datetime
import os
from pyocd.core.helpers import ConnectHelper

mq = MessageQueue(20200621, IPC_CREAT)
logging.basicConfig(filename='/var/log/xlab/core.log', level=logging.DEBUG)

while True:
  msg, _ = mq.receive()
  logging.info(f'message = {msg}')

  try:
    udev_param = msg.decode().split()
    if len(udev_param) != 2:
      raise Exception('wrong udev parameters: ' + udev_param)

    [udev_event, udev_node] = udev_param

    board_name = None
    board_uid = None
    
    if udev_node.startswith('/dev/ttyUSB'):
      board_name = 'esp32'
      board_uid = '0' # FIXME
    elif udev_node.startswith('/dev/sd'):
      start_time = datetime.now()
      while (datetime.now() - start_time).seconds < 10:
        with open('/proc/mounts') as f:
          for line in f:
            dev, mp = line.split()[0:2]
            if dev == udev_node:
              for board in ConnectHelper.get_all_connected_probes(blocking=False):
                if board.product_name == 'STM32 STLink':
                  bn = board.description.split()[0]
                  if bn.split('-')[1] == mp.split('_')[-1]:
                    board_name = bn
                    board_uid = board.unique_id
                    break

    if board_name is None:
      raise Exception('device "{}" not supported yet!'.format(udev_node))

    if udev_event == 'add':
      action = 'connect'
    elif udev_event == 'remove':
      action = 'disconnect'
    else:
      raise Exception('unknown udev event: ' + udev_event)

    url = ' http://xlab.huanjun.top/api/board/{}/{}'.format(board_uid, action)
    data = {'name': board_name, 'node': udev_node}
    header = {'Content-Type': 'application/json'}
    res = requests.post(url, json=data, headers=header)
    logging.info(res.text)
  except Exception as e:
    logging.error(e)
