#include "devicemanager.h"

std::unique_ptr<deviceManager> deviceManager::instance = nullptr;

// deviceManager Constructor
deviceManager::deviceManager() {
    qDebug() << "deviceManager Constructor Called";
}

// static method to create/get instance
deviceManager& deviceManager::getInstance()
{
    if(nullptr == instance)
    {
        instance = std::unique_ptr<deviceManager>(new deviceManager());
    }

    return *instance;
}

void deviceManager::addDevice(std::unique_ptr<Device> dev)
{
    devices.push_back(std::move(dev));
}

void deviceManager::removeDevice(const std::string id)
{
    // Tìm thiết bị với ID tương ứng và xóa thiết bị khỏi vector không gây lỗi out_of_range
    auto it = std::find_if(devices.begin(), devices.end(),
                             [&id](const std::unique_ptr<Device>& device) {
                                 return device->getDevId() == id;
                             });
    if (it != devices.end()) {
        devices.erase(it);
    } else {
        qDebug() << "Device with ID " << QString::fromStdString(id) << " not found.";
    }
}


const std::vector<std::unique_ptr<Device>>& deviceManager::getDevices()
{
    return devices;
}


