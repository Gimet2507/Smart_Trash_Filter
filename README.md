# 🗑️ Smart Trash Filter: Organic and Inorganic

A complete **IoT-based smart trash bin** using **ESP8266 (NodeMCU)** that automatically detects, classifies, and sorts trash as **organic** or **non-organic** using sensors, a **servo motor**, and **relay modules**. The system also sends **real-time notifications via Telegram** when trash bins are full, making waste management more efficient and smarter.

## 🧠 Features
- Detects presence of trash using **IR obstacle sensors**.
- Classifies trash:
  - **Organic** (non-metal) via **capacitive proximity sensor**.
  - **Non-organic** (metal) via **inductive proximity sensor**.
- Directs trash into the correct bin using a **servo motor**.
- Controls **relays** to simulate actuator or lid mechanisms.
- Sends **real-time notifications** to **Telegram** when either bin is full.
- Integrates with **Blynk** to monitor classification status remotely.

## 📦 Components Required

| Component                     | Quantity |
|------------------------------|----------|
| NodeMCU ESP8266              | 1        |
| Inductive Proximity Sensor   | 1        |
| Capacitive Proximity Sensor  | 1        |
| IR Obstacle Sensor           | 2        |
| Servo Motor (e.g. SG90)      | 1        |
| Relay Module                 | 2        |
| Jumper Wires & Breadboard    | As needed|
| Internet Access (WiFi)       | 1        |
| Blynk App                    | 1        |
| Telegram Bot (via BotFather) | 1        |

## 🔌 Wiring Diagram

| ESP8266 Pin | Connected To                     |
|-------------|----------------------------------|
| D1          | Inductive Proximity Sensor / IR (left) |
| D2          | IR Obstacle Sensor (right)       |
| D4          | Capacitive Proximity Sensor      |
| D5          | Relay Left                       |
| D6          | Relay Right                      |
| D7          | Servo Signal Pin                 |
| 3.3V / GND  | Power for all components         |

## 📲 Blynk Integration
- Monitors trash classification.
- Uses virtual pin **V0** to show whether trash is:
  - `Organik (Non-Logam)`
  - `Non-Organik (Logam)`
  - `Tidak Dikenali`

## 💬 Telegram Alerts
Telegram bot sends messages:
- "⚠️ Tempat Sampah Organik Penuh! Harap segera dikosongkan."
- "⚠️ Tempat Sampah Non-Organik Penuh! Harap segera dikosongkan."

Bot created via [@BotFather](https://t.me/BotFather), integrated using `UniversalTelegramBot`.

## 🔁 Logic Flow

1. **Trash Detection**:
   - IR sensors detect trash presence (LOW = trash present).
2. **Classification**:
   - Inductive sensor: detects **metal** → **Non-Organic**.
   - Capacitive sensor: detects **non-metal** → **Organic**.
   - If undetected by both → Unknown.
3. **Servo Movement**:
   - Turns **left (0°)** for **Organic**.
   - Turns **right (180°)** for **Non-Organic**.
   - Returns to **center (90°)** after movement.
4. **Relay Control**:
   - Each relay activates based on bin fullness.
5. **Notifications**:
   - Telegram bot sends messages **once** per full condition.
   - Status resets when bin is emptied (sensor changes state).

## 🚀 Getting Started

1. Replace your `BOT_TOKEN`, `CHAT_ID`, `ssid`, `password`, and Blynk credentials.
2. Wire components as per the wiring table.
3. Upload code using **Arduino IDE** with **ESP8266 board** selected.
4. Monitor system via **Serial Monitor**, **Blynk App**, and **Telegram**.

---
