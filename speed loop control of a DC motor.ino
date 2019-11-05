void setup() {
 // Intilialise the pin and attach interrrupts
 pinMode(sensor,INPUT);
 attachInterrupt(digitalPinToInterrupt(sensor), rpm, RISING);
 min_value = max_RPM/n; // calculate the minimum error for the motor (n is the number of PWM values)
 }
void loop() {
    // calculate RPM of the Motor
     analogWrite(10, PWM);
     current = micros();
      total_time = current - previous;
      previous = current;
        RPM=60000000/total_time;
        // check whether the RPM is within the minimum error rate and the calculate the desired PWM with the help of the trasnfer function
        if(abs(RPM-given_RPM)<= min_value)
          {
          PWM=((given_RPM)*(current_PWM)/(current_RPM));
          }
        // the desired PWM is achieved by calculating the PWM recursively using the loop function (seperate loop is not required)

    // Get the input from the user using which calculate the initial PWM
    if(Serial.available()>0)
       {
         int y=Serial.parseInt();
        PWM=((given_RPM)*(current_PWM)/(current_RPM));
        }  
}
