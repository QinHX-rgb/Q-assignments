#define LED_PIN 2
#define LED_PIN_R 13
#define LED_PIN_G 12
#define LED_PIN_Y 14

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT); 
  pinMode(LED_PIN_R, OUTPUT); 
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_Y, OUTPUT);
}

void loop() {
  Serial.println("Hello ESP32!");
  
  // 同步点亮
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, HIGH);
  digitalWrite(LED_PIN_Y, HIGH);
  delay(1000);
  
  // 同步熄灭
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN_R, LOW);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_Y, LOW);
  delay(1000);
}