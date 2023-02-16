#ifndef LedDriver_hpp
#define LedDriver_hpp

#include <Adafruit_NeoPixel.h>

#include <ColorState.hpp>

class LedDriver {
 public:
  LedDriver(int numPixels, int pin);

  void setColor(ColorState color);

  void begin();

 private:
  int _numPixels;
  int _pin;
  ColorState _color;

  Adafruit_NeoPixel _pixels;
  
  void update();
};

#endif  // LedDriver_hpp
