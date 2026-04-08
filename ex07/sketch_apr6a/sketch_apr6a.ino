#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "QinHX";
const char* password = "123456789";
const int LED_PIN = 2; 

WebServer server(80);

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Web无极调光器</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    input[type=range] { width: 80%; max-width: 300px; }
  </style>
</head>
<body>
  <h2>ESP32 无极调光器</h2>
  <p>当前亮度: <span id="pwmValue">0</span></p>
  
  <input type="range" min="0" max="255" value="0" id="slider" oninput="sendPWM(this.value)">

  <script>
    function sendPWM(val) {
      document.getElementById("pwmValue").innerText = val; // 更新网页显示的数值
      fetch(`/pwm?value=${val}`); // 向ESP32发送形如 /pwm?value=128 的请求
    }
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makePage());
}

void handlePWM() {
  if (server.hasArg("value")) {
    int pwmValue = server.arg("value").toInt(); 

    analogWrite(LED_PIN, pwmValue); 
    
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Error: No value provided");
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0); 
  
  WiFi.begin(ssid, password);
  Serial.print("正在连接 WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 连接成功！");
  Serial.print("请在手机或电脑浏览器输入以下地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/pwm", handlePWM); 
  
  server.begin();
}

void loop() {
  server.handleClient();
}