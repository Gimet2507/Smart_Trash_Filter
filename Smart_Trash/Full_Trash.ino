#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// WiFi config
const char* ssid = "tenda";
const char* password = "duakelinci";

// Telegram config
#define BOT_TOKEN "7819684068:AAFreX-rEyyTBk60Xths0Td35ZRbF2UB_yw" // Ganti dengan token bot kamu
#define CHAT_ID "1352955994"                         // Ganti dengan chat ID kamu

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// Hardware
#define IR_KIRI D1
#define IR_KANAN D2
#define RELAY_KIRI D5
#define RELAY_KANAN D6
#define SERVO_PIN D7

Servo servo;

bool sudahKirimKiri = false;
bool sudahKirimKanan = false;

void setup() {
  Serial.begin(115200);
  pinMode(IR_KIRI, INPUT);
  pinMode(IR_KANAN, INPUT);
  pinMode(RELAY_KIRI, OUTPUT);
  pinMode(RELAY_KANAN, OUTPUT);

  digitalWrite(RELAY_KIRI, LOW);
  digitalWrite(RELAY_KANAN, HIGH);

  servo.attach(SERVO_PIN);
  servo.write(0); // Buka

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");

  // Trust semua sertifikat (perlu untuk Telegram HTTPS)
  secured_client.setInsecure();
}

void loop() {
  bool kiriPenuh = digitalRead(IR_KIRI) == LOW;
  bool kananPenuh = digitalRead(IR_KANAN) == HIGH;

  // Relay
  digitalWrite(RELAY_KIRI, kiriPenuh ? HIGH : LOW);
  digitalWrite(RELAY_KANAN, kananPenuh ? LOW : HIGH);

  // Servo kontrol
  if (kiriPenuh || kananPenuh) {
    servo.write(90); // Tutup
  } else {
    servo.write(0); // Buka
  }

  // Notifikasi Telegram
  if (kiriPenuh && !sudahKirimKiri) {
    bot.sendMessage(CHAT_ID, "⚠️ Tempat Sampah Organik Penuh! Harap segera dikosongkan.", "");
    sudahKirimKiri = true;
  }
  if (!kiriPenuh) {
    sudahKirimKiri = false; // Reset kirim
  }

  if (kananPenuh && !sudahKirimKanan) {
    bot.sendMessage(CHAT_ID, "⚠️ Tempat Sampah Non-Organik Penuh! Harap segera dikosongkan.", "");
    sudahKirimKanan = true;
  }
  if (!kananPenuh) {
    sudahKirimKanan = false; // Reset kirim
  }

  delay(1000);
}
