//define PINS
#define thermistor_Pin A0
#define photo_Pin A2
#define alert_Pin 12

//threshold
const float temp_Threshold = 50.0;
const int light_Threshold = 220;

const int beta = 3950;
const int resistance = 10;

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

  if (temperature >= temp_Threshold && brightness <= light_Threshold) {
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

  float tempC = beta / (log((1025.0 * resistance / analogValue - resistance) / resistance) + beta / 298.0) - 273.0;

  return tempC;
}

int readBrightness() {
  int brightness = analogRead(photo_Pin);
  return brightness;
}
