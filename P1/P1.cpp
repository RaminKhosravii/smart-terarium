#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

using namespace std;

// کلاس Device به عنوان کلاس پایه
class Device {
protected:
    string deviceId; // Device ID (شناسه دستکاه)
    string status;    // وضعیت دستگاه

public:
    // سازنده کلاس Device که شناسه و وضعیت اولیه را می‌گیرد
    Device(const string& id, const string& initialStatus)
        : deviceId(id), status(initialStatus) {}

    // ویرایشگر مجازی برای پاک‌سازی منابع
    virtual ~Device() {}

    // متد برای دریافت وضعیت دستگاه
    string getStatus() const { return status; }

    // متد برای دریافت شناسه دستگاه
    string getId() const { return deviceId; }

    // متد مجازی خالص برای کنترل دستگاه، باید در زیرکلاس‌ها پیاده‌سازی شود
    virtual void controlDevice(const string& newStatus) = 0;
};

// کلاس SensorDevice که از Device ارث می‌برد
class SensorDevice : public Device {
public:
    // سازنده برای SensorDevice
    SensorDevice(const string& id, const string& initialStatus)
        : Device(id, initialStatus) {}

    // پیاده‌سازی متد کنترل دستگاه برای SensorDevice
    void controlDevice(const string& newStatus) override {
        status = newStatus; // تغییر وضعیت دستگاه
        cout << "SensorDevice " << deviceId << " status changed to " << status << endl;
    }
};

// کلاس MotorDevice که از Device ارث می‌برد
class MotorDevice : public Device {
public:
    // سازنده برای MotorDevice
    MotorDevice(const string& id, const string& initialStatus)
        : Device(id, initialStatus) {}

    // پیاده‌سازی متد کنترل دستگاه برای MotorDevice
    void controlDevice(const string& newStatus) override {
        status = newStatus; // تغییر وضعیت دستگاه
        cout << "MotorDevice " << deviceId << " status changed to " << status << endl;
    }
};

// کلاس RelayDevice که از Device ارث می‌برد
class RelayDevice : public Device {
public:
    // سازنده برای RelayDevice
    RelayDevice(const string& id, const string& initialStatus)
        : Device(id, initialStatus) {}

    // پیاده‌سازی متد کنترل دستگاه برای RelayDevice
    void controlDevice(const string& newStatus) override {
        status = newStatus; // تغییر وضعیت دستگاه
        cout << "RelayDevice " << deviceId << " status changed to " << status << endl;
    }
};

// کلاس DeviceManager برای مدیریت دستگاه‌ها
class DeviceManager {
private:
    // نقشه‌ای برای نگه‌داشتن دستگاه‌ها با شناسه دستگاه به عنوان کلید
    unordered_map < string, unique_ptr<Device>> devices;

public:
    // متد برای ساخت یک دستگاه جدید
    void createDevice(const string& deviceType, const string& deviceId, const string& initialStatus) {
        // بررسی نوع دستگاه و ساخت آن
        if (deviceType == "sensor") {
            devices[deviceId] = make_unique<SensorDevice>(deviceId, initialStatus); // ساخت دستگاه حسگر
        }
        else if (deviceType == "motor") {
            devices[deviceId] = make_unique<MotorDevice>(deviceId, initialStatus); // ساخت دستگاه موتور
        }
        else if (deviceType == "relay") {
            devices[deviceId] = make_unique<RelayDevice>(deviceId, initialStatus); // ساخت دستگاه رله
        }
        else {
            cout << "Device type not recognized." << endl; // خطا در نوع دستگاه
        }
    }

    // متد برای کنترل یک دستگاه با شناسه مشخص
    void controlDevice(const std::string& deviceId, const string& newStatus) {
        // بررسی وجود دستگاه در نقشه
        if (devices.find(deviceId) != devices.end()) {
            devices[deviceId]->controlDevice(newStatus); // صدا زدن متد کنترل دستگاه
        }
        else {
            cout << "Device not found." << endl; // دستگاه پیدا نشد
        }
    }

