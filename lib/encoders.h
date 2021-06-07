#pragma once

#include <Arduino.h>

namespace Encoders {

/**
 * Initiate the encoder library, setting pin modes and interrupts.
 */
void init();

/**
 * Gets the number of times the left encoder has ticked.
 * @return The number of left encoder ticks since init was called.
 */
uint16_t getLeftTicks();

/**
 * Gets the number of times the right encoder has ticked.
 * @return The number of right encoder ticks since init was called.
 */
uint16_t getRightTicks();

} // namespace Encoders