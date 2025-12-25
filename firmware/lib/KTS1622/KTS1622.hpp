/**
 * @file KTS1622.hpp
 * @author your name (you@domain.com)
 * @brief driver for Kinetic KTS1622 IO-Expander
 * @version 0.1
 * @date 2025-12-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdint.h>

#ifndef __KTS1622_HPP__
#define __KTS1622_HPP__

class KTS1622 {
private:
    //register addresses
    static constexpr uint8_t reg_addr_input_port_0              = 0x00;
    static constexpr uint8_t reg_addr_input_port_1              = 0x01;
    static constexpr uint8_t reg_addr_output_port_0             = 0x02;
    static constexpr uint8_t reg_addr_output_port_1             = 0x03;
    static constexpr uint8_t reg_addr_polarity_port_0           = 0x04;
    static constexpr uint8_t reg_addr_polarity_port_1           = 0x05;
    static constexpr uint8_t reg_addr_config_port_0             = 0x06;
    static constexpr uint8_t reg_addr_config_port_1             = 0x07;
    static constexpr uint8_t reg_addr_drive_strength_port_0a    = 0x40;
    static constexpr uint8_t reg_addr_drive_strength_port_0b    = 0x41;
    static constexpr uint8_t reg_addr_drive_strength_port_1a    = 0x42;
    static constexpr uint8_t reg_addr_drive_strength_port_1b    = 0x43;
    static constexpr uint8_t reg_addr_input_latch_port_0        = 0x44;
    static constexpr uint8_t reg_addr_input_latch_port_1        = 0x45;
    static constexpr uint8_t reg_addr_PUD_enable_port_0         = 0x46;
    static constexpr uint8_t reg_addr_PUD_enable_port_1         = 0x47;
    static constexpr uint8_t reg_addr_PUD_select_port_0         = 0x48;
    static constexpr uint8_t reg_addr_PUD_select_port_1         = 0x49;
    static constexpr uint8_t reg_addr_INT_mask_port_0           = 0x4A;
    static constexpr uint8_t reg_addr_INT_mask_port_1           = 0x4B;
    static constexpr uint8_t reg_addr_INT_status_port_0         = 0x4C;
    static constexpr uint8_t reg_addr_INT_status_port_1         = 0x4D;
    static constexpr uint8_t reg_addr_output_port_conf          = 0x4F;
    static constexpr uint8_t reg_addr_INT_edge_port_0a          = 0x50;
    static constexpr uint8_t reg_addr_INT_edge_port_0b          = 0x51;
    static constexpr uint8_t reg_addr_INT_edge_port_1a          = 0x52;
    static constexpr uint8_t reg_addr_INT_edge_port_1b          = 0x53;
    static constexpr uint8_t reg_addr_INT_clear_port_0          = 0x54;
    static constexpr uint8_t reg_addr_INT_clear_port_1          = 0x55;
    static constexpr uint8_t reg_addr_input_status_port_0       = 0x56;
    static constexpr uint8_t reg_addr_input_status_port_1       = 0x57;
    static constexpr uint8_t reg_addr_output_pin_conf_port_0    = 0x58;
    static constexpr uint8_t reg_addr_output_pin_conf_port_1    = 0x59;
    static constexpr uint8_t reg_addr_sw_debounce_enable_port_0 = 0x5A;
    static constexpr uint8_t reg_addr_sw_debounce_enable_port_1 = 0x5B;
    static constexpr uint8_t reg_addr_sw_debounce_count         = 0x5C;

    //private storage variables
    const uint8_t i2c_address;

    //function pointers
    uint8_t (*callback_readByte)(uint8_t deviceAddress, uint8_t registerAddress);
    void (*callback_writeByte)(uint8_t deviceAddress, uint8_t registerAddress, uint8_t value);

    /**
     * @brief check if callbacks are set -> if not throws exception
     * @exception Callback is Nullptr
     */
    void checkCallbackFunc();

    void modifyBit(uint8_t regAdr, uint8_t bitNum, bool newVal);


public:
    /**
     * @brief Construct a new KTS1622 object
     * 
     * @param[in] address I2C address of the device
     * @param[in] readByte pointer to a function to read one byte from an I2C device
     * @param[in] writeByte pointer to a function to write one byte to an I2C device
     */
    KTS1622(uint8_t address, uint8_t (*readByte)(uint8_t deviceAddress, uint8_t registerAddress), void (*writeByte)(uint8_t deviceAddress, uint8_t registerAddress, uint8_t value));
    KTS1622(KTS1622 &other) = delete;
    KTS1622(KTS1622 &&other) = delete;
    ~KTS1622();

    enum ports{
        PORT0 = 0,
        PORT1 = 1,
    };

    enum pins{
        PIN0 = 0,
        PIN1 = 1,
        PIN2 = 2,
        PIN3 = 3,
        PIN4 = 4,
        PIN5 = 5,
        PIN6 = 6,
        PIN7 = 7,
    };

    enum inversion{
        NOT_INVERTED = 0,
        INVERTED = 1,
    };

    enum direction{
        OUTPUT = 0,
        INPUT = 1,
    };

    /**
     * @brief get the value of all pins of one port
     * 
     * @param port port to be read from
     * @return uint8_t pin values
     * @exception Undefined Port -> selected port is not defined
     * @exception Callback is nullpointer -> callback_readByte() not set
     * @exception Unexpected Error -> something very unexpected went wrong
     */
    uint8_t getPortInputValue(ports port);

    /**
     * @brief function to get the input value of one specific pin
     * 
     * @param port port the pin is located in
     * @param pin pin to be read
     * @exception Undefined Port -> selected port is not defined
     * @exception Callback is nullpointer -> callback_readByte() not set
     * @exception Unexpected Error -> something very unexpected went wrong
     */
    bool getPinInputValue(ports port, pins pin);

    /**
     * @brief get value of output port register of port
     * 
     * @param port port to read
     * @return uint8_t value of the register
     */
    uint8_t getPortOutputValue(ports port);

    /**
     * @brief set the output of one port of the device
     * 
     * @param port port the value shall be written to
     * @param value value to be written
     */
    void setPortOutputValue(ports port, uint8_t value);

    /**
     * @brief set the value of one pin
     * 
     * @param port port the pin is located in
     * @param pin pin to be written to
     * @param value pin state to be set
     */
    void setPinOutputValue(ports port, pins pin, bool value);

    /**
     * @brief set the polarity of all pins in the port
     * 
     * @param port port to set
     * @param polarity polarity to set
     */
    void setPortPolarity(ports port, inversion polarity);

    /**
     * @brief set polarity of one specific pin
     * 
     * @param port port the pin is located in
     * @param pin pin to set
     * @param polarity polarity to set
     */
    void setPinPolarity(ports port, pins pin, inversion polarity);

    /**
     * @brief set the direction of one specific pin
     * 
     * @param port port the pin is located in
     * @param pin pin to set direction of
     * @param dir direction to set
     */
    void setPinDirection(ports port, pins pin, direction dir);

    /**
     * @brief enable latching of input value of specific pin
     * 
     * @param port 
     * @param pin 
     */
    void enableLatch(ports port, pins pin);

    void disableLatch(ports port, pins pin);

    void enablePulldown(ports port, pins pin);

    void disablePulldown(ports port, pins pin);

    void enablePullup(ports port, pins pin);

    void disablePulldown(ports port, pins pin);

    void enableInterrupt(ports port, pins pin);

    void disableInterrupt(ports port, pins pin);

    

    




};

#endif /*__KTS1622_HPP__*/
