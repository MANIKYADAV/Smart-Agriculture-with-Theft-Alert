#include <Arduino.h>
#include <DHT.h>

#define DHTPIN D2        // DHT11 data pin
#define DHTTYPE DHT11    // Sensor type
#define SOIL_PIN A0      // Soil moisture analog pin
#define LDR_PIN A1       // LDR analog pin
#define PUMP_PIN D3       // LED1 control pin
#define BUZZER_PIN D5      // LED2 control pin
#define PIR_PIN D4       // PIR sensor digital pin

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Read soil moisture
  int soilValue = analogRead(SOIL_PIN);
  float moisturePercent = map(soilValue, 1023, 0, 0, 100); // Adjust if needed

  // Read LDR value
  int ldrValue = analogRead(LDR_PIN);

  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read PIR sensor
  int motionDetected = digitalRead(PIR_PIN);

  // Display readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  Serial.print("LDR Value (light level): ");
  Serial.println(ldrValue);

  Serial.print("Motion Detected: ");
  Serial.println(motionDetected ? "YES" : "NO");

  // LED1 control logic (temperature or moisture AND motion)
  if ((temperature >= 25 || moisturePercent >= 70)) {
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("MOTOR ON");
  } else {
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("MOTOR OFF");
  }

  // LED2 control logic (motion OR light level > 500)
  if (motionDetected || ldrValue > 500) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("BUZZER ON");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("BUZZER OFF");
  }

  Serial.println("------------------------");
  delay(2000);
}