#pragma once
#include <WebServer.h>
#include "../../include/SystemConfig.h"
#include "MotorControl.h"
#include "DistanceSensor.h"
#include "EnvironmentSensor.h"
#include "InertialSensor.h"
#include "DisplayManager.h"
#include "PowerManager.h"

extern WebServer server;
extern const char* htmlPage;
extern MotorControl motor;
extern DistanceSensor front_dist;
extern DistanceSensor back_dist;
extern EnvironmentSensor dht;
extern InertialSensor mpu;
extern PowerManager ina;
extern DisplayManager display;
extern bool eco_mode;
extern int dht_interval;
extern int ina_interval;
extern int display_interval;
extern int front_interval;
extern int back_interval;
extern int mpu_interval;

void handleRoot();
void handleConfig();
void handleAction();
void handleDistance();
void handlePower();
void handleEnvironment();
void handleInertial();
void handleEco();

void updateDynamicIntervals();
