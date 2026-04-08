#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "QinHX";
const char* password = "123456789";

const int LED_PIN = 2;
const int TOUCH_PIN = 13;

WebServer server(80);

bool isArmed = false;
bool isAlarming = false;

unsigned long lastBlink = 0;
const long blinkSpeed = 100;

String makePage() {
  String armState = isArmed ? "已布防" : "未布防";
  String alarmState = isAlarming ? "⚠ 报警中！" : "正常";
  
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>实验8 安防主机</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">
  <h1>实验8：ESP32 安防报警系统</h1>
  <p>系统状态：<b style="color:blue;">)rawliteral" + armState + R"rawliteral(</b></p>
  <p>报警状态：<b style="color:red;">)rawliteral" + alarmState + R"rawliteral(</b></p>
  <br>
  <a href="/arm"><button style="padding:12px 24px; font-size:16px; background:green; color:white;">布防 (Arm)</button></a>
  <br><br>
  <a href="/disarm"><button style="padding:12px 24px; font-size:16px; background:red; color:white;">撤防 (Disarm)</button></a>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", makePage());
}

void handleArm() {
  isArmed = true;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location","/");
  server.send(303);
}

void handleDisarm() {
  isArmed = false;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location","/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi OK");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if (isArmed && !isAlarming) {
    if (digitalRead(TOUCH_PIN) == HIGH) {
      isAlarming = true;
    }
  }
  
  if (isAlarming) {
    if (millis() - lastBlink >= blinkSpeed) {
      lastBlink = millis();
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}