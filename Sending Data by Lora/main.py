from network import LoRa
import socket
import time
import binascii
import utime
import os
import pycom

from machine import Timer

def select_subband(lora, subband):
    if (type(subband) is int):
        if ((subband<1) or (subband>8)):
            raise ValueError("subband out of range (1-8)")
    else:
        raise TypeError("subband must be 1-8")

    for channel in range(0, 72):
        lora.remove_channel(channel)

    index = (subband-1)*8
    for channel in range(0, 7):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(8, 15):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(16, 23):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(24, 31):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(32, 39):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(40, 47):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(48, 55):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(56, 63):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

    index = (subband-1)*8
    for channel in range(64, 71):
        lora.add_channel(channel, frequency=902300000+index*200000, dr_min=0, dr_max=3)
        index+=1

# apagar LED
pycom.heartbeat(False)

#LoRa
lora = LoRa(mode=LoRa.LORAWAN, adr=False, public=True, tx_retries=0,device_class=LoRa.CLASS_C)

sb = 1 #Change to desired conduit frequency sub-band
select_subband(lora,sb)
dev_eui = binascii.unhexlify('00 80 00 00 A0 00 01 82'.replace(' ','')) # these settings can be found from TTN
app_eui = binascii.unhexlify('77 66 55 44 33 22 11 11'.replace(' ',''))
app_key = binascii.unhexlify('00 11 22 33 44 55 66 77 00 11 22 33 44 55 66 66'.replace(' ',''))

lora.join(activation=LoRa.OTAA, auth=(dev_eui, app_eui, app_key), timeout=0)

while not lora.has_joined():
    time.sleep(5)
    print('Not yet joined on frequency sub-band '+str(sb)+'...')

pycom.rgbled(0x003300)
if(lora.has_joined()):print("Successful join on frequency sub-band "+str(sb)+"!")

s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)

s.setsockopt(socket.SOL_LORA, socket.SO_DR, 3)
s.setblocking(False)
cont = 0
while lora.has_joined():
    #s.setblocking(True)
    #dat = bytes(str(payload),"ascii")
    s.send("G")
    time.sleep(4)
    rx = s.recv(256)
    if rx:
        print(rx)
    #s.setblocking(False)
    cont=cont+1
    time.sleep(6)
