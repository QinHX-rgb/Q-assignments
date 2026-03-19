// 定义LED引脚，ESP32通常板载LED连接在GPIO 2
const int ledPin = 2; 
#define LED_PIN_R 13
#define LED_PIN_G 12
#define LED_PIN_Y 14

void setup() {
  // 初始化串口通信，设置波特率为115200
  Serial.begin(115200);
  // 将LED引脚设置为输出模式
  pinMode(ledPin, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_Y, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);  // 点亮LED
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, HIGH);
  digitalWrite(LED_PIN_Y, HIGH);
  Serial.println("LED ON");    // 串口输出提示
  delay(500);                 // 保持0.5秒（500毫秒）
  
  digitalWrite(ledPin, LOW);   // 熄灭LED
  digitalWrite(LED_PIN_R, LOW);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_Y, LOW);
  Serial.println("LED OFF");   // 串口输出提示
  delay(500);                 // 保持0.5秒
}