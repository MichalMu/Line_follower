int predkosc = 110;        // MAX 255
 int zakrecanie = 230;    // MAX 255 
 int opoznienie_skretu = 10;

//L293 Connection
  const int Silnik1A      = 3;
  const int Silnik1B      = 4; 
  const int PWM1  = 9;
  const int Silnik2A      = 6; 
  const int Silnik2B     = 7; 
  const int PWM2  = 10;
  const int v = 12;

//Sensor Connection
  const int left_sensor =A5;
  const int right_sensor =A1;



  int left_odczyt;
  int right_odczyt;

void setup() {
  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(Silnik1A, OUTPUT);
  pinMode(Silnik1B, OUTPUT);
  pinMode(Silnik2A, OUTPUT);
  pinMode(Silnik2B, OUTPUT);
  pinMode(v ,OUTPUT);
  digitalWrite(v, HIGH);
  delay(3000);
  Serial.begin(9600);
  
}

void loop() {


left_odczyt = analogRead(left_sensor);
right_odczyt = analogRead(right_sensor);
//Serial.println("lewy");
//Serial.println(left_odczyt);
Serial.println("prawy");
Serial.println(right_odczyt);
delay(10);
if(right_odczyt > 1000 && left_odczyt < 1000)
{
  digitalWrite (Silnik1A,LOW);
  digitalWrite(Silnik1B,HIGH);
  digitalWrite (Silnik2A,LOW);
  digitalWrite(Silnik2B,HIGH);

  analogWrite (PWM1, predkosc);
  analogWrite (PWM2, 0);

  }
if(right_odczyt < 1000 && left_odczyt > 1000)
{
  digitalWrite (Silnik1A,HIGH);
  digitalWrite(Silnik1B,LOW);
  digitalWrite (Silnik2A,HIGH);
  digitalWrite(Silnik2B,LOW);

  analogWrite (PWM1, 0);
  analogWrite (PWM2, predkosc);

  delay(opoznienie_skretu);
  }

if(right_odczyt > 1000 && left_odczyt > 1000) //forward
{
  digitalWrite (Silnik1A,LOW);
  digitalWrite(Silnik1B,HIGH);
  digitalWrite (Silnik2A,HIGH);
  digitalWrite(Silnik2B,LOW);

  analogWrite (PWM1, predkosc);
  analogWrite (PWM2, predkosc);

  delay(opoznienie_skretu);

  }

if(right_odczyt < 1000 && left_odczyt < 1000) //stop
{

  analogWrite (PWM1, 0);
  analogWrite (PWM2, 0);

  }
}
