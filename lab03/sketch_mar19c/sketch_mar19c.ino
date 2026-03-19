// 定义LED引脚
const int ledPin = 2;   
#define LED_PIN_R 13
#define LED_PIN_G 12
#define LED_PIN_Y 14

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);

  // 初始化所有引脚
  ledcAttach(ledPin, freq, resolution);
  ledcAttach(LED_PIN_R, freq, resolution);
  ledcAttach(LED_PIN_G, freq, resolution); 
  ledcAttach(LED_PIN_Y, freq, resolution);
}

// 定义一个呼吸函数，传入引脚号即可
void breathe(int pin) {
  Serial.printf("Pin %d is breathing...\n", pin);
  
  // 逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){ 
    ledcWrite(pin, dutyCycle); 
    delay(5);
  }

  // 逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(pin, dutyCycle);   
    delay(5);
  }
}

void loop() {
  // 依次调用呼吸函数
  breathe(ledPin);    // 板载蓝灯
  breathe(LED_PIN_R); // 红灯
  breathe(LED_PIN_G); // 绿灯
  breathe(LED_PIN_Y); // 黄灯

  delay(500);
}