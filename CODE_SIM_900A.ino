#include <SoftwareSerial.h>

SoftwareSerial sim900a(7, 8); // RX, TX pins for SIM900A
int relayPins[] = {2, 3, 4, 5}; // Digital pins for controlling relays
String authorizedPhoneNumber = "+84339219366"; // Số điện thoại được ủy quyền

void setup() {
  Serial.begin(9600); // Kết nối với Serial Monitor
  sim900a.begin(9600);

  Serial.println("Starting communication with SIM900A...");
  delay(1000);

  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  // Cấu hình SIM900A để nhận tin nhắn SMS
  sim900a.println("AT+CMGF=1"); // Chọn chế độ văn bản
  delay(1000);
  sim900a.println("AT+CNMI=2,2,0,0,0"); // Cấu hình để nhận tin nhắn tức thì
  delay(1000);
}

void loop() {
  if (sim900a.available()) {
    String message = sim900a.readStringUntil('\n');
    message.trim();
    Serial.println("Received message: " + message);

    if (message.startsWith("RELAY1=ON")) {
      digitalWrite(relayPins[0], HIGH); // Bật relay 1
      sim900a.println("Relay 1 is ON.");
      sendSMS("Relay 1 is ON.");
    } else if (message.startsWith("RELAY1=OFF")) {
      digitalWrite(relayPins[0], LOW); // Tắt relay 1
      sim900a.println("Relay 1 is OFF.");
      sendSMS("Relay 1 is OFF.");
    } else if (message.startsWith("RELAY2=ON")) {
      digitalWrite(relayPins[1], HIGH); // Bật relay 2
      sim900a.println("Relay 2 is ON.");
      sendSMS("Relay 2 is ON.");
    } else if (message.startsWith("RELAY2=OFF")) {
      digitalWrite(relayPins[1], LOW); // Tắt relay 2
      sim900a.println("Relay 2 is OFF.");
      sendSMS("Relay 2 is OFF.");
    } else if (message.startsWith("RELAY3=ON")) {
      digitalWrite(relayPins[2], HIGH); // Bật relay 3
      sim900a.println("Relay 3 is ON.");
      sendSMS("Relay 3 is ON.");
    } else if (message.startsWith("RELAY3=OFF")) {
      digitalWrite(relayPins[2], LOW); // Tắt relay 3
      sim900a.println("Relay 3 is OFF.");
      sendSMS("Relay 3 is OFF.");
    } else if (message.startsWith("RELAY4=ON")) {
      digitalWrite(relayPins[3], HIGH); // Bật relay 4
      sim900a.println("Relay 4 is ON.");
      sendSMS("Relay 4 is ON.");
    } else if (message.startsWith("RELAY4=OFF")) {
      digitalWrite(relayPins[3], LOW); // Tắt relay 4
      sim900a.println("Relay 4 is OFF.");
      sendSMS("Relay 4 is OFF.");
    }
  }
}

void sendSMS(String message) {
  sim900a.println("AT+CMGF=1"); // Chọn chế độ văn bản
  delay(1000);
  sim900a.println("AT+CMGS=\"" + authorizedPhoneNumber + "\""); // Gửi tin nhắn đến số điện thoại ủy quyền
  delay(1000);
  sim900a.print(message);
  sim900a.print((char)26); // Gửi dấu CTRL+Z để kết thúc tin nhắn
  delay(1000);
}
