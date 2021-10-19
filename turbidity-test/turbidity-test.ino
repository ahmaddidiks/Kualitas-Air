void setup() {
  Serial.begin(9600); //Baud rate: 9600
}

float turbidity(float input){
  /*
   * 0 = 3,81
   * 4000 = 0  
   * perbandingan 3,81:4000
   * turb = abs((3,81-input)*4000)
   */
   float turb = abs((3.81-input)*4000); 
   
   return turb;
}

void loop() {
  int sensorValue = analogRead(A1);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
  Serial.println(turbidity(voltage)); // print out the value you read:
  delay(500);
}
