#define BUZZPIN 8
#define RedLED 7
#define YellowLED 6
#define GreenLED  5

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZPIN,OUTPUT);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(YellowLED,OUTPUT);
 Serial.begin(1200);
}

int sig;
void detect() {
  // put your main code here, to run repeatedly:
  
  sig=analogRead(A0);
  Serial.println(sig);
  
  int const thres = 945;  //threshold value for peak
  int rounds = 10;        // number of samples
  int lastTime =0,tic, period;        //variables for timing calculation
  int prev = sig;
  //We will calculate the period of one pulse by calculating peak to peak
  //By exploiting the peak cap 2nd timing
  //As long as thres is in between the highest peak and second peak of a pulse
  for (int nani =0; nani < rounds; nani++) {
  
  sig=analogRead(A0);
  if (sig>=thres)
    {
    //Serial.print("BUZZ");
    while(sig>=thres)
        sig=analogRead(A0);                     //idle waiting for peak to be over
    buzz();                                //buzz for pulse for fun
    tic = millis() ;
    if (lastTime!=0){
       period = period + (tic-lastTime) ;  //forgo first sample as millis() hasnt been called twice
       //Serial.print("Period is: ");Serial.println(period);
    }
    lastTime = tic;
   }
  else {
    while(sig < thres)
      sig=analogRead(A0);     
    } 
   //Serial.print("Iter :");Serial.println(nani);
  } 
  
  //calc heart rate
  
  int heartrate = (rounds-1)*1000*60/period;
  Serial.print("Heart rate is: ");Serial.println(heartrate);
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


void loop() {
  int last = 0,period = 0,now;
  while(1){
  sig = analogRead(A0);
  Serial.println(sig);
  if(sig>945) 
   {
        while(sig > 945){
          sig = analogRead(A0);
          Serial.println(sig);
        }
        buzz();
        now = millis();
        period = 0.7*period + 0.3*(now-last);
        last = now;
        int heartrate = 60000/period;
        //Serial.print("Heart rate is: ");Serial.println(heartrate);
        //shine LED accordingly
        if (heartrate >=100 && heartrate <160 )  
           OnOnlyThisLED(YellowLED) ;
        else if (heartrate >= 40 && heartrate <100) 
           OnOnlyThisLED(GreenLED) ;
        else 
           OnOnlyThisLED(RedLED) ;
      }
      //delay(150);
  }

  
  }
