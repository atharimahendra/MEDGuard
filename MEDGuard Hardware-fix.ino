#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <Keypad_I2C.h>

const int kanan = 5; //servo 1
const int kiri = 4; //Servo 2

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; 
byte colPins[COLS] = {4, 5, 6, 7};
int i2caddress = 0x20;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, i2caddress );

LiquidCrystal_I2C lcd(0x27, 16, 2);

int countKey1Press = 0;
int countKey2Press = 0;

bool buttonA_pressed = false;
bool buttonB_pressed = false;

void setup(){
  beginLiquidCrystal();
  beginKeypad();
  pinMode(kanan, OUTPUT);
  pinMode(kiri, OUTPUT);
  digitalWrite(kanan, LOW);
  digitalWrite(kiri, LOW);
  pinMode(16, OUTPUT);
}

void beginKeypad(){
  Serial.begin(9600);
  Wire.begin(0, 2);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ENTER YOUR CODE!");
  lcd.setCursor(0, 1);
  kpd.begin();
};
  
void beginLiquidCrystal(){
  Wire.begin(4, 5);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
};

void buzzer(){
  digitalWrite(16, 1);
  delay(20);
  digitalWrite(16, 0);
}

void loop(){
  char key = kpd.getKey();
  
  if (key){
    Serial.println(key);
    lcd.print(key);
    buzzer();
  
    if (key == '*'){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER YOUR CODE!");
      lcd.setCursor(0, 1);
    }

    if (key == '1') {
      countKey1Press++;
      if (countKey1Press == 4) {
        analogWrite(3, 255);
        digitalWrite(kanan, HIGH);
        delay(2000);
        analogWrite(3, 0);
        digitalWrite(kanan, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER YOUR CODE!");
        lcd.setCursor(0, 1);
        countKey1Press = 0;
      }
      else{
        analogWrite(3, 0);
        digitalWrite(kanan, LOW);
      }
    }

    if (key == '2') {
      countKey2Press++;
      if (countKey2Press == 4){
        analogWrite(2, 255);
        digitalWrite(kiri, HIGH);
        delay(2000);
        analogWrite(2, 0);
        digitalWrite(kiri, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER YOUR CODE!");
        lcd.setCursor(0, 1);
        countKey2Press = 0;
      }
      else{
        analogWrite(2, 0);
        digitalWrite(kiri, LOW);
      }
    }
  }
}

//d0(GPIO 16) = Buzzer
//d1 (GPIO 5) = servo 1
//d2 (GPIO 4) = servo 2
//d3 (GPIO 0) = PWM servo 1
//d4 (GPIO 2) = PWM servo 2
//d5 (GPIO 14) = SDA Keypad & I2C
//d6 (GPIO 12) = SCL Keypad & I2C