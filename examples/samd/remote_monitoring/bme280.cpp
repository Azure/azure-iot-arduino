// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "bme280.h"

const int Bme280_cs_pin__i = 5;
bool Bme_init_result = false;
Adafruit_BME280 bme(Bme280_cs_pin__i);


///////////////////////////////////////////////////////////////////////////////////////////////////
void initBme(void)
{
  Serial.println("Checking for the presence of the BME280 temp/humid/press module.");
  Bme_init_result = bme.begin();
  if (Bme_init_result)
  {
    Serial.println("Found and initialized BME280 module.");
  }
  else
  {
    Serial.println("Warning! BME280 module not found.");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void getNextSample(float* Temperature, float* Humidity)
{
  *Temperature = bme.readTemperature(); // Deg C
  //float Pres_hPa__f = bme.readPressure() / 100;
  *Humidity = bme.readHumidity();
  //printf("Temp=%.2f, Pres=%.2f, Humi=%.2f\n", Temp_c__f, Pres_hPa__f, Humi_pct__f);
  printf("Temp=%.2f, Humi=%.2f\n", *Temperature, *Humidity);
}

