#define LED_PIN 2
#define TOUCH_PIN 13
#define THRESHOLD 600

// PWM 设置
const int freq = 5000;
const int resolution = 8;

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
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Touch Value: ");
  Serial.println(touchRead(TOUCH_PIN));
  delay(100);
}