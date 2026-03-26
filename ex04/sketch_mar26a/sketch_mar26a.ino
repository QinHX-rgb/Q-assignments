#define LED_PIN 2
#define TOUCH_PIN 13
#define THRESHOLD 600

bool ledState = false;
unsigned long lastTriggerTime = 0;

void  gotTouch() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastTriggerTime > 300) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastTriggerTime = currentTime;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
