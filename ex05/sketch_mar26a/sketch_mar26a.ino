#define LED_PIN 2
#define TOUCH_PIN 13
#define THRESHOLD 600

// PWM 设置
const int freq = 5000;
const int resolution = 8;

int brightness = 0;//亮度
int fadeAmount = 5;//速度

int speedLevel = 1; 
unsigned long lastTriggerTime = 0;

void gotTouch() {
  unsigned long currentTime = millis();
  if (currentTime - lastTriggerTime > 300) {
    speedLevel++;
    if (speedLevel > 3) speedLevel = 1;
    lastTriggerTime = currentTime;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ledcAttach(LED_PIN, freq, resolution);
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(LED_PIN, brightness);

  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }


  Serial.print("Touch Value: ");
  Serial.println(touchRead(TOUCH_PIN));
  delay(100);
}