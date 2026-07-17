#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "UbidotsEsp32Mqtt.h"
#define SENSOR A0
#define REPORTING_PERIOD_MS 1000
const char *UBIDOTS_TOKEN ="BBUS-rsXMWZn0no4jgVn9AR2p2fuZMRRYI9";
const char *WIFI_SSID="POCO F5";
const char *WIFI_PASS="1234567890";
const char *DEVICE_LABEL="ESP32";
const char *VARIABLE_LABEL1="Pulse Rate";
const char *VARIABLE_LABEL2="SpO2";
const char *VARIABLE_LABEL3="ECG";
unsigned long timer;
Ubidots ubidots (UBIDOTS_TOKEN);
PulseOximeter pox;
uint32_t tsLastReport=0;
void onBeatDetected(){
  ;
}
void callback(char *topic,byte *payload,unsigned int length)
{
  Serial.print("Message arrived[");
  Serial.print(topic);
  Serial.print("]");
  for(int i=0;i<length;i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  ubidots.connectToWifi(WIFI_SSID,WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  Serial.print("Intializing pulse oximeter..");
  if(!pox.begin()){
    Serial.println("FAILED");
    for(;;)
    {
      ;
    }
  }else{
    Serial.println("SUCESS");
    digitalWrite(1,HIGH);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}
void loop()
  {
  if(!ubidots.connected()){
    ubidots.reconnect();
  }
  pox.update();
  if(millis()-tsLastReport>REPORTING_PERIOD_MS){
    ubidots.add(VARIABLE_LABEL1,pox.getHeartRate());
    ubidots.publish(DEVICE_LABEL);
    ubidots.add(VARIABLE_LABEL2,pox.getSpO2());
    ubidots.publish(DEVICE_LABEL);
    int sensor = analogRead(SENSOR);
    ubidots.add(VARIABLE_LABEL3,sensor);
    ubidots.publish(DEVICE_LABEL);
    lcd.setCursor(0,0);
    lcd.print("ECG");
    lcd.print(sensor);
    lcd.setCursor(0,1);
    lcd.print("BPM");
    lcd.print(pox.getHeartRate());
    lcd.setCursor(10,0);
    lcd.print("SpO2:");
    lcd.setCursor(12,1);
    lcd.print(pox.getSpO2());
    lcd.setCursor(14,1);
    lcd.print("%");
    ubidots.loop();
    tsLastReport=millis();
  }
}


