import paho.mqtt.client as mqtt
import time
from time import sleep
import datetime
import config

# Crear el archivo de config con las credenciales del Broker para replicar las pruebas 

def on_connect(client, userdata, flags, rc):
    print("Connected with result code" + str(rc))
    topic=config.topic
    client.subscribe(topic)


def on_log(client, userdata, level, buf):
    print("log: ",buf)

def on_message(client, userdata, message):
    print("message received " ,str(message.payload))
    payload=message.payload.decode("utf8")
    print(payload)

    try:
        val=int(payload)
        now= datetime.datetime.now()
        format=str(now.hour)+':'+str(now.minute)+':'+str(now.second)
        print(format)
        f = open("Tierra_5_.csv",'a')  # write in text mode
        f.write(format +","+payload+"\n")
        f.close()
    except:
        print('no se guarda por que no es un int ')

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

broker_address= config.broker_address
port =   config.port
user = config.user
password = config.password
client_device = config.client_device
topic=config.topic


mqttc = mqtt.Client(client_device)
mqttc.on_connect = on_connect
mqttc.on_message=on_message
#mqttc.on_log=on_log 
mqttc.on_publish = on_publish
mqttc.on_subscribe = on_subscribe

mqttc.username_pw_set(user, password)
mqttc.connect(broker_address, port)
mqttc.loop_start()


while True:
    time.sleep(1)
    print('Waiting for messages')

#mqttc.loop_stop() #stop the loop
