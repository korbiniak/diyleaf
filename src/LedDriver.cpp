#include <LedDriver.hpp>

#include <Adafruit_NeoPixel.h>

LedDriver::LedDriver(int numPixels, int pin)
    : _numPixels(numPixels), _pin(pin), _pixels(numPixels, pin, NEO_GRB + NEO_KHZ800) {
}

void LedDriver::begin() {
  _pixels.begin();
  _pixels.setBrightness(50);
  setColor(ColorState(123, 123, 123));
}

void LedDriver::setColor(ColorState color) {
  _color = color;
  update();
}

void LedDriver::update() {
  Serial.println("Updating leds...");
  for(int i = 0; i < _numPixels; i++) {
    _pixels.setPixelColor(i, _pixels.Color(_color._r, _color._g, _color._b));
  }
  _pixels.show();
  Serial.println("Updated!");
}
