#pragma once 

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#define ENABLE_USER_AUTH
#define ENABLE_FIRESTORE

#include <FirebaseClient.h>

class FirebaseUploader {
public:
    FirebaseUploader(const char* ssid,
                     const char* password,
                     const char* apiKey,
                     const char* userEmail,
                     const char* userPassword,
                     const char* projectId);

    void begin();
    void loop(); // must be called in main loop()
    void pushPayload(uint8_t nodeId, const String& payload);
    bool ready();

private:
    const char* _ssid;
    const char* _password;
    const char* _apiKey;
    const char* _userEmail;
    const char* _userPassword;
    const char* _projectId;

    using AsyncClient = AsyncClientClass;
    AsyncClient _aClient;
    UserAuth _userAuth;
    FirebaseApp _app;
    Firestore::Documents _docs;

    unsigned long _lastPush = 0;

    void connectWiFi();
    void syncTime();
    String getISO8601Time();
};
