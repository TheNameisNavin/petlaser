#include <Servo.h>

#define servo_pin_x 9
#define servo_pin_y 3

Servo myServox;
Servo myServoy;

int speed = 50;

void setup() {

    myServox.attach(servo_pin_x);  
    myServox.write(0);
    myServoy.attach(servo_pin_y);
    myServoy.write(0);
    delay(3000);
}


void loop() {

      for(int i=0; i<=90; i++){
      myServox.write(i);
      myServoy.write(i);
      delay(speed);
    }

    while (true){}

}

