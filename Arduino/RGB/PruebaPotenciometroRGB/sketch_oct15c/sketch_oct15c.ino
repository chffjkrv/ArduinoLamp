
#include <math.h>

const int analogPinR = A0;    //Declaramos los pines analógicos.
const int analogPinG = A1;
const int analogPinB = A2;
const int analogPinTemp = A3;

const int ledR = 11;    //Declaramos los pines dígitales.
const int ledG = 9;
const int ledB = 10;
const int touch = 2;

int touchFlag = 0;
int varTouchFlag = 0;

int R;      //variable que almacena la lectura analógica raw
int G;
int B;

int positionR;   //posicion del potenciometro en tanto por ciento
int positionG;
int positionB;


double Thermistor(int RawADC) {

  double Temp;
  Temp = log(10000.0 / (1024.0 / RawADC - 1));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}

void setup() {
  Serial.begin(9600);

  pinMode(analogPinR, INPUT);
  pinMode(analogPinG, INPUT);
  pinMode(analogPinB, INPUT);
  pinMode(analogPinTemp, INPUT);
  pinMode(touch, INPUT);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {

  R = analogRead(analogPinR);          // realizar la lectura analógica raw
  G = analogRead(analogPinG);
  B = analogRead(analogPinB);

  positionR = map(R, 0, 1023, 0, 255);  // convertir a porcentaje
  positionG = map(G, 0, 1023, 0, 255);
  positionB = map(B, 0, 1023, 0, 255);
  touchFlag = digitalRead(touch);

  int readVal = analogRead(analogPinTemp);
  double temp =  Thermistor(readVal);
  temp = temp * (-1);
  Serial.println(temp);  // display tempature
  //Serial.println(readVal);  // display tempature

  if (touchFlag == HIGH) {
    varTouchFlag = !varTouchFlag;
    if (varTouchFlag == HIGH) {

      analogWrite(ledR, positionR);
      analogWrite(ledG, positionG);
      analogWrite(ledB, positionB);

    } else {
      analogWrite(ledR, 0);
      analogWrite(ledG, 0);
      analogWrite(ledB, 0);
    }
  }




  delay(10);
}
