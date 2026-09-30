#include "UI.h"
#include <Arduino.h>

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleConfig() {
    char json[256];
    snprintf(json, sizeof(json),
        "{\"normal\":{\"dist\":%d,\"pow\":%d,\"env\":%d,\"imu\":%d},"
        "\"eco\":{\"dist\":%d,\"pow\":%d,\"env\":%d,\"imu\":%d}}",
        web_normal::dist, web_normal::power, web_normal::env, web_normal::imu,
        web_eco::dist, web_eco::power, web_eco::env, web_eco::imu
    );
    server.send(200, "application/json", json);
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

        dht_interval = hw_eco::dht;
        ina_interval = hw_eco::ina;
        display_interval = hw_eco::display;

        display.setBacklight(false);
    } else {
        WiFi.setTxPower(WIFI_POWER_19dBm);

        dht_interval = hw_normal::dht;
        ina_interval = hw_normal::ina;
        display_interval = hw_normal::display;

        display.setBacklight(true);
    }

    updateDynamicIntervals();

    server.send(200, "text/plain", "OK");
}

void updateDynamicIntervals() {
    char c = motor.getCurrentCommand();

    if (eco_mode) {
        if (c == 'F') {
            front_interval = hw_eco::dist_active;
            back_interval = hw_eco::dist_passive;
            mpu_interval = hw_eco::mpu_active;
        } else if (c == 'B') {
            front_interval = hw_eco::dist_passive;
            back_interval = hw_eco::dist_active;
            mpu_interval = hw_eco::mpu_active;
        } else {
            front_interval = hw_eco::dist_passive;
            back_interval = hw_eco::dist_passive;
            mpu_interval = hw_eco::mpu_idle;
        }
    } else {
        if (c == 'F') {
            front_interval = hw_normal::dist_active;
            back_interval = hw_normal::dist_passive;
            mpu_interval = hw_normal::mpu_active;
        } else if (c == 'B') {
            front_interval = hw_normal::dist_passive;
            back_interval = hw_normal::dist_active;
            mpu_interval = hw_normal::mpu_active;
        } else {
            front_interval = hw_normal::dist_passive;
            back_interval = hw_normal::dist_passive;
            mpu_interval = hw_normal::mpu_idle;
        }
    }
}
