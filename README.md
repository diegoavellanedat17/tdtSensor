# Sensor de Humedad IoT
En este repositorio se encuentran las pruebas del sensor de humedad IoT diseñado, se describen las pruebas y los resultados correspondientes a las mediciones a la salida del ADC enviadas a un broker MQTT y consolidadas en el archivo de Python. 

![alt text](https://github.com/diegoavellanedat17/tdtSensor/blob/master/images/portada.png)

## Dimensiones de la Microcinta 

Las siguientes son las dimensiones reales de la microcinta. 

![alt text](https://github.com/diegoavellanedat17/tdtSensor/blob/master/images/medidas.png)

## Pruebas 

En principio se toman los datos de la microcinta en el aire y posteriormente se empezarán a generar los archivos proporcionales a la cantidad de agua ingresada.
La cantidad de Tierra es 569.9 g. 

| Condición | Cantidad Agua (ml) | Archivo Generado |
| ----- | ---- | ---- |
| Aire | 0 | aire.csv |
| Tierra Seca | 0 | Tierra_0_.csv |
| 5 % | 28.5 | Tierra_5_.csv |
| 10 % | 56.9 | Tierra_10_.csv |
| 20 % | 114 | Tierra_20_.csv |









