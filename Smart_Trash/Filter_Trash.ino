#define BLYNK_TEMPLATE_ID "TMPL6afRPKJLp"
#define BLYNK_TEMPLATE_NAME "IOT SAMPAH"
#define BLYNK_AUTH_TOKEN "eGrrfjeMmIX8WN4U3KKVBXY-cS7uX0g-"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Ganti dengan WiFi dan Blynk Token kamu
char auth[] = "eGrrfjeMmIX8WN4U3KKVBXY-cS7uX0g-";
char ssid[] = "tenda";
char pass[] = "duakelinci";

// Pin setup
#define PIN_PROX_INDUKTIF D1     // Sensor logam
#define PIN_PROX_KAPASITIF D4    // Sensor non-logam
#define PIN_IR_OBS D5            // IR obstacle
#define PIN_RELAY D7             // Relay
#define PIN_SERVO D6             // Servo

Servo servo;
int delayGerak = 1000;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(PIN_PROX_INDUKTIF, INPUT);
  pinMode(PIN_PROX_KAPASITIF, INPUT);
  pinMode(PIN_IR_OBS, INPUT);
  pinMode(PIN_RELAY, OUTPUT);

  servo.attach(PIN_SERVO);
  servo.write(90); // posisi tengah
  digitalWrite(PIN_RELAY, LOW);
}

void loop() {
  Blynk.run();

  bool adaLogam = digitalRead(PIN_PROX_INDUKTIF) == HIGH;
  bool adaNonLogam = digitalRead(PIN_PROX_KAPASITIF) == HIGH;
  bool adaSampah = digitalRead(PIN_IR_OBS) == LOW; // LOW = ada objek

  // Jika ada sampah → nyalakan relay
  if (adaSampah) {
    digitalWrite(PIN_RELAY, HIGH);
  } else {
    digitalWrite(PIN_RELAY, LOW);
  }

  if (adaSampah) {
    if (adaLogam) {
      Serial.println("Sampah Non-Organik (Logam)");
      Blynk.virtualWrite(V0, "Non-Organik (Logam)");
      servo.write(180); // kanan
      delay(delayGerak);
      servo.write(90);  // kembali tengah
    } else if (adaNonLogam) {
      Serial.println("Sampah Organik (Non-Logam)");
      Blynk.virtualWrite(V0, "Organik (Non-Logam)");
      servo.write(0); // kiri
      delay(delayGerak);
      servo.write(90); // kembali tengah
    } else {
      Serial.println("Sampah tidak dikenali");
      Blynk.virtualWrite(V0, "Tidak Dikenali");
    }

    delay(2000);
  }

  delay(100);
}
