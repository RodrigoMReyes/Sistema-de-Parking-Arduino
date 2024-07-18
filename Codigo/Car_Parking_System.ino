#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>  
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL2EpseP58A"
#define BLYNK_TEMPLATE_NAME "Sistema de Parqueo ESP32"
#define BLYNK_AUTH_TOKEN "RiWd7KT3q8IRW_3VwVFhuAssWB1CIQ1R"

// Your WiFi credentials.
char auth[] = BLYNK_AUTH_TOKEN; // Blynk authentication token
char ssid[] = ""; // Your WiFi SSID
char pass[] = ""; // Your WiFi password

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inicializa el objeto lcd
Servo servo1;

int IR1 = 34; // Pin de entrada para el sensor IR1
int IR2 = 35; // Pin de entrada para el sensor IR2

int MaxSlots = 4; // Cantidad máxima de plazas de estacionamiento
int acumulado_input = 0;
int acumulado_output = 0;
int Slot = 4; // Contador de plazas de estacionamiento
int flag1 = 0; // Bandera para indicar la entrada de un coche
int flag2 = 0; // Bandera para indicar la salida de un coche

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi...");
  }

  lcd.clear();
  lcd.print("WiFi Conectado");
  delay(2000);  // Muestra por 2 segundos

  Serial.println("Conectado a WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.print("Conectando Blynk");
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    // Espera la conexión
  }

  lcd.clear();
  lcd.print("Blynk Conectado");
  delay(2000);  // Muestra por 2 segundos

  Serial.println("Conectado a Blynk");
  
  lcd.init(); // Inicializa la pantalla LCD
  lcd.backlight(); // Enciende la luz de fondo de la pantalla LCD

  pinMode(IR1, INPUT); // Configura el pin del sensor IR1 como entrada
  pinMode(IR2, INPUT); // Configura el pin del sensor IR2 como entrada

  servo1.attach(4); // Conecta el servo al pin 4
  servo1.write(100); // Mueve el servo a la posición 100 (posición cerrada)

  // Muestra el mensaje de bienvenida en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" SISTEMA DE PARQ ");
  delay(3000); // Espera 3 segundos
  lcd.clear(); // Limpia la pantalla LCD
}

void loop() {

  Blynk.run();

  // Detecta si un coche está entrando
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;

      if (flag2 == 0) {
        acumulado_input++; // Incrementa el contador cada vez que un coche entra
        Blynk.virtualWrite(V2, acumulado_input); // Envía el valor de acumulado_input a Blynk
        moveServoSlowly(0);
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("   LO SIENTO :( ");
      lcd.setCursor(0, 1);
      lcd.print(" ESTAC. LLENO  ");
      delay(3000);
      lcd.clear();
    }
  }

  // Detecta si un coche está saliendo
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1; // Marca la salida de un coche
    if (flag1 == 0 && Slot != MaxSlots) { // Si no hay coche entrando al mismo tiempo y no está lleno
      acumulado_output++; // Incrementa el contador cada vez que un coche entra
      Blynk.virtualWrite(V3, acumulado_output); // Envía el valor de acumulado_output a Blynk
      moveServoSlowly(0); // Mueve el servo lentamente a la posición 0 (abre la barrera)
      Slot = Slot + 1; // Incrementa el número de plazas disponibles
    }
  }

  // Si tanto la entrada como la salida han sido detectadas
  if (flag1 == 1 && flag2 == 1) {
    delay(1000); // Espera 1 segundo
    moveServoSlowly(100); // Mueve el servo lentamente a la posición 100 (cierra la barrera)
    flag1 = 0; // Reinicia la bandera de entrada
    flag2 = 0; // Reinicia la bandera de salida
  }

  // Muestra el mensaje de bienvenida y el número de plazas disponibles en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("   BIENVENIDO!  ");
  lcd.setCursor(0, 1);
  lcd.print("Espacios Disp: ");
  lcd.print(Slot); // Muestra el número de plazas disponibles
}

void moveServoSlowly(int targetPosition) {
  int currentPosition = servo1.read(); // Lee la posición actual del servo
  if (currentPosition < targetPosition) {
    for (int pos = currentPosition; pos <= targetPosition; pos++) {
      servo1.write(pos);
      delay(10); // Ajusta este valor para cambiar la velocidad (mayor valor = más lento)
    }
  } else {
    for (int pos = currentPosition; pos >= targetPosition; pos--) {
      servo1.write(pos);
      delay(10); // Ajusta este valor para cambiar la velocidad (mayor valor = más lento)
    }
  }
}

BLYNK_WRITE(V0) // Slider Widget for Servo 1 on V0
{
  int pos1 = param.asInt(); // Get value from slider
  servo1.write(pos1); // Set servo 1 position
  Blynk.virtualWrite(V1, pos1);
}
