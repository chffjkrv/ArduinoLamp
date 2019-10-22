
#include <math.h>

const int analogPinR = A0;    //Declaramos los pines analógicos.
const int analogPinG = A1;
const int analogPinB = A2;
const int analogPinTemp = A3;

const int ledR = 11;    //Declaramos los pines dígitales.
const int ledG = 9;
const int ledB = 10;
const int touch = 2;
const int ledTOUCHON = 13;

int touchFlag = 0;
int varTouchFlag = 0;

int R;      //variable que almacena la lectura analógica raw
int G;
int B;

int r = 0;
int v = 0;
int a = 0;

int t; //Variable que recoge la temperatura en int.
double temp; //Variable que recoge la temperatura en double.

int positionR;   //posicion del potenciometro en tanto por ciento
int positionG;
int positionB;


void setup() {
  Serial.begin(9600);

  pinMode(analogPinR, INPUT);
  pinMode(analogPinG, INPUT);
  pinMode(analogPinB, INPUT);
  pinMode(analogPinTemp, INPUT);
  pinMode(touch, INPUT);

  pinMode(ledTOUCHON, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {

  touchFlag = digitalRead(touch);
  int readVal = analogRead(analogPinTemp);
  temp =  Thermistor(readVal);
  temp = temp * (-1);
  t = (int)temp;
  Serial.print(t);
  Serial.print("\n");
  control(t);

  //Serial.println(temp);  // display tempature
  //Serial.println(readVal);  // display tempature
  /**
    if (touchFlag == HIGH) {
      varTouchFlag = !varTouchFlag;
      delay(500);

      if (varTouchFlag == HIGH) {

        digitalWrite(ledTOUCHON, HIGH);
        control(t);
        delay(10);

      } else {
        digitalWrite(ledTOUCHON, LOW);
        digitalWrite(ledR, LOW);
        digitalWrite(ledB, LOW);
      }
    }*/

  delay(1);
}



void control(int temp)
{
  int r2, v2, a2;
  if (t <= 5)
  {
    r2 = 150;
    v2 = 150;
    a2 = 150;
  }
  else if (t > 35)
  {
    r2 = 255;
    v2 = 0;
    a2 = 0;
  }
  else if (t > 5 && t <= 10)
  {
    r2 = t * 10 + 100;
    v2 = t * 15;
    a2 = t * 15 + 100;
  }
  else if (t > 30 && t <= 35)
  {
    r2 = (t - 30) * 10 + 200;
    v2 = 50 - (t - 30) * 10;
    a2 = 0;
  }
  else if (t > 25 && t <= 30)
  {
    r2 = 250 - 10 * (t - 25);
    v2 = 150 - 20 * (t - 25);
    a2 = 0;
  }
  else if (t > 20 && t <= 25)
  {
    r2 = 50 * (t - 20);
    v2 = 250 - 20 * (t - 20);
    a2 = 0;
  }
  else if (t > 15 && t <= 20)
  {
    if (t == 16)
    {
      r2 = 150;
      v2 = 0;
      a2 = 200;
    }
    else if (t == 17)
    {
      r2 = 250;
      v2 = 0;
      a2 = 200;
    }
    else if (t == 18)
    {
      r2 = 0;
      v2 = 0;
      a2 = 250;
    }
    else if (t == 19)
    {
      r2 = 50;
      v2 = 250;
      a2 = 50;
    }
    else
    {
      r2 = 0;
      v2 = 250;
      a2 = 0;
    }
  }
  else if (t > 10 && t <= 15)
  {
    r2 = 200 - 20 * (t - 10);
    v2 = 150 - 30 * (t - 10);
    a2 = 250;
  }
  else
  {
    r2 = 0;
    v2 = 0;
    a2 = 0;
  }

  if (r == r2 && v == v2 && a == a2)
    Serial.println("La temperatura no a cambiado");
  else
    color(r2, v2, a2);
}

void color(int r2, int v2, int a2)
{
  int i;
  int nega[3];
  int mayor = 0;
  int temp[3];
  int men1;
  int men2;


  temp[0] = r2 - r;
  temp[1] = v2 - v;
  temp[2] = a2 - a;

  for (i = 0; i < 3; i++)
  {
    if (temp[i] < 0)
    {
      temp[i] = -1 * temp[i];
      nega[i] = 1;
    }
    else
      nega[i] = 0;
  }

  for (i = 0; i < 3; i++)
    if (mayor < temp[i])
      mayor = temp[i];

  for (i = 0; i < mayor; i++)
  {
    analogWrite(ledR, r);
    analogWrite(ledG, v);
    analogWrite(ledB, a);

    if (mayor == temp[0])
    {
      men1 = mayor / temp[1];
      men2 = mayor / temp[2];
      if (i % men1 == 0 && v != v2)
        if (nega[1] == 0)
          v++;
        else
          v--;

      if (i % men2 == 0 && a != a2)
        if (nega[2] == 0)
          a++;
        else
          a--;

      if (nega[0] == 0)
        r++;
      else
        r--;
    }

    else if (mayor == temp[1])
    {
      men1 = mayor / temp[0];
      men2 = mayor / temp[2];
      if (i % men1 == 0 && r != r2)
        if (nega[0] == 0)
          r++;
        else
          r--;

      if (i % men2 == 0 && a != a2)
        if (nega[2] == 0)
          a++;
        else
          a--;

      if (nega[1] == 0)
        v++;
      else
        v--;
    }

    else
    {
      men1 = mayor / temp[0];
      men2 = mayor / temp[1];
      if (i % men1 == 0 && r != r2)
        if (nega[0] == 0)
          r++;
        else
          r--;

      if (i % men2 == 0 && v != v2)
        if (nega[1] == 0)
          v++;
        else
          v--;

      if (nega[2] == 0)
        a++;
      else
        a--;
    }

    delay(15);
  }
}


double Thermistor(int RawADC) {

  double Temp;
  Temp = log(10000.0 / (1024.0 / RawADC - 1));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}
