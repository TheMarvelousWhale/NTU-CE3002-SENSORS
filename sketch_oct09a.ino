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

  int const thres = 945;
  int rounds = 10;
  int lastTime =0,tic, period;
  for (int nani =0; nani < rounds; nani++) {
  if (sig>thres )
    {
    while(sig>thres) ;
    buzz();
    tic = millis() ;
    if (lastTime!=0)
       period = period+ (tic-lastTime) ;
    lastTime = tic;
    } 
  } 
   
  int heartrate = (rounds-1)*1000*60/period;
  if (heartrate >=100 && heartrate <160 )  
     OnOnlyThisLED(YellowLED) ;
  else if (heartrate >= 40 && heartrate <100) 
     OnOnlyThisLED(GreenLED) ;
  else 
     ONonlyThisLED(RedLED) ;
}

void buzz() {
  analogWrite(BUZZPIN, 250);
  delay(20);
  analogWrite(BUZZPIN,0); 
  }


void offAllLEDs() {
  digitalWrite(GreenLED, LOW);
  digitalWrite(YellowLED, LOW) ;
  digitalWrite(GreenLED, LOW) ;
  }

void OnOnlyThisLED(int pin) {
  offAllLEDs() ;
  digitalWrite(pin, HIGH) ;
} 
