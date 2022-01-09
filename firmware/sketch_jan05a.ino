#include <SPI.h>

const byte slaveSelectPin = 53;

uint8_t status_data = 0;
uint16_t bridge_data = 0;
uint16_t temperature_data = 0;

void setup() {
  Serial.begin(9600);
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin,HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.begin();
  Serial.println("PSI");
}

void loop() {
  digitalWrite(slaveSelectPin,LOW);   
  delay(1);
  
  uint8_t data[4];
  
  for(char i = 3; i >= 0; --i) {
    data[i] = SPI.transfer(0xFF);
  }

  status_data = data[3] >> 6;
  bridge_data = ((data[3] & 0x3F) << 8) | data[2];
  temperature_data = (data[1] << 3) | ((data[0] & 0xE0) >> 5);
  delay(1);
  digitalWrite(slaveSelectPin,HIGH);
  delay(100);

//  Serial.print("Status: ");
//  Serial.print(status_data);
//  Serial.print(" bridge_data: ");
//  Serial.print(bridge_data);
//  Serial.print(" temp_data: ");
//  Serial.print(temperature_data);
//  Serial.print(" in C: ");
  uint32_t temp_in_c = (((uint32_t)temperature_data) * 200) / 2047 - 50;
//  Serial.println(temp_in_c);

  // 10-90% sensor min 0psi to max 1psi

  float output_max = 14745; // 90% of 2^13
  float output_min = 1638; // 10% of 2^14
  float preassure_min = 0; // 0psi
  float preassure_max = 1; // 1psi

  float preassure = (((float)bridge_data) - output_min) * (preassure_max - preassure_min) / (output_max - output_min) + preassure_min;
  if (bridge_data <= output_min) {
    preassure = 0;
  }
//  Serial.print("psi: ");
  Serial.println(preassure);
  
  
}
