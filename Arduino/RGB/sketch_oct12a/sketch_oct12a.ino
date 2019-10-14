#include <SoftwareSerial.h> //Esta librería nos permite establecer pines digitales para comunicacione en serie

SoftwareSerial miBt(10, 11); //  RX / TX

int Rp = 2;
int Gp = 3;
int Bp = 4;
int t = 80;
int dato = 0;

void setup() {
  pinMode(Rp, OUTPUT);
  pinMode(Gp, OUTPUT);
  pinMode(Bp, OUTPUT);
  miBt.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 bps

}

void loop() {
  if (miBt.available()) {
    dato = miBt.read();

    if (dato == '0')
      RGB_color(255, 0, 0); //Rojo 0

    if (dato == '1')
      RGB_color(0, 255, 0); //Verde 1

    if (dato == '2')
      RGB_color(0, 0, 255); //Azul 2

    if (dato == '3')
      RGB_color(255, 0, 255); //Morado 3

    if (dato == '4')
      RGB_color(0, 255, 255); //Cian 4

    if (dato == '5')
      RGB_color(250, 0, 80); //Magenta 5

    if (dato == '6')
      RGB_color(255, 255, 125); //Amarillo 6

    if (dato == '7')
      RGB_color(255, 255, 255); //Blanco 7

    if (dato == '8')
      
            RGB_color(random(255), random(255), random(255)); //Random 8

      }
  }



void RGB_color(int RpValor, int GpValor, int BpValor) {
  analogWrite(Rp, RpValor);
  analogWrite(Gp, GpValor);
  analogWrite(Bp, BpValor);
}
