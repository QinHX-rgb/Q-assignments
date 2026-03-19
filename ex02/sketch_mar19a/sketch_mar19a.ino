#define LED_PIN_R 13
unsigned long previousMillis = 0; // 记录上一次变灯的时间
int state = LOW;          // 记录灯是亮还是灭

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN_R, OUTPUT);
}

void loop() {
  if (millis() - previousMillis >= 500) {
    previousMillis = millis();
    state = !state;
    digitalWrite(LED_PIN_R, state);
  }
}