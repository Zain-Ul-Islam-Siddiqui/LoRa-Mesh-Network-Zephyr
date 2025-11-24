#include "GatewayFirebase.hpp"
#include "ExampleFunctions.h"

SSL_CLIENT _sslClient;

unsigned long getEpoch() {
  time_t now;
  time(&now);
  return now;
}

FirebaseUploader::FirebaseUploader(const char* ssid,
                                   const char* password,
                                   const char* apiKey,
                                   const char* userEmail,
                                   const char* userPassword,
                                   const char* projectId)
    : _ssid(ssid),
      _password(password),
      _apiKey(apiKey),
      _userEmail(userEmail),
      _userPassword(userPassword),
      _projectId(projectId),
      _aClient(_sslClient),
      _userAuth(apiKey, userEmail, userPassword, 3000) {}

void FirebaseUploader::connectWiFi() {
    WiFi.begin(_ssid, _password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println(" Connected!");
}

void FirebaseUploader::syncTime() {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("Syncing time");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.print(".");
        delay(500);
    }
    Serial.println(" Time synced!");
}

String FirebaseUploader::getISO8601Time() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "1970-01-01T00:00:00Z";
    }
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(buf);
}

void FirebaseUploader::begin() {
    connectWiFi();
    syncTime();

    set_ssl_client_insecure_and_buffer(_sslClient);

    Serial.println("Initializing Firebase app...");
    initializeApp(_aClient, _app, getAuth(_userAuth), auth_debug_print, "authTask");

    _app.getApp<Firestore::Documents>(_docs);
    Serial.println("Firebase initialized.");
}

void FirebaseUploader::loop() {
    _app.loop(); // must be called in main loop
}

bool FirebaseUploader::ready() {
    return _app.ready(); // must be called in main loop
}

void FirebaseUploader::pushPayload(uint8_t nodeId, const String& payload) {
    if (!_app.ready()) {
        Serial.println("Firebase not ready yet");
        return;
    }

    unsigned long epoch = getEpoch();
    String parentPath = String("nodes/node_") + nodeId + "/history";
    String documentPath = parentPath + "/data_" + String(epoch); // unique doc

    // Prepare Firestore document
    Values::StringValue payloadValue(payload);
    Values::TimestampValue tsValue(getISO8601Time());

    Document<Values::Value> doc("payload", Values::Value(payloadValue));
    doc.add("timestamp", Values::Value(tsValue));

    Serial.printf("Pushing payload for node %u...\n", nodeId);
    _docs.createDocument(_aClient,
                         Firestore::Parent(_projectId),
                         documentPath,
                         DocumentMask(),
                         doc,
                         [](AsyncResult &result) {
                             if (result.isError()) {
                                 Serial.printf("Firestore Error: %s (code %d)\n",
                                               result.error().message().c_str(),
                                               result.error().code());
                             } else if (result.available()) {
                                 Serial.printf("Firestore Success: %s\n",
                                               result.c_str());
                             }
                         },
                         "pushPayloadTask");
}
