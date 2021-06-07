
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


#define Relay1 15
#define Relay2 2
#define Relay3 4
#define Relay4 1

boolean connectWifi();


void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);



// WiFi Credentials
const char* ssid = "SmS_jiofi";
const char* password = "sms123458956";

// device names
String relay_1 = "relay1";
String relay_2 = "relay2";
String relay_3 = "relay3";
String relay_4 = "relay4";

boolean wifiConnected = false;
Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(relay_1, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(relay_2, secondLightChanged);
    espalexa.addDevice(relay_3, thirdLightChanged);
    espalexa.addDevice(relay_4, fourthLightChanged);

    espalexa.begin();

  }

  else
  {
    while (1)
    {
      Serial.println("Cannot connect to at the movement pls check the wifi WiFi");
      delay(2500);
    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(Relay1, HIGH);
      Serial.println("relay one on");
    }
  }
  else
  {
    digitalWrite(Relay1, LOW);
    Serial.println("relay one off");
  }
}

void secondLightChanged(uint8_t brightness)
{
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(Relay2, HIGH);
      Serial.println("relay two onn");
    }
  }
  else
  {
    digitalWrite(Relay2, LOW);
    Serial.println("relay two off");
  }
}

void thirdLightChanged(uint8_t brightness)
{
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(Relay3, HIGH);
      Serial.println("relay three onn");
    }
  }
  else
  {
    digitalWrite(Relay3, LOW);
    Serial.println("relay three off");
  }
}

void fourthLightChanged(uint8_t brightness)
{
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(Relay4, HIGH);
      Serial.println("relay four onn");
    }
  }
  else
  {
    digitalWrite(Relay4, LOW);
    Serial.println("relay four off");
  }
}
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("connection failed.");
  }
  return state;
}
