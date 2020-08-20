
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  //delay(300);
  Serial.begin(9600);

}

void loop() {
  Serial.print("Lewy czujnik: ");
  Serial.println(analogRead(A0));
Serial.print("prawy czujnik: ");
  Serial.println(analogRead(A1));
 

if(analogRead(A0)  > 3){
    digitalWrite(13, HIGH);}
  else{
    digitalWrite(13, LOW);
  }
if(analogRead(A1) > 3){
    digitalWrite(12, HIGH);}
  else{
    digitalWrite(12, LOW);
  }

if(analogRead(A1) > 3 && analogRead(A0) < 3){
  digitalWrite (3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite (6,LOW);
  digitalWrite(7,HIGH);
}

else if(analogRead(A1) < 3 && analogRead(A0)>3){
  digitalWrite (3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite (6,HIGH);
  digitalWrite(7,LOW);
}

else if(analogRead(A1)>3 && analogRead(A0)>3){
  digitalWrite (3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite (6,HIGH);
  digitalWrite(7,LOW);
}

else if(analogRead(A1)<3 && analogRead(A0)<3){
  digitalWrite (3,LOW);
  digitalWrite(4,LOW);
  digitalWrite (6,LOW);
  digitalWrite(7,LOW);
}

}
