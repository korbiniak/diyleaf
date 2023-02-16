#ifndef DiyleafStateService_h 
#define DiyleafStateService_h

#include <WebSocketTxRx.h>

#include <StatefulService.h>
#include <ColorState.hpp>
#include <LedDriver.hpp>

// Note that the built-in LED is on when the pin is low on most NodeMCU boards.
// This is because the anode is tied to VCC and the cathode to the GPIO 4 (Arduino pin 2).

#define DIYLEAF_SETTINGS_SOCKET_PATH "/ws/diyleafState"
#define DEFAULT_COLOR_STATE ColorState()

class DiyleafState {
 public:
  ColorState _color;

  static void read(DiyleafState& diyleafState, JsonObject& root) {
    JsonObject color = root["color"];
    ColorState::read(diyleafState._color, color);
  }

  static StateUpdateResult update(JsonObject& root, DiyleafState& diyleafState) {
    serializeJson(root, Serial);
    JsonObject color = root["color"];
    return ColorState::update(color, diyleafState._color);
  }
};

class DiyleafStateService : public StatefulService<DiyleafState> {
 public:
  DiyleafStateService(AsyncWebServer* server,
                      SecurityManager* securityManager,
                      LedDriver* ledDriver);
  void begin();

 private:
  WebSocketTxRx<DiyleafState> _webSocket;
  LedDriver *_ledDriver;

  void onConfigUpdated();
};

#endif  // DiyleafStateService_h
