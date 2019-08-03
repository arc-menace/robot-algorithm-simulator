#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

//Error Messages:
#define ERROR_WRONG_VAL "ERROR: Value either too large or too small"
#define ERROR_INVALID_INPUT "ERROR: Invalid input"

//Global Constants:
#define DEFAULT_BOARD_SIZE 96.0
#define DEFAULT_ROBOT_X 48.0
#define DEFAULT_ROBOT_Y 48.0
#define MAX_ROBOT_WIDTH 12.0
#define MAX_ROBOT_LENGTH 12.0
#define DEFAULT_START_ORIENTATION 90.0
#define MAX_SENSE_DIST 135.77
#define MIN_SENSE_DIST 0.1
#define DEFAULT_SENSE_ANGLE 360.0
#define DEFAULT_WHEEL_DIAM 0.0
#define MAX_WHEEL_DIAM 6.0
#define DEFAULT_OBSTACLE_RADIUS 0.75
#define MARGIN_OF_ERROR 1
#define DEFAULT_MECHANUM false
#define PI 3.14159265358979323846264338327
const double convert_deg = 0.0174532925;

#endif