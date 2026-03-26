#define LED_PIN_R 13
#define LED_PIN_B 14

// PWM 设置
const int freq = 5000;
const int resolution = 8;

// 呼吸控制变量
int brightness = 0;
int fadeAmount = 5;
int interval = 10;//频闪速率

unsigned long lastFadeTime = 0;

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastFadeTime >= interval) {
    lastFadeTime = currentMillis;

    ledcWrite(LED_PIN_R, brightness);
    ledcWrite(LED_PIN_B, 255 - brightness);

    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}
