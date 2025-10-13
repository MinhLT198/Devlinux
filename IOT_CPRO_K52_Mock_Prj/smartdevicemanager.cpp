#include "smartdevicemanager.h"
#include "./ui_smartdevicemanager.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "devicemanager.h"
#include "adddevicedialog.h"


SmartDeviceManager::SmartDeviceManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartDeviceManager)
{
    ui->setupUi(this);
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,this,&SmartDeviceManager::on_DeviceSelected);
}

void SmartDeviceManager::updateDeviceList(const std::vector<std::unique_ptr<Device>>& list)
{
    ui->listWidget->clear();
    
    for(auto& device:list)
    {
        ui->listWidget->addItem(QString::fromStdString(device->getDevName()));
    }
}

SmartDeviceManager::~SmartDeviceManager()
{
    delete ui;
}


void SmartDeviceManager::on_btnAddDevice_clicked()
{

    addDeviceDialog diaglog(this);

    int result = diaglog.exec();

    if(result == QDialog::Accepted)
    {
        QString name = diaglog.getDeviceName();
        QString id = diaglog.getDeviceId();
        QString location = diaglog.getDeviceLocation();
        int type = diaglog.getDeviceType();

        // --- Kiểm tra ID có trùng hay không ---
        auto& devices = deviceManager::getInstance().getDevices();
        auto it = std::find_if(devices.begin(), devices.end(),
                               [&id](const std::unique_ptr<Device>& dev)
                               {
                                   return QString::fromStdString(dev->getDevId()) == id;
                               });
        if (it != devices.end())
        {
            // Nếu ID đã tồn tại, không thêm nữa
            ui->txtLogging->appendPlainText("[ERR] Thiết bị có ID " + id + " đã tồn tại, không thể thêm.");
            qDebug() << "Thiết bị có ID trùng, không thêm.";
            return;
        }

        // --- Nếu chưa tồn tại thì tạo mới ---
        auto device = DeviceFactory::createDevice(
            name.toStdString(),
            id.toStdString(),
            location.toStdString(),
            type);
        
        if(device)
        {
            deviceManager::getInstance().addDevice(std::move(device));
            updateDeviceList(deviceManager::getInstance().getDevices());
        }

        ui->txtLogging->appendPlainText("");
        ui->txtLogging->appendPlainText("[OK] Thêm thiết bị mới:");
        ui->txtLogging->appendPlainText("     Tên Thiết Bị: " + name);
        ui->txtLogging->appendPlainText("     ID Thiết Bị: " + id);
        ui->txtLogging->appendPlainText("     Vị Trí Thiết Bị: " + location);
        ui->txtLogging->appendPlainText("     Kiểu Thiết Bị: " + QString::number(type));
        qDebug() << "Dialog nhận OK";
        qDebug() << name;
        qDebug() << id;
        qDebug() << location;
        qDebug() << type;
    }
    else
    {
        qDebug() << "Dialog bị từ chối/đóng.";
    }
}


void SmartDeviceManager::on_btnRemoveDevice_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Remove Device",
                                  "Are you sure you want to remove this device?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int itemIdx = ui->listWidget->row(ui->listWidget->currentItem());
        auto deviceId = deviceManager::getInstance().getDevices().at(itemIdx)->getDevId();
        // Gọi hàm xóa thiết bị ở đây
        if(!deviceId.empty())
        {
            // clear danh sach thiet bi tranh th out_of_range khi remove thiet bi
            ui->listWidget->clear();
            ui->txtDevInfo->clear();

            deviceManager::getInstance().removeDevice(deviceId);
            updateDeviceList(deviceManager::getInstance().getDevices());
            ui->txtLogging->appendPlainText("");
            ui->txtLogging->appendPlainText("Xóa Thiết Bị Có ID: "+ QString::fromStdString(deviceId));
            qDebug() << "Remove Device ID: " << QString::fromStdString(deviceId);
        }
    } else {
        qDebug() << "User clicked No";
    }
}

void SmartDeviceManager::on_DeviceSelected()
{
    int itemIdx = ui->listWidget->row(ui->listWidget->currentItem());
    auto deviceName = deviceManager::getInstance().getDevices().at(itemIdx)->getDevName();
    auto deviceId = deviceManager::getInstance().getDevices().at(itemIdx)->getDevId();
    auto deviceLocation = deviceManager::getInstance().getDevices().at(itemIdx)->getDevLocation();
    auto deviceType = deviceManager::getInstance().getDevices().at(itemIdx)->getDevType();

    auto deviceValue = deviceManager::getInstance().getDevices().at(itemIdx)->getValue();

    // CLear Text Infor
    ui->txtDevInfo->clear();

    ui->txtDevInfo->appendPlainText("Tên Thiết Bị:      " + QString::fromStdString(deviceName));
    ui->txtDevInfo->appendPlainText("ID Thiết Bị:      " + QString::fromStdString(deviceId));
    ui->txtDevInfo->appendPlainText("Vị Trí Thiết Bị:      " + QString::fromStdString(deviceLocation));

    if(Device::TEMPERATURE_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Nhiệt Độ:      " + QString::number(deviceValue,'f',2) + " °C");
    }
    else if(Device::PRESSURE_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Áp Suất:      " + QString::number(deviceValue,'f',2) + " Bar");
    }
    else if(Device::HUMIDITY_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Độ Ẩm:      " + QString::number(deviceValue,'f',2) + " %%");
    }
    else if(Device::LIGHT_SWITCH == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Ligh State:      " );
    }
    else
    {
        ui->txtDevInfo->appendPlainText("================= Invalid Device Selected ================= ");
    }

    qDebug() << "Selected Item " << itemIdx << " --- " << QString::fromStdString(deviceName);
}

