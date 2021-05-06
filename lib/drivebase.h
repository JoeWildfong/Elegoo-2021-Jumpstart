#pragma once

/************************
 * Joe's Drivebase Library
 * This library is designed to provide an easy way to control the robot.
 * It's similar to WPILib's drive functions, which are used on FRC robots.
 *
 * Usage:
 * You need to create an ElegooCar object before using this.
 * Then, you need to pass a pointer to it into the init function.
 * You can find an example of this in main.ino. (lines 4 and 11)
 * 
 * There are two main functions you can use to drive the robot.
 * Both take two integer values between -255 and 255.
 * In both functions, the robot will keep going until you tell it to stop.
 * You can use the stop() function for this.
 *
 * tankDrive moves the robot according to a given speed for each side.
 * You can specify a speed for the left and right sides of the robot.
 * This means a full-speed left turn is tankDrive(-255, 255);
 * (full speed backwards on the left, full speed forwards on the right)
 * This function is... honestly not that useful.
 * I use arcadeDrive for pretty much everything.
 *
 * arcadeDrive moves the robot based on forward/backward and left/right speeds.
 * Full speed straght forwards is arcadeDrive(255, 0);
 * A full-speed left turn is arcadeDrive(0, -255);
 * This function is ideal for mapping a joystick or a controller's analog stick.
 *
 * stop() stops the robot. Simple as that.
 * It's the same as tankDrive(0, 0) and arcadeDrive(0, 0).
 * There really isn't much of a reason for this to exist.
 *
 * Setting a deadzone:
 * You can set a deadzone on the drivebase with the setDeadzone function.
 * Any motor output smaller than the deadzone will instead output 0.
 * You cannot set a negative deadzone - only inputs between 0 and 255 will work.
 * Anything outside this range might not behave as expected.
 *
 ***********************/

#include "elegoo-car.h"

/// Namespace containing functions to control drive motors.
namespace Drivebase {

    /// Sets pin modes and initializes the Drivebase library.
    void init(ElegooCar *car);

    /// Sets a deadzone for the drivebase.
    void setDeadzone(uint8_t deadzone);

    /// Sets motors on each side of the robot to given values between -255 and 255.
    /// Negative values move backwards.
    /// Values outside the range of -255 to 255 will be clamped.
    /// Robot will not automatically stop.
    void tankDrive(int16_t left, int16_t right);

    /// Sets motors based on x and y coordinates between -255 and 255.
    /// Positive y is forwards, positive x is a right turn.
    /// Values outside the range of -255 to 255 will be clamped.
    /// Robot will not automatically stop.
    void arcadeDrive(int16_t y, int16_t x);

    /// Stops the robot. Equivalent to TankDrive(0, 0) or ArcadeDrive(0, 0).
    void stop();

} // namespace Drivebase