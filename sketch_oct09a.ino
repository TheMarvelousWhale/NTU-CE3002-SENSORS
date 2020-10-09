#define BUZZPIN 8
#define GreenLED 7
#define YellowLED 6
#define RedLED 5 

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZPIN,OUTPUT);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(YellowLED,OUTPUT);
 Serial.begin(1200);
}

int sig;
void loop() {
  // put your main code here, to run repeatedly:

  sig=analogRead(A0);
  Serial.println(sig);
  if (sig > 945)
    buzz();
    delay(400);

  
}

void buzz() {
  analogWrite(BUZZPIN, 250);
  delay(20);
  analogWrite(BUZZPIN,0); 
  }


void blinkLED(int pin) {
  
  }
  
