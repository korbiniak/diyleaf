#include <APSettingsService.h>

APSettingsService::APSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) :
    _httpEndpoint(APSettings::serialize,
                  APSettings::deserialize,
                  this,
                  server,
                  AP_SETTINGS_SERVICE_PATH,
                  securityManager),
    _fsPersistence(APSettings::serialize, APSettings::deserialize, this, fs, AP_SETTINGS_FILE) {
  addUpdateHandler([&](String originId) { reconfigureAP(); }, false);
}

void APSettingsService::begin() {
  _fsPersistence.readFromFS();
  reconfigureAP();
}

void APSettingsService::reconfigureAP() {
  _lastManaged = millis() - MANAGE_NETWORK_DELAY;
}

void APSettingsService::loop() {
  unsigned long currentMillis = millis();
  unsigned long manageElapsed = (unsigned long)(currentMillis - _lastManaged);
  if (manageElapsed >= MANAGE_NETWORK_DELAY) {
    _lastManaged = currentMillis;
    manageAP();
  }
  handleDNS();
}

void APSettingsService::manageAP() {
  WiFiMode_t currentWiFiMode = WiFi.getMode();
  if (_state.provisionMode == AP_MODE_ALWAYS ||
      (_state.provisionMode == AP_MODE_DISCONNECTED && WiFi.status() != WL_CONNECTED)) {
    if (currentWiFiMode == WIFI_OFF || currentWiFiMode == WIFI_STA) {
      startAP();
    }
  } else {
    if (currentWiFiMode == WIFI_AP || currentWiFiMode == WIFI_AP_STA) {
      stopAP();
    }
  }
}

void APSettingsService::startAP() {
  Serial.println("Starting software access point");
  WiFi.softAP(_state.ssid.c_str(), _state.password.c_str());
  if (!_dnsServer) {
    IPAddress apIp = WiFi.softAPIP();
    Serial.print("Starting captive portal on ");
    Serial.println(apIp);
    _dnsServer = new DNSServer;
    _dnsServer->start(DNS_PORT, "*", apIp);
  }
}

void APSettingsService::stopAP() {
  if (_dnsServer) {
    Serial.println("Stopping captive portal");
    _dnsServer->stop();
    delete _dnsServer;
    _dnsServer = nullptr;
  }
  Serial.println("Stopping software access point");
  WiFi.softAPdisconnect(true);
}

void APSettingsService::handleDNS() {
  if (_dnsServer) {
    _dnsServer->processNextRequest();
  }
}