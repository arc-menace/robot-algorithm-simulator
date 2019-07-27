#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

//Error Messages:
#define ERROR_VAL_TOO_LARGE "ERROR: Value too large."
#define ERROR_INVALID_INPUT "ERROR: Invalid input"

//Global Constants:
#define DEFAULT_BOARD_SIZE 96.0
#define DEFAULT_ROBOT_X 48.0
#define DEFAULT_ROBOT_Y 48.0
#define DEFAULT_ROBOT_WIDTH 12.0
#define DEFAULT_ROBOT_LENGTH 12.0
#define DEFAULT_START_ORIENTATION 90.0
#define MAX_SENSE_DIST 135.77
#define MIN_SENSE_DIST 0.1
#define MAX_WHEEL_DIAM 6.0
#define DEFAULT_OBSTACLE_RADIUS 0.75
#define MARGIN_OF_ERROR 0.000001
const double convert_deg = 0.0174532925;

#endif