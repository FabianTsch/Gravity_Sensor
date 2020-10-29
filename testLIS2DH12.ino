
#include <Wire.h>
#include <DFRobot_LIS2DH12.h>


DFRobot_LIS2DH12 LIS; //Accelerometer

void setup(){
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);

  // Set measurement range
  // Ga: LIS2DH12_RANGE_2GA
  // Ga: LIS2DH12_RANGE_4GA
  // Ga: LIS2DH12_RANGE_8GA
  // Ga: LIS2DH12_RANGE_16GA
  while(LIS.init(LIS2DH12_RANGE_16GA) == -1){  //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
}

void loop(){
  acceleration();
}

/*!
 *  @brief Print the position result.
 */
void acceleration(void)
{
  int16_t x, y, z;

  delay(100);
  LIS.readXYZ(x, y, z);
  LIS.mgScale(x, y, z);
  Serial.print("Acceleration x: "); //print acceleration
  Serial.print(x);
  Serial.print(" mg \ty: ");
  Serial.print(y);
  Serial.print(" mg \tz: ");
  Serial.print(z);
  Serial.println(" mg");
}
