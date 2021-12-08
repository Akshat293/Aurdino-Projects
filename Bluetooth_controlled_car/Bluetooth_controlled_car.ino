 #include <SoftwareSerial.h>
SoftwareSerial bluetooth(2,3); // RX, TX
char t;
 
void setup() {
  Serial.begin(9600);
bluetooth.begin(9600);
pinMode(10,OUTPUT);   //left motors forward
pinMode(11,OUTPUT);   //left motors reverse
pinMode(12,OUTPUT);   //right motors forward
pinMode(13,OUTPUT);   //right motors reverse
}
 
void loop() {
if(bluetooth.available()>0){
  t = bluetooth.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}
 
else if(t == 'S'){           //STOP (all motors stop)
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}
delay(100);
}
