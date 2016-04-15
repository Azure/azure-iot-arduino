///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Attunix, 2016. All rights reserved.
//
// This example code shows how to use an Adafruit Feather M0 module and Microsoft Azure for IoT
// applications.

// change the next three lines to use on non-Adafruit WINC1500 based boards/shields
#include <Adafruit_WINC1500.h>
#include <Adafruit_WINC1500SSLClient.h>
#include <Adafruit_WINC1500Udp.h>

// for WiFi101
//#include <WiFi101.h>
//#include <WiFiSSLClient.h>
//#include <WiFiUdp.h>

// for ESP8266
//#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
//#include <WiFiUdp.h>

#include <Adafruit_BME280.h>
#include <NTPClient.h>
#include <AzureIoTHub.h>

#include "rem_ctrl_http.h"

// for the Adafruit WINC1500 we need to create our own WiFi instance
// Define the WINC1500 board connections below.
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2     // or, tie EN to VCC
// Setup the WINC1500 connection with the pins above and the default hardware SPI.
Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);

static const char ssid[] = "[Your WiFi network SSID or name]";
static const char pass[] = "[Your WiFi network WPA password or WEP key]";

// The connection string is the one which begins with HostName=... and contains the DeviceId
// and SharedAccessKey for this particular Thing on the Internet.
static const char* connectionString = "[Device Connection String]";

// change the next line to use on non-Adafruit WINC1500 based boards/shields
Adafruit_WINC1500SSLClient sslClient; // for Adafruit WINC150
//WiFiSSLClient sslClient; // for WiFi101
//WiFiClientSecure sslClient; // for ESP8266

AzureIoTHubClient iotHubClient(sslClient);

#define SEALEVELPRESSURE_HPA (1013.25)
const int Bme280_cs_pin__i = 5;
bool Bme_init_result = false;
Adafruit_BME280 bme(Bme280_cs_pin__i);

void setup() {
  initSerial();

  Serial.println("Azure_remote_monitoring Sketch.");

  initWifi();
  initTime();
  initBME();

  if (rem_ctrl_set_connection_string(connectionString)) {
    Serial.print("Connection string successfully set to \"");
    Serial.print(connectionString);
    Serial.println("\"");
  }
  else {
    Serial.println("Unable to set connection string. (too long?)");
  }

  int Init_result__i = rem_ctrl_http_init();
  if (Init_result__i < 4)
  {
    Serial.println("Unable to initialize the Azure connection. Halting.");
  }

  iotHubClient.begin();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// The Arduino millisecond clock is used here to get a simplistic multitasking effect.
// This macro handles wrap-around correctly.
#define IS_TASK_TIME(curr_time_ms, next_task_time_ms) \
  ((curr_time_ms >= next_task_time_ms) && ( ! ((curr_time_ms ^ next_task_time_ms) & 0x80000000L)))
uint32_t const Sensor_read_period_ms__u32 = 15000;
uint32_t Sensor_read_next_ms__u32 = 0;
uint32_t const Azure_io_update_period_ms__u32 = 100;
uint32_t Azure_io_update_next_ms__u32 = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  uint32_t Curr_time_ms__u32 = millis();

  if (IS_TASK_TIME(Curr_time_ms__u32, Sensor_read_next_ms__u32)) {
    float Temp_c__f = bme.readTemperature();
    float Pres_hPa__f = bme.readPressure() / 100;
    float Humi_pct__f = bme.readHumidity();
    printf("Temp=%.2f, Pres=%.2f, Humi=%.2f\n", Temp_c__f, Pres_hPa__f, Humi_pct__f);
    rem_ctrl_http_send_data(Temp_c__f, Pres_hPa__f, Humi_pct__f);

    Sensor_read_next_ms__u32 = Curr_time_ms__u32 + Sensor_read_period_ms__u32;
  }

  if (IS_TASK_TIME(Curr_time_ms__u32, Azure_io_update_next_ms__u32)) {
    rem_ctrl_http_run();

    Azure_io_update_next_ms__u32 = Curr_time_ms__u32 + Azure_io_update_period_ms__u32;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initSerial() {
  //Initialize serial and wait for port to open:
  // For SAMD boards (e.g. MKR1000, Adafruit WINC1500 based)
  Serial.begin(9600);
  
  // Uncomment the next two lines For ESP8266 boards (and comment out the line above)
  // Serial.begin(115200);
  // Serial.setDebugOutput(true);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void initWifi() {
  // for the Adafruit WINC1500 we need to enable the chip
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);

  // check for the presence of the shield :
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // unsuccessful, retry in 4 seconds
    Serial.print("failed ... ");
    delay(4000);
    Serial.print("retrying ... ");
  }

  Serial.println("Connected to wifi");
}

void initTime() {
  // change the next line to use on non-WINC1500 based boards/shields
  Adafruit_WINC1500UDP ntpUdp; // for Adafruit WINC1500
  // WiFiUDP ntpUdp; // for WiFi101 
  // for ESP8266 boards see comment below
  NTPClient ntpClient(ntpUdp);

  ntpClient.begin();

  while (!ntpClient.update()) {
    Serial.println("Fetching NTP epoch time failed! Waiting 5 seconds to retry.");
    delay(5000);
  }

  ntpClient.end();

  unsigned long epochTime = ntpClient.getEpochTime();

  Serial.print("Fetched NTP epoch time is: ");
  Serial.println(epochTime);

  iotHubClient.setEpochTime(epochTime);
  
  // For ESP8266 boards comment out the above portion of the function and un-comment
  // the remainder below.
  
  // time_t epochTime;

  // configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  // while (true) {
  //     epochTime = time(NULL);

  //     if (epochTime == 0) {
  //         Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
  //         delay(2000);
  //     } else {
  //         Serial.print("Fetched NTP epoch time is: ");
  //         Serial.println(epochTime);
  //         break;
  //     }
  // }
}

void initBME() {
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

