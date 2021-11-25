/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLINJOfhJD"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "65XQjPn6QwhQGd6ZnVYWQn8PwhQyCEV-"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//SERIAL 2
#define RXD2 16
#define TXD2 17

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wisma RG";
char pass[] = "Toptenan";

union {
  struct {
    float temperature;
    float oksigen;
    float ph;
    float turbidity;
  } param;
  byte packet[16]; //4 x 4Byte
} dataRecv;

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  Serial.println(value);
  digitalWrite(2, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.

//  dumy value just for testing
//  dataRecv.param.temperature++;
//  if (dataRecv.param.temperature> 35) dataRecv.param.temperature = 10;
  
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V4, dataRecv.param.temperature); Serial.print("temp: "); Serial.println(dataRecv.param.temperature);
  Blynk.virtualWrite(V5, dataRecv.param.oksigen);     Serial.print("oksigen: "); Serial.println(dataRecv.param.oksigen);
  Blynk.virtualWrite(V6, dataRecv.param.ph);          Serial.print("ph: "); Serial.println(dataRecv.param.ph);
  Blynk.virtualWrite(V7, dataRecv.param.turbidity);   Serial.print("turbidity: "); Serial.println(dataRecv.param.turbidity); Serial.println("");
}

void setup()
{
  // Debug console
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();

  //get data from sensor
  if (Serial2.available()) {
    Serial2.readBytes(dataRecv.packet, sizeof(dataRecv.packet));
  }
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
