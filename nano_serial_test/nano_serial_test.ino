//TEST SERIAL
union {
  struct {
    float data1;
    float data2;
    float data3;
    float data4;
  } param;
  byte packet[16]; //4 x 4Byte
} data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  data.param.data1 = temperature
  // put your main code here, to run repeatedly:
  Serial.write("test");
}
