// www.elegoo.com
// Roksolana Amarova
// 2IZB
// 2019/05/18

#include <Servo.h>  // include servo library
Servo myservo;      // create servo object to control servo

// define pin numbers for 5 ultrasonic sensors  
int Echo = A4;  
int Trig = A5; 

int Echo_right = 53;
int Trig_right = 52;

int Echo_left = 51;
int Trig_left = 50;

int Echo_left_back = 48;
int Trig_left_back = 49;

int Echo_right_back = 46;
int Trig_right_back = 47;

// define pin numbers for the car wheels
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//define speed for the car
#define carSpeed 175

// create variables as integers
int carSpeed_forward_left_side = 70;
int carSpeed_forward_right_side = 55;

int rightDistanceForward = 0, leftDistanceForward = 0, middleDistanceForward = 0; 
int rightDistanceMiddle = 0, leftDistanceMiddle = 0;
int rightDistanceBack = 0, leftDistanceBack = 0;

//function to move the car forward
void forward(){
  analogWrite(ENA, carSpeed_forward_left_side);//left wheels
  analogWrite(ENB, carSpeed_forward_right_side);//right wheels
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}
//function to move the car back
void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

//function to turn the car on the left
void left() {
  analogWrite(ENA, carSpeed-10);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}

//function to turn the car on the right
void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed-10);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

//function to stop the car
void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 

//Ultrasonic distance measurement functions for each ultrasonic sensors

int Distance_test_forward() {
  digitalWrite(Trig, LOW); // Clears the trigPin 
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH); // sets the trigPin on HIGH state for 10 microseconds  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH); // reads the echoPin, returns the sound wave travel time in microseconds 
  Fdistance = Fdistance / 58; //diatance = (speed of sound(340m/s)*time taken(Fdistance))/2       
  return (int)Fdistance; //function return calculated distance
}  
int Distance_test_left_middle() {
  digitalWrite(Trig_left, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig_left, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig_left, LOW);   
  float Ldistance = pulseIn(Echo_left, HIGH);  
  Ldistance= Ldistance / 58;       
  return (int)Ldistance;
}

int Distance_test_right_middle() {
  digitalWrite(Trig_right, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig_right, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig_right, LOW);   
  float Rdistance = pulseIn(Echo_right, HIGH);  
  Rdistance= Rdistance / 58;       
  return (int)Rdistance;
} 


int Distance_test_left_back() {
  digitalWrite(Trig_left_back, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig_left_back, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig_left_back, LOW);   
  float Rdistance = pulseIn(Echo_left_back, HIGH);  
  Rdistance= Rdistance / 58;       
  return (int)Rdistance;
}
int Distance_test_right_back() {
  digitalWrite(Trig_right_back, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig_right_back, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig_right_back, LOW);   
  float Rdistance = pulseIn(Echo_right_back, HIGH);  
  Rdistance= Rdistance / 58;       
  return (int)Rdistance;
}

void setup() { 
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600); // Starts the serial communication

  // Sets the Pins as an Output or as an Input
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(Echo_left, INPUT);    
  pinMode(Trig_left, OUTPUT);  
  pinMode(Echo_right, INPUT);    
  pinMode(Trig_right, OUTPUT); 
  
  pinMode(Echo_left_back, INPUT);    
  pinMode(Trig_left_back, OUTPUT);  
  pinMode(Echo_right_back, INPUT);    
  pinMode(Trig_right_back, OUTPUT); 
    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
  
} 

