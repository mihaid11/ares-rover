#pragma once
#include <WebServer.h>
#include "MotorControl.h"
#include "DistanceSensor.h"
#include "EnvironmentSensor.h"
#include "InertialSensor.h"
#include "PowerManager.h"

extern WebServer server;
extern const char* htmlPage;
extern MotorControl motor;
extern DistanceSensor front_dist;
extern DistanceSensor back_dist;
extern EnvironmentSensor dht;
extern InertialSensor mpu;
extern PowerManager ina;

void handleRoot();
void handleAction();
void handleDistance();
void handlePower();
void handleEnvironment();
void handleInertial();
