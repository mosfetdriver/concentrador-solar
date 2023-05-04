#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SPI.h>
#include <SD.h>

Adafruit_INA219 SolarConcentrator(0x40);
Adafruit_INA219 SolarPanel(0x41); 

const int chip_select = 5;

float shunt_voltage_panel = 0.0;
float bus_voltage_panel   = 0.0;
float current_mA_panel    = 0.0;
float load_voltage_panel  = 0.0;
float power_panel         = 0.0;

float shunt_voltage_concentrator = 0.0;
float bus_voltage_concentrator   = 0.0;
float current_mA_concentrator    = 0.0;
float load_voltage_concentrator  = 0.0;
float power_concentrator         = 0.0;

void setup() {
  Serial.begin(115200);
  SolarConcentrator.begin();
  SolarPanel.begin();
  SD.begin(chip_select);
}

void loop() {
  shunt_voltage_panel = SolarPanel.getShuntVoltage_mV();
  bus_voltage_panel   = SolarPanel.getBusVoltage_V();
  current_mA_panel    = SolarPanel.getCurrent_mA();
  power_panel         = SolarPanel.getPower_mW();
  load_voltage_panel  = bus_voltage_panel + shunt_voltage_panel * 0.001;

  shunt_voltage_concentrator = SolarConcentrator.getShuntVoltage_mV();
  bus_voltage_concentrator   = SolarConcentrator.getBusVoltage_V();
  current_mA_concentrator    = SolarConcentrator.getCurrent_mA();
  power_concentrator         = SolarConcentrator.getPower_mW();
  load_voltage_concentrator  = bus_voltage_concentrator + shunt_voltage_concentrator * 0.001;
}
