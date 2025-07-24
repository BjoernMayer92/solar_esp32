const int analogPin=36;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10000);
}

void loop() {
  int adcValue = analogRead(analogPin);
  float voltage = adcValue*3.3/4095.0;
  Serial.printf("ADC Value: %d, Voltage: %.3f V\n", adcValue, voltage);
  delay(500);
  // put your main code here, to run repeatedly:

}
