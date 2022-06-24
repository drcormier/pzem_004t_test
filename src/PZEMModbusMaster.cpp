/*
 * File: PZEMModbusMaster.cpp
 * Project: src
 * File Created: Saturday, 18th June 2022 5:38:20 pm
 * Author: Daniel Cormier
 * -----
 * Last Modified: Friday, 24th June 2022 8:54:17 am
 * Modified By: Daniel Cormier
 * -----
 * Copyright 2022 Daniel Cormier
 */

#include "PZEMModbusMaster.h"

PZEMModbusMaster::PZEMModbusMaster()
{
    power.voltage_usage    = 0;
    power.current_usage    = 0;
    power.active_power     = 0;
    power.active_energy    = 0;
    power.frequency        = 0;
    power.power_factor     = 0;
    power.over_power_alarm = false;
    power.apparent_power   = 0;
    power.phase_angle      = 0;
}

/**
 * Gets two response buffers intended to be interpreted as a 32 bit value.
 * @param u8IndexLow Index of the lower two byte buffer.
 * @param u8IndexHigh Index of the upper two byte buffer.
 * @return The 32 bit value resulting from the two buffers.
 */
uint32_t PZEMModbusMaster::getTwoResponseBuffers(uint8_t u8IndexLow, uint8_t u8IndexHigh)
{
    uint32_t output;
    output = getResponseBuffer(u8IndexHigh);
    output <<= 16;
    output |= getResponseBuffer(u8IndexLow);
    return output;
}

/**
 * Reads all the stored power data from the PZEM-004T into the internal buffer.
 */
void PZEMModbusMaster::readPowerData()
{
    uint8_t result = readHoldingRegisters(0x0000, 10); // read all 10 registers from pzem

    if (result == ku8MBSuccess)
    {
        power.voltage_usage    = (getResponseBuffer(0x00) / 10.0f);
        power.current_usage    = (getTwoResponseBuffers(0x01, 0x02) / 1000.000f);
        power.active_power     = (getTwoResponseBuffers(0x03, 0x04) / 10.0f);
        power.active_energy    = (getTwoResponseBuffers(0x05, 0x06) / 1000.0f);
        power.frequency        = (getResponseBuffer(0x07) / 10.0f);
        power.power_factor     = (getResponseBuffer(0x08) / 100.0f);
        power.over_power_alarm = (getResponseBuffer(0x09));
        derivedData();
    }
}

/**
 * Loads the internal buffer with data derived from the PZEM-004T data.
 */
void PZEMModbusMaster::derivedData()
{
    power.apparent_power = power.voltage_usage * power.current_usage;
    power.reactive_power = sqrt(sq(power.apparent_power) - sq(power.active_power));
}