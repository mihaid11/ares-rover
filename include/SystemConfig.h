#pragma once

namespace hw_normal {
    constexpr int dht = 2000;
    constexpr int ina = 700;
    constexpr int display = 600;

    constexpr int dist_active = 80;
    constexpr int dist_passive = 500;
    constexpr int mpu_active = 25;
    constexpr int mpu_idle = 100;
}

namespace hw_eco {
    constexpr int dht = 60000;
    constexpr int ina = 3000;
    constexpr int display = 2000;

    constexpr int dist_active = 120;
    constexpr int dist_passive = 1000;
    constexpr int mpu_active = 50;
    constexpr int mpu_idle = 1000;
}

namespace web_normal {
    constexpr int dist = 200;
    constexpr int power = 700;
    constexpr int env = 2000;
    constexpr int imu = 500;
}

namespace web_eco {
    constexpr int dist = 500;
    constexpr int power = 3000;
    constexpr int env = 10000;
    constexpr int imu = 2000;
}
