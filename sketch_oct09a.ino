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

  int const thres = 945;  //threshold value for peak
  int rounds = 10;        // number of samples
  int lastTime =0,tic, period;        //variables for timing calculation
  
  //We will calculate the period of one pulse by calculating peak to peak
  //By exploiting the peak cap 2nd timing
  //As long as thres is in between the highest peak and second peak of a pulse
  for (int nani =0; nani < rounds; nani++) {
  if (sig>thres )
    {
    while(sig>thres) ;                     //idle waiting for peak to be over
    buzz();                                //buzz for pulse for fun
    tic = millis() ;
    if (lastTime!=0)
       period = period+ (tic-lastTime) ;  //forgo first sample as millis() hasnt been called twice
    lastTime = tic;
    } 
  } 
  
  //calc heart rate
  int heartrate = (rounds-1)*1000*60/period;

  //shine LED accordingly
  if (heartrate >=100 && heartrate <160 )  
     OnOnlyThisLED(YellowLED) ;
  else if (heartrate >= 40 && heartrate <100) 
     OnOnlyThisLED(GreenLED) ;
  else 
     OnOnlyThisLED(RedLED) ;
}

void buzz() {
  //buzz a short 20ms pulse to buzzer
  analogWrite(BUZZPIN, 250);
  delay(20);
  analogWrite(BUZZPIN,0); 
  }


void offAllLEDs() {
  digitalWrite(GreenLED, LOW);
  digitalWrite(YellowLED, LOW) ;
  digitalWrite(RedLED, LOW) ;
  }

void OnOnlyThisLED(int pin) {
  offAllLEDs() ;
  digitalWrite(pin, HIGH) ;
} 
