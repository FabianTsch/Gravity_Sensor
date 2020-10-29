/*!
 * @file DFRobot_LIS2DH12.h
 * @brief DFRobot's Read LIS2DH12 data
 * @n This example achieve receiving LIS2DH12  data via serial
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2016-10-13
 * @https://github.com/DFRobot/DFRobot_LIS2DH12
 */


#ifndef DFRobot_LIS2DH12_h
#define DFRobot_LIS2DH12_h

#include <stdlib.h>
#include <stdint.h>

#define LIS2DH12_RANGE_2GA	0x00
#define LIS2DH12_RANGE_4GA	0x10
#define LIS2DH12_RANGE_8GA	0x20
#define LIS2DH12_RANGE_16GA	0x30

class DFRobot_LIS2DH12 {
public:
	DFRobot_LIS2DH12(uint8_t address) : sensorAddress(address){}
	uint8_t getSensorAdresse();
	int8_t init(uint8_t range); ///< Initialization function
	void readXYZ(int16_t&, int16_t&, int16_t&); ///< read x, y, z data
	void mgScale(int16_t&, int16_t&, int16_t&); ///< transform data to millig
	//void readReg(uint8_t, uint8_t *, uint8_t, bool autoIncrement = true);
	//uint8_t writeReg(uint8_t, uint8_t *, size_t, bool autoIncrement = true);

private:
	uint8_t sensorAddress; ///< IIC address of the sensor
	void setRange(uint8_t range);
	uint8_t mgPerDigit;
	uint8_t  mgScaleVel;
};
#endif
