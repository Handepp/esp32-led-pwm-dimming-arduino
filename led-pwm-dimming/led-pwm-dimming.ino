#define LED_PIN 2

// PWM config ESP32
const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8; // 0-255 brightness

// fade config
int brightness = 0;
int fadeAmount = 5;

unsigned long previousMillis = 0;
const long interval = 30; // speed fade (ms)

void setup() {
  Serial.begin(115200);

  // setup PWM channel
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(LED_PIN, pwmChannel);

  Serial.println("ESP32 PWM LED Dimming Started");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // set brightness
    ledcWrite(pwmChannel, brightness);

    // update brightness
    brightness += fadeAmount;

    // reverse direction at limits
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    Serial.print("Brightness: ");
    Serial.println(brightness);
  }
}