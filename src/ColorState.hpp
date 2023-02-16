#ifndef ColorState_h
#define ColorState_h

#include <stdint.h>

#include <ArduinoJson.h>
#include <StatefulService.h>

class ColorState {
 public:
  uint8_t _r;
  uint8_t _g;
  uint8_t _b;
  uint8_t _a;

  ColorState(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0xff);

  static void read(ColorState& state, JsonObject& root);

  static StateUpdateResult update(JsonObject& root, ColorState& colorState);

  operator String() const;
};

#endif  // ColorState_h
