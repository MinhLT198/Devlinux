#include "device.h"

// variables for randoom generation
bool Device::isGenSeed = false;
std::default_random_engine Device::gen;
std::uniform_real_distribution<double> Device::distribution{0.0, 100.0};


// Device Class Implementation
Device::Device(std::string name, std::string id, std::string location): _devName(name), _devId(id), _devLocation(location){
    if(!isGenSeed)
    {
        srand(time(0));
        isGenSeed = true;
        qDebug() << "Gen Seed for first time call Device Constructor";
    }
    qDebug() << "Device Constructor Called";
};

const std::string Device::getDevName()
{
    return _devName;
}

const std::string Device::getDevId()
{
    return _devId;
}

const std::string Device::getDevLocation()
{
    return _devLocation;
}

// TemperatureSensor Class Implementation
TemperatureSensor::TemperatureSensor(std::string name, std::string id, std::string location):Device(name,id,location) {
    qDebug() << "TemperatureSensor Constructor Called";
}


const int TemperatureSensor::getDevType() {
    return Device::TEMPERATURE_SENSOR;
}

const float TemperatureSensor::getValue() {
    return distribution(gen);
}


// PressureSensor Class Implementation
PressureSensor::PressureSensor(std::string name, std::string id, std::string location):Device(name,id,location) {
    qDebug() << "PressureSensor Constructor Called";
}

const int PressureSensor::getDevType() {
    return Device::PRESSURE_SENSOR;
}

const float PressureSensor::getValue() {
    return distribution(gen);
}


// HimiditySensor Class Implementation
HumiditySensor::HumiditySensor(std::string name, std::string id, std::string location):Device(name,id,location) {
    qDebug() << "HumiditySensor Constructor Called";
}

const int HumiditySensor::getDevType() {
    return Device::HUMIDITY_SENSOR;
}

const float HumiditySensor::getValue() {
    return distribution(gen);
}


// LightSwitch Class Implementation
LightSwitch::LightSwitch(std::string name, std::string id, std::string location):Device(name,id,location) {
    qDebug() << "LightSwitch Constructor Called";
}

const int LightSwitch::getDevType() {
    return Device::LIGHT_SWITCH;
}

const float LightSwitch::getValue() {
    return distribution(gen);
}

// DeviceFactory Implementation
std::unique_ptr<Device> DeviceFactory::createDevice(std::string name,std::string id, std::string location, int type)
{
    switch(type)
    {
    case Device::TEMPERATURE_SENSOR:
        return std::make_unique<TemperatureSensor>(name,id,location);
        break;
    case Device::PRESSURE_SENSOR:
        return std::make_unique<PressureSensor>(name,id,location);
        break;
    case Device::HUMIDITY_SENSOR:
        return std::make_unique<HumiditySensor>(name,id,location);
        break;
    case Device::LIGHT_SWITCH:
        return std::make_unique<LightSwitch>(name,id,location);
        break;
    default:
        qDebug() << "Invalid Device Type";
        return nullptr;
    }

    return nullptr;
}
