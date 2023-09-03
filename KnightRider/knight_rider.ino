      
      int t = 20;
      void setup() {
        for(int pin=2; pin<14; pin++){
          pinMode(pin,OUTPUT);
        }
      }

      void loop() {
      //forward-motion (starts from pin 2 led to pin 13 led)
        for(int i=2; i<14; i++){
          digitalWrite(i,HIGH);
          delay(t);
          digitalWrite(i+1,HIGH);
          delay(t);
          digitalWrite(i+2,HIGH);
          delay(t);
          digitalWrite(i,LOW);
          delay(t);
          digitalWrite(i+1,LOW);
        }
        
      //backward-motion (starts from pin 13 led to pin 2 led)
        for(int i=13; i>1; i--){
          digitalWrite(i,HIGH);
          delay(t);
          digitalWrite(i-1,HIGH);
          delay(t);
          digitalWrite(i-2,HIGH);
          delay(t);
          digitalWrite(i,LOW);S
          delay(t);
          digitalWrite(i-1,LOW);
        }
      }
