#include <ColorState.hpp>

#include <stdio.h>

namespace {

uint8_t scaleAlphaToInt(float a) {
  return (uint8_t)(a * 0xFF);
}

float scaleAlphaToFloat(uint8_t a) {
  return ((float)a) / 0xFF;
}

}

ColorState::ColorState(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
  : _r(r), _g(g), _b(b), _a(scaleAlphaToInt(a)) {}

void ColorState::read(ColorState& colorState, JsonObject& root) {
  root["r"] = colorState._r;
  root["b"] = colorState._b;
  root["g"] = colorState._g;
  root["a"] = scaleAlphaToFloat(colorState._a);
}

StateUpdateResult ColorState::update(JsonObject& root, ColorState& colorState) {
  StateUpdateResult updated = 
    (root["r"] == colorState._r &&
    root["g"] == colorState._g &&
    root["b"] == colorState._b &&
    scaleAlphaToInt(root["a"]) == colorState._a) ?
      StateUpdateResult::UNCHANGED : StateUpdateResult::CHANGED;
  if (updated == StateUpdateResult::CHANGED) {
    colorState._r = root["r"] | 0;
    colorState._g = root["g"] | 0;
    colorState._b = root["b"] | 0;
    colorState._a = scaleAlphaToInt(root["a"] | 1.0);
  }
  return updated;
}

ColorState::operator String() const {
  static char buf[100];
  sprintf(buf, "#%02X%02X%02X%02X", _r, _g, _b, _a);
  return String(buf);
}
