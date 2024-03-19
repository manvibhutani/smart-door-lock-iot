#include <ESP32Servo.h>
#include <LiquidCrystal.h>

// From .env file
#define BLYNK_TEMPLATE_ID " "
#define BLYNK_TEMPLATE_NAME " "
#define BLYNK_AUTH_TOKEN " "

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
int servo_pin = 4;
int buz_pin = 26;
Servo s;

void unlockDoor()
{
    s.write(180);
    delay(500);
}

void lockDoor()
{
    s.write(0);
    delay(500);
}

void soundBuzzer()
{
    tone(buz_pin, 1000);
    delay(1000);
}

void reset()
{
    lockDoor();
    lcd.clear();
    noTone(buz_pin);
}

void sendMessage()
{
    Blynk.logEvent("notification", "Theft Alert!");
}
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); 
  // 0-> Default
  // 1-> Door Open
  // 2-> Door Closed
  if (pinValue == 2)
  {
    lockDoor();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Burglar Detected");
    sendMessage();
    soundBuzzer();
  }
  else if(pinValue==1) 
  {
    reset();
    lcd.clear();
    unlockDoor();
    noTone(buz_pin);
    lcd.setCursor(0,1);
    lcd.print("Welcome");
  }
  else if(pinValue==0)
  {
    reset();
  }
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  s.attach(servo_pin); 
  pinMode(buz_pin,OUTPUT);
  lcd.begin(16,2);
  reset();
}

void loop()
{
  Blynk.run();
}























