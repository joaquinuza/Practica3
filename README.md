## Practica 3 
## Comunicación, gestión y representación de datos de sensores con Python.

El objetivo de esta práctica es la creación de tablas csv y ficheros de texto para almacenar datos de sensores. Partiendo del [código](https://github.com/joaquinuza/Practica2/blob/main/FREERTOS_ejc2/FREERTOS_ejc2.ino) donde se capturaban datos del sensor inercial MPU9250 cada segundo y se enviaban por puerto serie, en esta practica, se crea un script en Python que recoge estos datos del puerto serie y los almacena en ficheros csv y txt para su posterior análisis y representación. 
Se hace uso de las librerías serial, que encapsula el acceso al puerto serie, csv para poder escribir y leer ficheros en ese formato y la librería time, para poder almacenar datos un tiempo determinado.
Por ultimo una vez recogidos los datos mediante el uso de la librería matemática numpy junto con pyplot para la representación por pantalla de datos,  se obtienen y muestran la media y la desviación estándar de los datos capturados. 

## Enlace.
Los siguientes ejercicios se pueden consultar en [git](https://github.com/joaquinuza/Practica3)