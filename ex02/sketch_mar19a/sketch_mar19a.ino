unsigned long myTime;

void setup() {
  Serial.begin(115200);
}

void loop() {
  myTime = millis(); // 获取当前时间
  Serial.println(myTime); // 在串口监视器打印，你会看到数字飞速增长
  delay(1000);
}