#define BLYNK_PRINT Serial

// -------- Blynk IoT Credentials --------
#define BLYNK_TEMPLATE_ID "TMPL650uDP0-t"
#define BLYNK_TEMPLATE_NAME "DHT11Monitor"
#define BLYNK_AUTH_TOKEN    "JIyNFkS1qOtS0Chq0EeMLqVX4JmPSKey"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// -------- WiFi Credentials --------
char ssid[] = "Advanced Air Service2.4G";
char pass[] = "0924422409";

// -------- Pin Definitions --------
#define RELAY_PIN D1
#define DHT_PIN   D2
#define DHT_TYPE  DHT11

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

// -------- Control Variables --------
bool autoMode = false;
float setTemp = 30.0;
bool manualRelayState = false;

// -------- AUTO / MANUAL MODE SWITCH --------
BLYNK_WRITE(V1) {
  autoMode = param.asInt();

  Serial.print("Mode: ");
  Serial.println(autoMode ? "AUTO" : "MANUAL");
}

// -------- MANUAL RELAY CONTROL --------
BLYNK_WRITE(V0) {
  if (autoMode) return;   // Ignore when in AUTO

  manualRelayState = param.asInt();
  digitalWrite(RELAY_PIN, manualRelayState ? LOW : HIGH);
}

// -------- TEMPERATURE SETPOINT --------
BLYNK_WRITE(V10) {
  setTemp = param.asStr().toFloat();

  Serial.print("Set temperature: ");
  Serial.println(setTemp);
}

// -------- Read DHT11 --------
void readDHT() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);

  // -------- AUTO MODE LOGIC --------
  if (autoMode) {
    if (temperature >= setTemp) {
      digitalWrite(RELAY_PIN, LOW);   // Relay ON
    } else {
      digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, readDHT);
}

void loop() {
  Blynk.run();
  timer.run();
}
