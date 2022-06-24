/*
 * File: PZEMModbusMaster.h
 * Project: src
 * File Created: Saturday, 18th June 2022 5:36:59 pm
 * Author: Daniel Cormier (git@drc97.com)
 * -----
 * Last Modified: Friday, 24th June 2022 8:24:44 am
 * Modified By: Daniel Cormier (git@drc97.com)
 * -----
 * Copyright 2022 Daniel Cormier
 */

#include "ModbusMaster.h"

typedef struct
{
    // V, resolution of 0.1V
    double voltage_usage;
    // A, resolution of 0.001A
    double current_usage;
    // W, resolution of 0.1W
    double active_power;
    // kWh, resolution of 0.001kWh
    double active_energy;
    // Hz, resolution of 0.1Hz
    double frequency;
    // Unitless, resolution of 0.01
    double power_factor;
    // VA, resolution of 0.1VA
    double apparent_power;
    // VAR, resolution of 0.1VAR
    double reactive_power;
    double phase_angle;
    // True if the active power is above the set power alarm value
    bool over_power_alarm;

} power_data;

class PZEMModbusMaster : public ModbusMaster
{
  public:
    PZEMModbusMaster();
    uint32_t getTwoResponseBuffers(uint8_t u8IndexLow, uint8_t u8IndexHigh);
    void readPowerData();
    power_data power;

  private:
    void derivedData();
};
