# 🌡️ ESP8266 (NodeMCU) DHT11 + Relay Control with Blynk IoT

This project uses a **NodeMCU ESP8266** to:

* Read **temperature & humidity from a DHT11 sensor**
* Control a **relay module**
* Switch between **MANUAL** and **AUTO (temperature-based)** modes using **Blynk IoT**
* Set temperature threshold via **Blynk Text Input**

---

## ✨ Features

* 📡 WiFi control using **Blynk IoT**
* 🌡️ Real-time **temperature & humidity monitoring**
* 🔘 **Manual relay control** from the app
* 🤖 **Automatic relay control** based on temperature setpoint
* 🔁 Toggle between **AUTO / MANUAL** modes
* ⚡ Compatible with **NodeMCU v3 (ESP8266)**

---

## 🧰 Hardware Requirements

* NodeMCU ESP8266 (v3)
* DHT11 temperature & humidity sensor
* Relay module (active LOW recommended)
* Jumper wires
* WiFi connection

---

## 🔌 Pin Connections

| Component  | NodeMCU Pin | GPIO  |
| ---------- | ----------- | ----- |
| Relay IN   | D1          | GPIO5 |
| DHT11 DATA | D2          | GPIO4 |
| DHT11 VCC  | 3.3V        |       |
| DHT11 GND  | GND         |       |

---

## 📱 Blynk IoT Dashboard Setup

### Widgets Configuration

| Widget          | Virtual Pin | Description               |
| --------------- | ----------- | ------------------------- |
| Button (Switch) | V1          | AUTO / MANUAL mode toggle |
| Button (Switch) | V0          | Manual relay ON/OFF       |
| Text Input      | V10         | Temperature setpoint (°C) |
| Display / Gauge | V5          | Temperature               |
| Display / Gauge | V6          | Humidity                  |

### Widget Notes

* **V1 (Mode Switch)**

  * OFF → MANUAL
  * ON → AUTO
* **Text Input (V10)**

  * Enter numeric value (example: `30`)
* Relay is **active LOW**

---

## ⚙️ Software Requirements

* Arduino IDE
* ESP8266 Board Package
* Libraries:

  * `Blynk`
  * `DHT sensor library`
  * `Adafruit Unified Sensor`

Install libraries via **Arduino Library Manager**.

---

## 🚀 How It Works

### MANUAL Mode

* Relay is controlled directly using the **Blynk button (V0)**

### AUTO Mode

* ESP8266 compares **current temperature** with **setpoint**
* Relay behavior:

  * `Temperature ≥ Setpoint` → Relay **ON**
  * `Temperature < Setpoint` → Relay **OFF**
* Manual button is ignored in AUTO mode

---

## 🧪 Example Logic

| Mode   | Temp | Setpoint | Relay             |
| ------ | ---- | -------- | ----------------- |
| MANUAL | —    | —        | Button controlled |
| AUTO   | 29°C | 30°C     | OFF               |
| AUTO   | 31°C | 30°C     | ON                |

---

## 📄 Configuration (Important)

Before uploading the code, update:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "DHT11Monitor"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

---

## ⚠️ Notes & Tips

* DHT11 should have a **pull-up resistor** (usually built-in)
* Do **not power a 5V relay from 3.3V** directly
* Use a relay module with optocoupler if possible
* For real applications, consider adding **hysteresis** to protect relay

---

## 🛠️ Possible Improvements

* Add temperature hysteresis (anti relay chatter)
* Replace Text Input with Slider
* Save mode & setpoint to EEPROM
* Add alert notifications in Blynk
* Support DHT22 sensor

---

