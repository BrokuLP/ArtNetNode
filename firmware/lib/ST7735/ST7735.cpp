#include <ST7735.hpp>

void ST7735::sendDataByte(uint8_t data){

    //initiate transaction
    writePin(pinA0, true);
    writePin(pinCS, false);

    //send data via SPI
    transmitByte(data);

    //end transaction
    writePin(pinA0, false);
    writePin(pinCS, true);
}

void ST7735::sendCMDByte(commands cmd){

    //initiate transaction
    writePin(pinA0, false);
    writePin(pinCS, false);

    //send data via SPI
    transmitByte(cmd);

    //end transaction
    writePin(pinA0, false);
    writePin(pinCS, true);
}