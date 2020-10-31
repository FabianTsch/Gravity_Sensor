/*!
 * @file DFRobot_LIS2DH12.cpp
 * @brief DFRobot's Read LIS2DH12 data
 * @n This example is in order to achieve the serial port to receive LIS2DH12 back to the data
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2016-10-13
 * @https://github.com/DFRobot/DFRobot_LIS2DH12
 */

#include <DFRobot_LIS2DH12.h>


uint8_t DFRobot_LIS2DH12::getSensorAdresse(){return sensorAddress;}

int8_t DFRobot_LIS2DH12::init(uint8_t range, I2C& i2c){
    uint8_t regAdresse;
    int ack;
    char data[7];
    setRange(LIS2DH12_RANGE_2GA);
    i2c_bus = &i2c;


    uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00, range, 0x00, 0x00};
    regAdresse = 0x80 | 0x20;
    data[0] = regAdresse;
    for(uint8_t i = 0; i < sizeof(ctrl_reg_values); ++i)
      data[i+1] = ctrl_reg_values[i];
    ack = i2c.write(sensorAddress, data, sizeof(data));

    return ack;
}

void DFRobot_LIS2DH12::readXYZ(int16_t &x, int16_t &y, int16_t &z) {
    //read x, y, z data
    char data[1];
    data[0] = 0x80 | 0x28;
    uint8_t sensorData[6];
    i2c_bus->write(sensorAddress, data, 1, true);
    i2c_bus->read(sensorAddress, (char*)sensorData, sizeof(sensorData));

    x = ((int8_t) sensorData[1])*256+sensorData[0];
    y = ((int8_t) sensorData[3])*256+sensorData[2];
    z = ((int8_t) sensorData[5])*256+sensorData[4];
}

void DFRobot_LIS2DH12::mgScale(int16_t &x, int16_t &y, int16_t &z){
    x = (int32_t)x*1000/(1024*mgScaleVel); //transform data to millig, for 2g scale axis*1000/(1024*16),
    y = (int32_t)y*1000/(1024*mgScaleVel); //for 4g scale axis*1000/(1024*8),
    z = (int32_t)z*1000/(1024*mgScaleVel); //for 8g scale axis*1000/(1024*4)
}

void DFRobot_LIS2DH12::setRange(uint8_t range){
    switch(range)
    {
    case LIS2DH12_RANGE_2GA:
        mgScaleVel = 16;
        break;

    case LIS2DH12_RANGE_4GA:
        mgScaleVel = 8;
        break;

    case LIS2DH12_RANGE_8GA:
        mgScaleVel = 4;
        break;

    case LIS2DH12_RANGE_16GA:
        mgScaleVel = 2;
        break;

    default:
        mgScaleVel = 16;
        break;
    }
}


uint8_t DFRobot_LIS2DH12::readReg(uint8_t regAddress, char *regValue, uint8_t quantity, bool autoIncrement = true){
    int ack;
    if(autoIncrement){
    	char data[1];
	    data[0] = 0x80 | regAddress;
	    i2c_bus->write(sensorAddress, data, 1, true);
	    ack = i2c_bus->read(sensorAddress, regValue, sizeof(regValue));
	    return ack;
    }
    else{
    	ack = -1;
    	return ack;
    }
}

uint8_t DFRobot_LIS2DH12::writeReg(uint8_t regAddress, char *regValue, size_t quantity, bool autoIncrement = true){
    int ack;
    if(autoIncrement){
    	char data[7] = {0};
    	data[0] = 0x80 | regAddress;
    	for(uint8_t i = 0; i < quantity; ++i)
      	data[i+1] = regValue[i];
    	ack = i2c_bus->write(sensorAddress, data, sizeof(data));
    	return ack;
    }
    else{
    	ack = -1;
    	return ack;
    }
}
