/*
 * File: main.cpp
 * Project: src
 * File Created: Saturday, 18th June 2022 10:50:19 am
 * Author: Daniel Cormier
 * -----
 * Last Modified: Friday, 24th June 2022 8:54:51 am
 * Modified By: Daniel Cormier
 * -----
 * Copyright 2022 Daniel Cormier
 */

#include "ModbusMaster.h"
#include "PZEMModbusMaster.h"
#include <Arduino.h>

power_data power;

PZEMModbusMaster node;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200); // USB serial port
    Serial1.begin(9600);  // UART serial port for PZEM
    node.begin(1, Serial1);
}

void loop()
{
    // put your main code here, to run repeatedly:
    node.readPowerData();
    delay(1000);
}