    // متد برای گرفتن وضعیت یک دستگاه خاص
    string getStatus(const string& deviceId) {
        // بررسی وجود دستگاه در نقشه
        if (devices.find(deviceId) != devices.end()) {
            return devices[deviceId]->getStatus(); // برگرداندن وضعیت دستگاه
        }
        else {
            return "Device not found."; // خطا در پیدا نکردن دستگاه
        }
    }

    // متد برای نمایش وضعیت همه دستگاه‌ها
    void displayAllStatuses() {
        cout << "Device Statuses:" << endl; // عنوان خروجی
        for (const auto& pair : devices) {
            // حلقه برای نمایش وضعیت تمامی دستگاه‌ها
            cout << "Device ID: " << pair.second->getId() << ", Status: " << pair.second->getStatus() << endl;
        }
    }
};

// TODO: متد برای ارتباط با دستگاه‌های خارجی
void communicateWithExternalDevice(const string& deviceId) {
    // کد های مربوط بخ ارتباط با دستگاه های خارجی
    // برای مثال:
    // - ایجاد یا استفاده از یک API HTTP برای تعامل با دستگاه خارجی
    // - استفاده از پروتکل‌های مانند MQTT یا WebSocket
    // - ارسال و دریافت اطلاعات از دستگاه‌ها
    // - بررسی پاسخ‌ها و اطمینان از اینکه دستگاه به درستی پاسخ می‌دهد
};

// تابع برای منو و تعامل با کاربر
void showMenu(DeviceManager& manager) {
    while (true) { // حلقه بی‌پایان برای منو
        cout << "\nMenu:\n";
        cout << "1. Create Device\n";
        cout << "2. Control Device\n";
        cout << "3. Get Device Status\n";
        cout << "4. Display All Device Statuses\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";

        int choice; // متغیر برای ذخیره انتخاب کاربر
        cin >> choice; // دریافت ورودی از کاربر

        if (choice == 1) { 
            string deviceType, deviceId, initialStatus; // متغیرها برای نوع دستگاه، شناسه و وضعیت
            cout << "Enter device type (sensor/motor/relay): ";
            cin >> deviceType;
            cout << "Enter device ID: ";
            cin >> deviceId; // دریافت شناسه دستگاه
            cout << "Enter initial status: ";
            cin >> initialStatus; // دریافت وضعیت اولیه
            manager.createDevice(deviceType, deviceId, initialStatus); // ساخت دستگاه در DeviceManager
        }
        else if (choice == 2) { // اگر گزینه ۲ انتخاب شد
            string deviceId, newStatus; // متغیرها برای شناسه و وضعیت جدید
            cout << "Enter device ID: ";
            cin >> deviceId; // دریافت شناسه دستگاه
            cout << "Enter new status: ";
            cin >> newStatus; // دریافت وضعیت جدید
            manager.controlDevice(deviceId, newStatus); // کنترل دستگاه با وضعیت جدید
        }
        else if (choice == 3) { // اگر گزینه ۳ انتخاب شد
            string deviceId; // متغیر برای شناسه دستگاه
            cout << "Enter device ID: ";
            cin >> deviceId; // دریافت شناسه دستگاه
            string status = manager.getStatus(deviceId); // دریافت وضعیت دستگاه
            cout << "Status of device " << deviceId << ": " << status << endl; // نمایش وضعیت دستگاه
        }
        else if (choice == 4) { // اگر گزینه ۴ انتخاب شد
            manager.displayAllStatuses(); // نمایش وضعیت تمام دستگاه‌ها
        }
        else if (choice == 5) { // اگر گزینه ۵ انتخاب شد
            break; // خروج از حلقه و پایان برنامه
        }
        else {
            cout << "Invalid choice, please try again." << endl; // اگر ورودی نامعتبر باشد
        }
    }
}

// تست برنامه
int main() {
    DeviceManager deviceManager; // ساخت یک شیء از کلاس DeviceManager
    showMenu(deviceManager); // نمایش منو و شروع تعامل با کاربر
    return 0; // پایان برنامه
}