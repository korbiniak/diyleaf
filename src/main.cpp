#include <ESP8266React.h>
#include <LightMqttSettingsService.hpp>
#include <LightStateService.hpp>
#include <DiyleafStateService.hpp>
#include <LedDriver.hpp>
#include <Esp.h>

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager(),
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService);
LedDriver ledDriver(FACTORY_PIXEL_COUNT, FACTORY_PIXEL_PIN);
DiyleafStateService diyleafStateService(&server, esp8266React.getSecurityManager(), &ledDriver);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  Serial.begin(SERIAL_BAUD_RATE);
  esp8266React.begin();
  lightStateService.begin();
  lightMqttSettingsService.begin();
  diyleafStateService.begin();
  ledDriver.begin();
  ESP.wdtEnable(1000);
  server.begin();
}


void loop() {
  esp8266React.loop();
  // ledDriver.setColor(ColorState(123,123,123));
  ESP.wdtFeed();
  delay(50);
}

