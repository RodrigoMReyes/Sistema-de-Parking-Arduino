// Rodrigo Manuel Reyes Cordova

#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD con I2C
LiquidCrystal_I2C lcd(0x27,16,2); // Inicializa el objeto lcd con la dirección I2C 0x27, y define una pantalla de 16x2

#include <Servo.h> // Biblioteca para controlar el servo
Servo myservo; // Crea un objeto servo

int IR1 = 2; // Pin de entrada para el sensor IR1
int IR2 = 3; // Pin de entrada para el sensor IR2

int MaxSlots = 4; // Cantidad máxima de plazas de estacionamiento
int Slot = 4; // Contador de plazas de estacionamiento
int flag1 = 0; // Bandera para indicar la entrada de un coche
int flag2 = 0; // Bandera para indicar la salida de un coche

void setup() {
  Serial.begin(9600); // Inicia la comunicación serie a 9600 baudios
  
  lcd.init(); // Inicializa la pantalla LCD
  lcd.backlight(); // Enciende la luz de fondo de la pantalla LCD

  pinMode(IR1, INPUT); // Configura el pin del sensor IR1 como entrada
  pinMode(IR2, INPUT); // Configura el pin del sensor IR2 como entrada
  
  myservo.attach(4); // Conecta el servo al pin 4
  myservo.write(100); // Mueve el servo a la posición 100 (posición cerrada)

  // Muestra el mensaje de bienvenida en la pantalla LCD
  lcd.setCursor(0,0); 
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0,1);
  lcd.print(" SISTEMA DE PARQ ");
  delay(2000); // Espera 2 segundos
  lcd.clear(); // Limpia la pantalla LCD
}

void loop() { 
  // Detecta si un coche está entrando
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) { // Si hay plazas disponibles
      flag1 = 1; // Marca la entrada de un coche
      if (flag2 == 0) { // Si no hay coche saliendo al mismo tiempo
        moveServoSlowly(0); // Mueve el servo lentamente a la posición 0 (abre la barrera)
        Slot = Slot - 1; // Decrementa el número de plazas disponibles
      }
    } else { // Si no hay plazas disponibles
      lcd.setCursor(0,0);
      lcd.print("   LO SIENTO :( ");  
      lcd.setCursor(0,1);
      lcd.print(" ESTAC. LLENO  "); 
      delay(3000); // Espera 3 segundos
      lcd.clear(); // Limpia la pantalla LCD
    }
  }

  // Detecta si un coche está saliendo
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1; // Marca la salida de un coche
    if (flag1 == 0 && Slot != MaxSlots) { // Si no hay coche entrando al mismo tiempo y no está lleno
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
  lcd.setCursor(0,0);
  lcd.print("   BIENVENIDO!  ");
  lcd.setCursor(0,1);
  lcd.print("Espacios Disp: ");
  lcd.print(Slot); // Muestra el número de plazas disponibles
}

void moveServoSlowly(int targetPosition) {
  int currentPosition = myservo.read(); // Lee la posición actual del servo
  if (currentPosition < targetPosition) {
    for (int pos = currentPosition; pos <= targetPosition; pos++) {
      myservo.write(pos);
      delay(10); // Ajusta este valor para cambiar la velocidad (mayor valor = más lento)
    }
  } else {
    for (int pos = currentPosition; pos >= targetPosition; pos--) {
      myservo.write(pos);
      delay(10); // Ajusta este valor para cambiar la velocidad (mayor valor = más lento)
    }
  }
}
