// 
// Made for ESP32 MCU using the Arduino framework
// https://wiki.dfrobot.com/Gravity_Analog_AC_Current_Sensor__SKU_SEN0211_
// 
// To use on arduino change:
// - ADC pin
// - ADC resolution (10bit for uno)
// - VREF
// 

#include <Arduino.h>

#define ADC_PIN 12
#define ADC_RESOLUTION_BITS 12
#define MAX_AMPERAGE 20
#define VREF 3.3
#define RMS_VOLTAGE 220

float val;
int power;
char buf[50];

float calculate_amp()
{
  float current_val = 0;
  float peak_voltage = 0;  
  float rms_value = 0;  //Vrms
  for (int i = 0; i < 50; i++)
  {
    peak_voltage += analogRead(ADC_PIN);   //read peak voltage
    // delay(1);
  }
  peak_voltage = peak_voltage / 50;   
  rms_value = peak_voltage * 0.707;    //change the peak voltage to the Virtual Value of voltage

  /*The circuit is amplified by 2 times, so it is divided by 2.*/
  rms_value = (rms_value / pow(2, ADC_RESOLUTION_BITS) * VREF ) / 2;  

  current_val = rms_value * MAX_AMPERAGE;

  return current_val;
}

void setup()
{
  Serial.begin(115200);
  // adcAttachPin(ADC_PIN);
  Serial.println("Initializing AC current sensor");
  delay(100);
}

void loop()
{
  val = calculate_amp();
  power = RMS_VOLTAGE*val;
  sprintf(buf, "%.2f A  /  %d VA @ %d V RMS", val, power, RMS_VOLTAGE);
  Serial.println(buf);

  // Serial.println(analogRead(ADC_PIN));

  delay(500);
}

