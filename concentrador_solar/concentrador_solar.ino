#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SPI.h>
#include <SD.h>

Adafruit_INA219 SolarConcentrator(0x40);
Adafruit_INA219 SolarPanel(0x41); 

File dataFile;
const int chip_select = 5;

unsigned long previous_millis = 0;
unsigned long current_millis = 0;
const long interval = 500;

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
  SolarConcentrator.setCalibration_16V_400mA();
  SolarPanel.setCalibration_16V_400mA();

  SD.begin(chip_select);
  dataFile = SD.open("data.csv", FILE_WRITE);
  delay(1000);
  dataFile.println("Timer[ms],ShuntVoltagePV[mV],BusVoltagePV[V],CurrentPV[mA],PowerPV[mW],LoadVoltagePV[V],ShuntVoltageSC[mV],BusVoltageSC[V],CurrentSC[mA],PowerSC[mW],LoadVoltageSC[V]");
  dataFile.close();
  delay(1000);
}

void loop() {
  current_millis = millis();

  if(current_millis - previous_millis >= interval)
  {
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

    dataFile = SD.open("data.csv", FILE_WRITE);

    dataFile.print(current_millis);
    dataFile.print(",");
    dataFile.print(shunt_voltage_panel);
    dataFile.print(",");
    dataFile.print(bus_voltage_panel);
    dataFile.print(",");
    dataFile.print(current_mA_panel);
    dataFile.print(",");
    dataFile.print(power_panel);
    dataFile.print(",");
    dataFile.print(load_voltage_panel);
    dataFile.print(",");
    dataFile.print(shunt_voltage_concentrator);
    dataFile.print(",");
    dataFile.print(bus_voltage_concentrator);
    dataFile.print(",");
    dataFile.print(current_mA_concentrator);
    dataFile.print(",");
    dataFile.print(power_concentrator);
    dataFile.print(",");
    dataFile.println(load_voltage_concentrator);

    dataFile.close();

    previous_millis = current_millis;
  }
}
