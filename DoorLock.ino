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

