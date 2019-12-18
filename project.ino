int n=255; // max PWM
int min_value=0;
unsigned long int previous1=0;
unsigned long int current1=0;
unsigned long int max_RPM=0;
unsigned int l;
int interrupt=0;
int cnt;
float current_RPM;
float current_PWM;
unsigned int PWM=0;
int y=0;
int sensor=3;
int given_RPM=0;
int NoR=0;
unsigned long int total_time;
unsigned long int previous=0;
unsigned long int current=0;
unsigned long int w=0;
unsigned long int RPM=0;
void setup() {
  Serial.begin(9600);
  //initialise the pin and attatch interupt
  pinMode(sensor,INPUT);
  attachInterrupt(digitalPinToInterrupt(sensor), increment_interupt, RISING);
  // calculate the max RPM 
    analogWrite(10,255);
    delay(1000);
    while(digitalRead(3)==LOW);
    previous1=millis();
    while(digitalRead(3)==HIGH);
    while(digitalRead(3)==LOW);
    current1=millis();
    max_RPM=60000/(current1-previous1);
    min_value=max_RPM/n;  // calculating the error limit
 analogWrite(10,0);
  // put your setup code here, to run once:
 }
// intertupt function
void increment_interupt()
{
  interrupt=1;
 }
void loop() {
  // get the input from the user
      if(Serial.available()>0)
       {
        count=0;
        NoR=0; // Number of Rotations  
         int y=Serial.parseInt();
          if(y>0)
         { 
           given_RPM=y;
           current_RPM=max_RPM;
           current_PWM=255;
           i=0;
              w=millis();
          }
        PWM=((given_RPM)*(current_PWM)/(current_RPM));
        }  
    analogWrite(10,PWM); // make the motor rotate at the PWM
    // RPM Claculation
    if(interrupt==1) 
    {
      NoR++; 
     current = micros();
      total_time = current - previous;
      previous = current;
        RPM=60000000/total_time; 
         interrupt=0;
    }     
    if(NoR>1) // feedback system does not consider the first rotation
      {
        if(RPM-given_RPM<=min_value || given_RPM-RPM<=min_value)   // checking whether the motor is within it's limit
        {
          // the PWM is not changed
          cnt = 0; // cnt is declared to remove spikes
          Serial.print(RPM);
         }
         else
         {
           NoR=0;
           cnt++;
           if(cnt==2) // if the motor's RPM excedds the limit more than twice continuously, then the PWM is changed (to remove spikes)
           {
              current_RPM=RPM;
              current_PWM=PWM;
              PWM=((given_RPM)*(current_PWM)/(current_RPM)); // calculate the new desired PWM
              Serial.print(RPM);
           }
         }
       }
}
