# Sistema de Parking ESP32 Blynk

## Integrante:
* Reyes Cordova Rodrigo Manuel

## Descripción
El Sistema de Parking ESP32 Blynk es un proyecto diseñado para automatizar el control y monitoreo de un estacionamiento utilizando la tecnología ESP32 y la plataforma Blynk. Este sistema permite la gestión de accesos mediante sensores infrarrojos y un servo motor que actúa como barrera física.

## Características
- **Control de acceso automático**: Utiliza sensores IR para detectar la entrada y salida de vehículos.
- **Interfaz de usuario**: Dispone de un display LCD que muestra información relevante como el estado de la conexión y la disponibilidad de espacios.
- **Monitoreo y control remoto**: Integración con la plataforma Blynk para visualizar y gestionar el parqueo desde cualquier lugar.
- **Servo controlado**: Barrera controlada por un servo motor, que se maneja automáticamente según el flujo de vehículos.

## Componentes
- ESP32
- LiquidCrystal I2C (LCD)
- Servo Motor
- Sensores Infrarrojos (IR)
- Conexión a Internet para Blynk

## Configuración
1. **Conexión de Componentes**: Conecta los sensores IR, el servo motor y el LCD al ESP32 según el esquema de pines definido.
2. **Configuración WiFi**: Establece las credenciales de tu red WiFi en el código.
3. **Configuración de Blynk**: Asegúrate de tener una cuenta en Blynk y de configurar el token de autenticación en el código.

## Uso
Una vez que el sistema esté configurado y en funcionamiento, mostrará en el LCD el estado de conexión y los espacios disponibles. Las entradas y salidas de vehículos se registrarán automáticamente y podrás monitorear y controlar el sistema a través de la app Blynk.

## Soporte
Para soporte técnico o contribuciones al proyecto, por favor abre un issue en el repositorio de GitHub o envía un correo directamente al equipo de desarrollo.

## Licencia
Este proyecto está licenciado bajo la Licencia MIT - ver el archivo LICENSE.md para más detalles.
