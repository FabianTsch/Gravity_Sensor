
#include "mbed.h"
#include <DFRobot_LIS2DH12.h>

Serial pc(USBTX, USBRX);
I2C i2c(p9,p10);
DFRobot_LIS2DH12 LIS(0x18<<1); //Accelerometer


int main(){

  // init loop
  while(LIS.init(LIS2DH12_RANGE_2GA) != 0){
    pc.printf("No I2C devices found\n\r");
    wait_ms(1000);
  }

  // main loop
  while(true){
    int16_t x, y, z;
    wait_ms(100); //delay(100);
    LIS.readXYZ(x, y, z);
    LIS.mgScale(x, y, z);
    pc.printf("Acceleration x: %d ",x); //print acceleration
    pc.printf(" mg \ty: %d ",y);
    pc.printf(" mg \tz: %z ",z);
    pc.printf(" mg");
  }
}