void loop() { 
 
    myservo.write(85);  //set servo position according to scaled value
   
    middleDistanceForward = Distance_test_forward(); //measure middle distance using ultrasonic sensor that is ahead
    rightDistanceMiddle = Distance_test_right_middle(); //measure right distance using right middle ultrasonic sensor
    leftDistanceMiddle = Distance_test_left_middle(); //measure right distance using left middle ultrasonic sensor
    

  //if the forward distance is more or equal than 5 cm 
  if(middleDistanceForward >= 5)    
  {
    
    rightDistanceBack = Distance_test_right_back();
    
    if (rightDistanceMiddle > 15 && rightDistanceBack > 15)
    {
        right();
        delay(400);
        
        stop();
        delay(200);
        
        leftDistanceMiddle = Distance_test_left_middle();
        leftDistanceBack = Distance_test_left_back();
        rightDistanceMiddle = Distance_test_right_middle();
        rightDistanceBack = Distance_test_right_back();
       
        
        //turn the car on the right by 90 degrees 
        while (leftDistanceMiddle != leftDistanceBack && rightDistanceMiddle != rightDistanceBack)
        {
            right();
            delay(50);
            stop();
            delay(100);
            
            leftDistanceMiddle = Distance_test_left_middle();
            leftDistanceBack = Distance_test_left_back();
            rightDistanceMiddle = Distance_test_right_middle();
            rightDistanceBack = Distance_test_right_back();
        
        }

        forward();
        delay(1000);
        
        
    }
    //driving straight and always level the car using right and left middle ultrasonic sensors
    if (rightDistanceMiddle < 10)
     {    //if the rightDistanceMiddle is less than 10cm then move the car forward tilted to the left side
          carSpeed_forward_left_side = 70 - 10;//decrease the speed of the left wheels
          carSpeed_forward_right_side = 55 + 30; //increase the speed of the right wheels
          forward();
     }
        
    else if(leftDistanceMiddle < 10)
        {
          //if the leftDistanceMiddle is less than 10cm then move the car forward tilted to the right side
          carSpeed_forward_left_side = 70 + 30; //increase the speed of the left wheels
          carSpeed_forward_right_side = 55 - 10; //decrease the speed of the right wheels
          forward();
    }
          
    else
    {
       //if the leftDistanceMiddle and rightDistanceMiddle are equal then drive the car straight 
       carSpeed_forward_left_side = 70; 
       carSpeed_forward_right_side = 55;
       forward();
    }
      
  }
  
    // If the forward distance is less than 5 cm then stop the car and check the distance to the right side and left side
    //by turning the ultrasonic sensor, with the help of a servo motor
    else if(middleDistanceForward < 5) 
    {
        stop();      
        delay(500);
        myservo.write(0);          
        delay(500);  
        rightDistanceForward = Distance_test_forward();   
        delay(100);
        
        myservo.write(85);              
        delay(500); 
        middleDistanceForward = Distance_test_forward();      
        delay(100);   
                                               
        myservo.write(180);              
        delay(500); 
        leftDistanceForward = Distance_test_forward();      
        delay(100);
        myservo.write(85);              
        delay(500);

   
      //if right distance >=15 then turn the car on the right by 90 degrees
      if(rightDistanceForward  >= 15 && leftDistanceForward <= 15 )
      {
        right();
        delay(400);
        
        stop();
        delay(200);
        
        leftDistanceMiddle = Distance_test_left_middle();
        leftDistanceBack = Distance_test_left_back();
        rightDistanceMiddle = Distance_test_right_middle();
        
        rightDistanceBack = Distance_test_right_back();
       
        
        //turn the car on the right by 90 degrees 
        while (leftDistanceMiddle != leftDistanceBack && rightDistanceMiddle != rightDistanceBack)
        {
            right();
            delay(50);
            stop();
            delay(100);
            
            leftDistanceMiddle = Distance_test_left_middle();
            leftDistanceBack = Distance_test_left_back();
            rightDistanceMiddle = Distance_test_right_middle();
            rightDistanceBack = Distance_test_right_back();
        
            Serial.print("left_Middle: ");
            Serial.println(leftDistanceMiddle);
        
            Serial.print("left_Back: ");
            Serial.println(leftDistanceBack);
            Serial.print("right_Middle: ");
            Serial.println(rightDistanceMiddle);
        
            Serial.print("right_Back: ");
            Serial.println(rightDistanceBack);
        }
       forward();
       delay(1000);
       
       }
       //if left distance >=15 then turn the car on the left by 90 degrees
       else if(rightDistanceForward  <= 15 && leftDistanceForward >= 15 )
      {
        left();
        delay(400);
        
        stop();
        delay(200);
        //measure distances
        leftDistanceMiddle = Distance_test_left_middle();
        leftDistanceBack = Distance_test_left_back();
        rightDistanceMiddle = Distance_test_right_middle();
        rightDistanceBack = Distance_test_right_back();
       
        
        //turn the car on the left by 90 degrees 
        while (leftDistanceMiddle != leftDistanceBack && rightDistanceMiddle != rightDistanceBack)
        {
            left();
            delay(50);
            stop();
            delay(100);
            //measure distances
            leftDistanceMiddle = Distance_test_left_middle();
            leftDistanceBack = Distance_test_left_back();
            rightDistanceMiddle = Distance_test_right_middle();
            rightDistanceBack = Distance_test_right_back();
        
        }

        forward();
        delay(1000);
      }
         //if right distance >=15 and left distance >=15 then turn the car on the left by 90 degrees
        else if(rightDistanceForward  >= 15 && leftDistanceForward >= 15 )
      {
        right();
        delay(400);
        stop();
        delay(200);

        //measure distances
        leftDistanceMiddle = Distance_test_left_middle();
        leftDistanceBack = Distance_test_left_back();
        rightDistanceMiddle = Distance_test_right_middle();
        rightDistanceBack = Distance_test_right_back();
       
        
        //turn the car on the left by 90 degrees 
        while (leftDistanceMiddle != leftDistanceBack && rightDistanceMiddle != rightDistanceBack)
        {
            right();
            delay(50);
            stop();
            delay(100);
            
            //measure distances
            leftDistanceMiddle = Distance_test_left_middle();
            leftDistanceBack = Distance_test_left_back();
            rightDistanceMiddle = Distance_test_right_middle();
            rightDistanceBack = Distance_test_right_back();
        
        }

        forward();
        delay(1000);
      
       }

       else if(rightDistanceForward  <= 15 && leftDistanceForward <= 15 )
      {
        back();
        delay(100);
        stop();
        delay(200);

        myservo.write(180);              
        delay(500); 
        leftDistanceForward = Distance_test_forward();   
        
        

        while (leftDistanceForward < 15)
        {
            back();
            delay(50);
            stop();
            delay(100);
            
            //measure distances
            leftDistanceForward = Distance_test_forward();
        }
        myservo.write(85);              
        delay(500); 
        stop();
        delay(200);
        left();
        delay(400);
        stop();
        delay(200);

        //measure distances
        leftDistanceMiddle = Distance_test_left_middle();
        leftDistanceBack = Distance_test_left_back();
        rightDistanceMiddle = Distance_test_right_middle();
        rightDistanceBack = Distance_test_right_back();
       
        
        //turn the car on the left by 90 degrees 
        while (leftDistanceMiddle != leftDistanceBack && rightDistanceMiddle != rightDistanceBack)
        {
            left();
            delay(50);
            stop();
            delay(100);
            
            //measure distances
            leftDistanceMiddle = Distance_test_left_middle();
            leftDistanceBack = Distance_test_left_back();
            rightDistanceMiddle = Distance_test_right_middle();
            rightDistanceBack = Distance_test_right_back();
        
        }

        forward();
        delay(1000);
      
       }
       


       
    }
         
}




    
                           
