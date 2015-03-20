int led = 13;

void setup(){
  Serial.begin(9600);
}

void loop(){
/*  Serial.println(digitalRead(0));
  Serial.println(digitalRead(1));
  Serial.println(digitalRead(3));
  Serial.println(digitalRead(4));
  Serial.println(" "); */
  Serial.println(analogRead(A0));
  analogWrite(A5,3500);
  if(abs(analogRead(A0)) < 100){
      analogWrite(A5, 0);
  }
      
  
}
