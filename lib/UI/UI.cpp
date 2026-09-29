#include "UI.h"
#include <Arduino.h>
#include <esp32-hal-cpu.h>

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleAction() {
    String dir = server.arg("dir");
    int spd = server.arg("speed").toInt();

    motor.setCommand(dir[0], spd);
    updateDynamicIntervals();

    server.send(200, "text/plain", "OK");
}

void handleDistance() {
    String front = (front_dist.getDistance() <= 0.0) ? "---" : String(front_dist.getDistance(), 1);
    String back = (back_dist.getDistance() <= 0.0) ? "---" : String(back_dist.getDistance(), 1);

    String json = "{";
    json += "\"f\":\"" + front + "\",";
    json += "\"b\":\"" + back + "\"";
    json += "}";

    server.send(200, "application/json", json);
}

void handlePower() {
    String json = "{";

    json += "\"v\":" + String(ina.getVoltage(), 2) + ",";
    json += "\"c\":" + String(ina.getCurrent(), 0) + ",";
    json += "\"p\":" + String(ina.getPower(), 0) + ",";
    json += "\"b\":" + String(ina.getBatteryPercentage());
    json += "}";

    server.send(200, "application/json", json);
}

void handleEnvironment() {
    String json = "{";

    json += "\"t\":" + String(dht.getTemperature(), 1) + ",";
    json += "\"h\":" + String(dht.getHumidity(), 1);
    json += "}";

    server.send(200, "application/json", json);
}

void handleInertial() {
    String json = "{";

    json += "\"ax\":" + String(mpu.getAccelerationX(), 2) + ",";
    json += "\"ay\":" + String(mpu.getAccelerationY(), 2) + ",";
    json += "\"az\":" + String(mpu.getAccelerationZ(), 2) + ",";
    json += "\"gx\":" + String(mpu.getGyroX(), 2) + ",";
    json += "\"gy\":" + String(mpu.getGyroY(), 2) + ",";
    json += "\"gz\":" + String(mpu.getGyroZ(), 2);
    json += "}";

    server.send(200, "application/json", json);
}

void handleEco() {
    bool state = server.arg("state") == "1";
    eco_mode = state;

    if (eco_mode) {
        WiFi.setTxPower(WIFI_POWER_8_5dBm);

        dht_interval = 60000;
        ina_interval = 3000;
        display_interval = 2000;

        display.setBacklight(false);
    } else {
        WiFi.setTxPower(WIFI_POWER_19dBm);

        dht_interval = 2000;
        ina_interval = 700;
        display_interval = 600;

        display.setBacklight(true);
    }

    updateDynamicIntervals();

    server.send(200, "text/plain", "OK");
}

void updateDynamicIntervals() {
    char c = motor.getCurrentCommand();

    if (eco_mode) {
        if (c == 'F') {
            front_interval = 120;
            back_interval = 1000;
            mpu_interval = 50;
        } else if (c == 'B') {
            front_interval = 1000;
            back_interval = 120;
            mpu_interval = 50;
        } else {
            front_interval = 1000;
            back_interval = 1000;
            mpu_interval = 1000;
        }
    } else {
        if (c == 'F') {
            front_interval = 80;
            back_interval = 500;
            mpu_interval = 25;
        } else if (c == 'B') {
            front_interval = 500;
            back_interval = 80;
            mpu_interval = 25;
        } else {
            front_interval = 500;
            back_interval = 500;
            mpu_interval = 100;
        }
    }
}
