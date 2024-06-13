#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Configuración del LCD con dirección 0x27, 16 columnas y 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaración del servo motor
Servo myservo;

// Pines para los sensores infrarrojos
const int IR1 = 2;
const int IR2 = 3;

// Número total de plazas de estacionamiento disponibles
int Slot = 4;

int flag1 = 0; // Bandera para el sensor de entrada
int flag2 = 0; // Bandera para el sensor de salida

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial

  lcd.init(); // Inicializar el LCD
  lcd.backlight(); // Encender la luz de fondo del LCD

  // Configurar los pines de los sensores IR como entradas
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Conectar el servo motor al pin 4 y moverlo a la posición inicial (100 grados)
  myservo.attach(4);
  myservo.write(100);

  // Mensaje inicial en el LCD
  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Verificar si el sensor IR1 detecta un vehículo (LOW) y la bandera está baja
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) { // Si hay plazas disponibles
      flag1 = 1; // Activar la bandera de entrada
      if (flag2 == 0) { // Si el vehículo no está saliendo
        myservo.write(0); // Abrir la barrera
        delay(1000); // Esperar un segundo para que el vehículo pase
        myservo.write(100); // Cerrar la barrera
        Slot = Slot - 1; // Disminuir el número de plazas disponibles
      }
    } else { // Si no hay plazas disponibles
      // Mostrar mensaje de "Parking Full" en el LCD
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }

  // Verificar si el sensor IR2 detecta un vehículo saliendo (LOW) y la bandera está baja
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1; // Activar la bandera de salida
    if (flag1 == 0) { // Si el vehículo no está entrando
      myservo.write(0); // Abrir la barrera
      delay(1000); // Esperar un segundo para que el vehículo pase
      myservo.write(100); // Cerrar la barrera
      Slot = Slot + 1; // Aumentar el número de plazas disponibles
      // Asegurarse de que Slot no exceda el número total de plazas
      if (Slot > 4) Slot = 4;
    }
  }

  // Resetear las banderas si no hay vehículos detectados
  if (digitalRead(IR1) == HIGH) {
    flag1 = 0;
  }
  if (digitalRead(IR2) == HIGH) {
    flag2 = 0;
  }

  // Mostrar el mensaje de bienvenida y el número de plazas disponibles en el LCD
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
}
