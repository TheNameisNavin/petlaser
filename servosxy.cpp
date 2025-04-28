#include <Servo.h>

#define servo_pin_x 9
#define servo_pin_y 3
#define LASER_PIN 5

Servo myServox;  
Servo myServoy;

int min_deg_x= 45;
int max_deg_x= 135;
int min_deg_y= 35;
int max_deg_y= 80;
int min_x=-100;
int max_x= 100;
int min_y=-100;
int max_y= 100;


int position_x = 90;
int position_y = 90;

int target_x = 0;
int target_y = 0;



int angle_rate = 15; 
int time_angle_rate = 150; 

struct coord {
  int x;
  int y;
};

//Here is where you can input the coordinates you want, manually or using AI.
coord shape [] = {

{50, 0}, {49, 6}, {48, 12}, {46, 18}, {43, 24}, {40, 29}, {36, 34}, {31, 38}, {26, 42}, {21, 45}, 
{15, 47}, {9, 49}, {3, 49}, {-3, 49}, {-9, 49}, {-15, 47}, {-21, 45}, {-26, 42}, {-31, 38}, {-36, 34}, 
{-40, 29}, {-43, 24}, {-46, 18}, {-48, 12}, {-49, 6}, {-50, 0}, {-49, -6}, {-48, -12}, {-46, -18}, {-43, -24}, 
{-40, -29}, {-36, -34}, {-31, -38}, {-26, -42}, {-21, -45}, {-15, -47}, {-9, -49}, {-3, -49}, {3, -49}, {9, -49}, 
{15, -47}, {21, -45}, {26, -42}, {31, -38}, {36, -34}, {40, -29}, {43, -24}, {46, -18}, {48, -12}, {49, -6},
{25, 0}, {24, 3}, {24, 6}, {23, 9}, {21, 12}, {20, 14}, {18, 17}, {15, 19}, {13, 21}, {10, 22}, 
{7, 23}, {4, 24}, {1, 24}, {-1, 24}, {-4, 24}, {-7, 23}, {-10, 22}, {-13, 21}, {-15, 19}, {-18, 17}, 
{-20, 14}, {-21, 12}, {-23, 9}, {-24, 6}, {-24, 3}, {-25, 0}, {-24, -3}, {-24, -6}, {-23, -9}, {-21, -12}, 
{-20, -14}, {-18, -17}, {-15, -19}, {-13, -21}, {-10, -22}, {-7, -23}, {-4, -24}, {-1, -24}, {1, -24}, 
{4, -24}, {7, -23}, {10, -22}, {13, -21}, {15, -19}, {18, -17}, {20, -14}, {21, -12}, {23, -9}, {24, -6}, {24, -3},
{-50, 0}, {-40, 0}, {-40, 10}, {-30, 10}, {-30, 20}, {-20, 20}, {-20, 30}, {-10, 30}, {-10, 40}, {0, 40}, 
{0, 50}, {10, 50}, {10, 60}, {20, 60}, {20, 70}, {30, 70}, {30, 80}, {40, 80}, {40, 90}, {50, 90}, 
{50, 100}, {60, 100}
};



void setup() {

    Serial.begin(9600);
    myServox.attach(servo_pin_x);   
    myServox.write(position_x);

    myServoy.attach(servo_pin_y);
    myServoy.write(position_y);
    delay(500);
    pinMode(LASER_PIN, OUTPUT);
    digitalWrite(LASER_PIN, HIGH);
}

void loop() {
 
  int shape_point_qty = sizeof(shape)/sizeof(shape[0]);
  for (int i = 0; i < shape_point_qty ; i++){
    target_x = map(shape[i].x,min_x,max_x,min_deg_x,max_deg_x);
    target_y = map(shape[i].y,min_y,max_y,min_deg_y,max_deg_y);

    move_servos();

  }
  
}


void move_servos(){ 

  bool flag_x = true;
  bool flag_y = true;
  
  while (flag_x || flag_y){
    //

    if(position_x == target_x){
      flag_x = false;
    }

   if(position_y == target_y){
      flag_y = false;
    }

    if (position_x < target_x) { 

      position_x += angle_rate;
      if (position_x > target_x){
        position_x = target_x;
        flag_x=false;
      }


    }

    if (position_y < target_y){ 

          position_y += angle_rate;
          if (position_y > target_y){
            position_y = target_y;
            flag_y=false;
            }

    }

    if (position_y > target_y){ 

      position_y -= angle_rate;
      if (position_y < target_y){
        position_y = target_y;
        flag_y=false;
      }      

    }



    if (position_x > target_x){ 

      position_x -= angle_rate;
      if (position_x < target_x){
        position_x = target_x;
        flag_x=false;
      }

    }

    myServox.write(position_x);
    myServoy.write(position_y);
    delay (time_angle_rate); 

  }
    

}
