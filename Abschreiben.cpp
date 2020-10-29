#include "mbed.h"

// Global Variables
Serial pc(USBTX, USBRX);
I2C i2c(p9,p10);

// Functions
int8_t init();
void readXYZ(int16_t&, int16_t&, int16_t&);
uint8_t sensorAddress = 0x18<<1;

int main(){
  int16_t x,y,z;
  wait_ms(100);
  while(init() == -1){
    pc.printf("No I2C devices found\n\r");
    wait_ms(1000);
  }

  while(true){
    wait_ms(100);
    readXYZ(x,y,z);
    pc.printf("Acceleration x: %d ",x); //print acceleration
    pc.printf(" mg \ty: %d ",y);
    pc.printf(" mg \tz: %d ",z);
    pc.printf(" mg");
  }
}

// Function Declarations
int8_t init(){
  uint8_t regAdresse;
  int ack;
  char data[7];

  uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00, 0x00, 0x00, 0x00};
  regAdresse = 0x80 | 0x20;
  data[0] = regAdresse;
  for(uint8_t i = 0; i < sizeof(ctrl_reg_values); ++i)
    data[i+1] = ctrl_reg_values[i];
  ack = i2c.write(sensorAddress, data, sizeof(data));

  return ack;
}

void readXYZ(int16_t& x, int16_t& y, int16_t& z){
  char data[1];
  data[0] = 0x80 | 0x28;
  uint8_t sensorData[6];
  i2c.write(sensorAddress, data, 1, true);
  i2c.read(sensorAddress, (char*)sensorData, sizeof(sensorData));

  x = ((int8_t) sensorData[1])*256+sensorData[0];
  y = ((int8_t) sensorData[3])*256+sensorData[2];
  z = ((int8_t) sensorData[5])*256+sensorData[4];

  // Scale Value 
  uint8_t mgScaleVel = 16;
  x = (int32_t)x*1000/(1024*mgScaleVel);
  y = (int32_t)y*1000/(1024*mgScaleVel);
  z = (int32_t)z*1000/(1024*mgScaleVel);
}
