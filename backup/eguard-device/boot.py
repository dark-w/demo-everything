import bluetooth
import struct
from micropython import const
import time
from machine import Pin
import _thread

_ADV_APPEARANCE_GENERIC_COMPUTER = const(128)
_ADV_TYPE_FLAGS = const(0x01)
_ADV_TYPE_NAME = const(0x09)
_ADV_TYPE_APPEARANCE = const(0x19)

_IRQ_CENTRAL_CONNECT = const(1 << 0)
_IRQ_CENTRAL_DISCONNECT = const(1 << 1)
_IRQ_GATTS_WRITE = const(1 << 2)

interval = 100000

_CMD_OPEN = "o"

def _append(adv_type, value):
    return struct.pack("BB", len(value) + 1, adv_type) + value

payload = bytearray()
payload += _append(_ADV_TYPE_FLAGS, struct.pack("B", (0x02) + (0x04)))
payload += _append(_ADV_TYPE_NAME, "eguard")
payload += _append(_ADV_TYPE_APPEARANCE, struct.pack("<h", _ADV_APPEARANCE_GENERIC_COMPUTER))

UART_UUID = bluetooth.UUID('6E400001-B5A3-F393-E0A9-E50E24DCCA9E')
UART_RX = (bluetooth.UUID('6E400002-B5A3-F393-E0A9-E50E24DCCA9E'), bluetooth.FLAG_WRITE,)
UART_SERVICE = (UART_UUID, (UART_RX,),)
SERVICES = (UART_SERVICE,)

def drive_wheel():
    #init Pin
    p25 = Pin(25, Pin.OUT)
    p26 = Pin(26, Pin.OUT)
    #down
    p25.on()
    p26.off()
    time.sleep(2.1)
    #wait open
    p25.off()
    time.sleep(0.9)
    #up
    p26.on()
    time.sleep(1)
    #stop
    p26.off()

def do_cmd(cmd):
    if cmd == _CMD_OPEN:
        drive_wheel()
        
def ble_irq(event, data):
    if event == _IRQ_CENTRAL_CONNECT:
        print('connect:', data)

    elif event == _IRQ_CENTRAL_DISCONNECT:
        print('disconnect')
        ble.gap_advertise(interval, adv_data=payload)
        
    elif event == _IRQ_GATTS_WRITE:
        try:
            cmd = ble.gatts_read(rx).decode()
            _thread.start_new_thread(do_cmd, (cmd,))
        finally:
            pass
 
ble = bluetooth.BLE()
ble.active(True)
ble.irq(ble_irq)
((rx,), ) = ble.gatts_register_services(SERVICES)
ble.gap_advertise(interval, adv_data=payload)
