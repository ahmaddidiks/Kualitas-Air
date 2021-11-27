//SERIAL 2
#define RXD2 16
#define TXD2 17

union {
  struct {
    float temperature;
    float oksigen;
    float ph;
    float turbidity;
  } param;
  byte packet[16]; //4 x 4Byte
} dataRecv;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available()) {
    Serial2.readBytes(dataRecv.packet, sizeof(dataRecv.packet));
  }
  
  Serial.print("temp: "); Serial.println(dataRecv.param.temperature);
}
