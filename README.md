# Sistema-de-Parking-Arduino
## Proyecto de Estacionamiento Automatizado con Arduino

Este repositorio contiene el código y la documentación para un sistema de estacionamiento automatizado utilizando Arduino. El proyecto facilita la gestión de acceso de vehículos a un estacionamiento con capacidad para cuatro espacios, mostrando en tiempo real la disponibilidad de espacios y controlando una barrera automática para la entrada y salida de vehículos.

## Componentes Principales

- **Arduino:** Actúa como el cerebro del sistema, coordinando la lectura de sensores, el control del servo motor y la actualización de la pantalla LCD.
- **Servo Motor:**
  - **Librería Utilizada:** `Servo.h`
  - **Función:** Controla la apertura y cierre de la barrera de estacionamiento.
- **Sensores Infrarrojos (IR):**
  - **Pines de Conexión:** IR1 conectado al pin 2, IR2 al pin 3.
  - **Función:** Detectar la entrada y salida de vehículos, ajustando el contador de espacios disponibles.
- **Pantalla LCD:**
  - **Modelo:** I2C LCD
  - **Configuración:** Dirección I2C 0x27, 16 columnas y 2 filas.
  - **Función:** Muestra información sobre la cantidad de espacios disponibles y mensajes importantes como "Estacionamiento lleno".

## Funcionamiento del Sistema

1. **Inicialización:** Al encenderse, el sistema muestra un mensaje de bienvenida en la pantalla LCD.
2. **Detección de Entrada:** Si un vehículo se acerca a la entrada y hay espacios disponibles, el sistema abre la barrera y decrementa el contador de espacios disponibles.
3. **Detección de Salida:** Al detectar un vehículo en la salida, el sistema abre la barrera, permite la salida del vehículo y actualiza el contador de espacios.
4. **Actualización de la Pantalla LCD:** Constantemente se muestra el número de espacios disponibles y mensajes de estado.

## Características Adicionales

- Retraso breve antes de cerrar la barrera para asegurar un movimiento seguro.
- Mensajes en la pantalla LCD cuando el estacionamiento está lleno para informar a los conductores.

## Autor

- Rodrigo Manuel Reyes Cordova
