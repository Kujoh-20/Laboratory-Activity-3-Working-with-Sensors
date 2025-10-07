// Define PINS
#define thermistor_Pin A0
#define photo_Pin A2
#define alert_Pin 12

// Thresholds
const float temp_Threshold = 40.0; // Celsius
const int light_Threshold = 220;   // Brightness

const int beta = 3950;
const int resistance = 10000; // 10k ohm fixed resistor

void setup() {
  pinMode(alert_Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temperature = readTemperature();
  int brightness = readBrightness();

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Brightness: ");
  Serial.println(brightness);

  if (temperature >= temp_Threshold && brightness >= light_Threshold) {
    digitalWrite(alert_Pin, HIGH);
    delay(100);
    digitalWrite(alert_Pin, LOW);
    delay(100);
  } else {
    digitalWrite(alert_Pin, LOW);
  }

  delay(500);
}

float readTemperature() {
  int analogValue = analogRead(thermistor_Pin);
  float R = (1023.0 / analogValue - 1.0) * resistance; // Thermistor resistance
  float tempK = 1.0 / (log(R / resistance) / beta + 1.0 / 298.15);
  float tempC = tempK - 273.15;
  return tempC;
}

int readBrightness() {
  return analogRead(photo_Pin);
}
