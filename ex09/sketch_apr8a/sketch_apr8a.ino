#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "QinHX";
const char* password = "123456789";

#define TOUCH_PIN T0

WebServer server(80);

String getHtml() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>实时触摸传感器仪表盘</title>
  <style>
    body{
      text-align:center;
      font-family:Arial;
      margin-top:100px;
      background:#f7f7f7;
    }
    .value{
      font-size:80px;
      font-weight:bold;
      color:#2196F3;
      margin:40px 0;
    }
    .title{
      font-size:28px;
      color:#333;
    }
  </style>
</head>
<body>
  <div class="title">ESP32 实时触摸传感器数值</div>
  <div class="value" id="touchValue">--</div>

  <script>
    function updateValue() {
      var xhr = new XMLHttpRequest();
      xhr.open('GET', '/getData', true);
      xhr.onload = function() {
        if (xhr.status == 200) {
          document.getElementById('touchValue').innerText = xhr.responseText;
        }
      }
      xhr.send();
    }
    setInterval(updateValue, 100);  
</body>
</html>
)rawliteral";
  return html;
}

void handleData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", getHtml());
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 连接成功");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/getData", handleData);  
  server.begin();
}

void loop() {
  server.handleClient();
}