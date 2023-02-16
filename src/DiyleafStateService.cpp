#include <DiyleafStateService.hpp>


DiyleafStateService::DiyleafStateService(AsyncWebServer* server,
                                        SecurityManager* securityManager,
                                        LedDriver* ledDriver):
          _webSocket(DiyleafState::read,
                     DiyleafState::update,
                     this,
                     server,
                     DIYLEAF_SETTINGS_SOCKET_PATH,
                     securityManager,
                     AuthenticationPredicates::IS_AUTHENTICATED),
          _ledDriver(ledDriver) {
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void DiyleafStateService::begin() {
  _state._color = DEFAULT_COLOR_STATE;
  onConfigUpdated();
}

void DiyleafStateService::onConfigUpdated() {
  Serial.println(String(_state._color));
  _ledDriver->setColor(_state._color);
}

