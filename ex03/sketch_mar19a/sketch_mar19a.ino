#define LED_PIN_R 13
unsigned long previousMillis = 0;
int step = 0;
int interval = 200;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN_R, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis= millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

  int currentState = digitalRead(LED_PIN_R);  // 定义当前LED状态
    digitalWrite(LED_PIN_R, !currentState);

  if (digitalRead(LED_PIN_R) == HIGH) {
      if (step < 3 || step >= 6) interval = 200;
      else interval = 600;                      
    } 
    else {
      step++;
      if (step < 10) {
        interval = 200; 
      } else {
        interval = 2000;
        step = 0;
      }
    }
  }
}
