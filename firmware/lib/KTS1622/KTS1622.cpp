#include <KTS1622.hpp>
#include <stdexcept>



KTS1622::KTS1622(uint8_t address, uint8_t (*readByte)(uint8_t deviceAddress, uint8_t registerAddress), void (*writeByte)(uint8_t deviceAddress, uint8_t registerAddress, uint8_t value)) : i2c_address(address){
    if (callback_readByte == 0){
        throw std::runtime_error("callback pointer cannot be null");
    }

    if (callback_writeByte == 0){
        throw std::runtime_error("callback pointer cannot be null");
    }

    callback_readByte = readByte;
    callback_writeByte = writeByte;
}

void KTS1622::checkCallbackFunc(){
    if (callback_readByte == nullptr){
        throw std::runtime_error("Callback is Nullptr");
    }
    if (callback_writeByte == nullptr){
        throw std::runtime_error("Callback is Nullptr");
    }
}

uint8_t KTS1622::getPortInputValue(ports port){

    checkCallbackFunc();

    switch (port) {
        case PORT0:
            return callback_readByte(i2c_address, reg_addr_input_port_0);
            break;
        case PORT1:
            return callback_readByte(i2c_address, reg_addr_input_port_1);
            break;
    default:
        throw std::runtime_error("Undefined Port");
    }
}

bool KTS1622::getPinInputValue(ports port, pins pin){
    //exception not handled since they would be passed to caller
    uint8_t _val = getPortInputValue(port);
    
    return 0 != (_val && 1<<pin);
}

void KTS1622::setPortOutputValue(ports port, uint8_t value){
    
    checkCallbackFunc();

    switch (port){
    case PORT0:
        callback_writeByte(i2c_address, reg_addr_output_port_0, value);
        break;
    
    case PORT1:
        callback_writeByte(i2c_address, reg_addr_output_port_1, value);
        break;
    
    default:
        throw std::runtime_error("Undefined Port");
    }
}

uint8_t KTS1622::getPortOutputValue(ports port){
    
    checkCallbackFunc();

    switch (port){
        case PORT0:
            return callback_readByte(i2c_address, reg_addr_output_port_0);
            break;

        case PORT1:
            return callback_readByte(i2c_address, reg_addr_output_port_1);
            break;
    
        default:
            throw std::runtime_error("Undefined Port");
    }    
}

void KTS1622::modifyBit(uint8_t regAdr, uint8_t bitNum, bool newVal){
    
    checkCallbackFunc();

    //get old reg value and modify target bit value
    uint8_t _val = callback_readByte(i2c_address, regAdr);
    _val &= ~static_cast <uint8_t> (1 << bitNum);
    _val |= static_cast <uint8_t> (newVal << bitNum);

    callback_writeByte(i2c_address, regAdr, _val);
}

void KTS1622::setPinOutputValue(ports port, pins pin, bool value){

    switch (port){
        case PORT0:
            modifyBit(reg_addr_output_port_0, pin, value);
            break;
        
        case PORT1:
            modifyBit(reg_addr_output_port_1, pin, value);
            break;

        default:
            throw std::runtime_error("Undefined Port");
    }    
}

void KTS1622::setPortPolarity(ports port, inversion polarity){
    
    checkCallbackFunc();

    uint8_t _val = 0;

    switch (polarity) {
        case NOT_INVERTED:
            _val = 0x00;
            break;

        case INVERTED:
            _val = 0xFF;
            break;
    }
    
    switch (port){
        case PORT0:
            callback_writeByte(i2c_address, reg_addr_polarity_port_0, _val);
            break;

        case PORT1:
            callback_writeByte(i2c_address, reg_addr_polarity_port_1, _val);
            break;
        
        default:
            throw std::runtime_error("Undefined Port");
    }

}

void KTS1622::setPinPolarity(ports port, pins pin, inversion polarity){
    switch (port) {
        case PORT0:
            modifyBit(reg_addr_polarity_port_0, pin, polarity);
            break;

        case PORT1:
            modifyBit(reg_addr_polarity_port_1, pin, polarity);
            break;

        default:
            throw std::runtime_error("Undefined Port");
    }
};

void KTS1622::setPinDirection(ports port, pins pin, direction dir){
    switch (port) {
        case PORT0:
            modifyBit(reg_addr_config_port_0, pin, dir);
            break;
        
        case PORT1:
            modifyBit(reg_addr_config_port_1, pin, dir);
            break;
        
        default:
            throw std::runtime_error("Undefined Port");
    }
}
