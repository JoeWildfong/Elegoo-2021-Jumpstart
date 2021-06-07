#include "lib/encoders.h"

#include <avr/interrupt.h>

#define leftPin PIN_A1
#define rightPin PIN_A0

#if leftPin <= 7
#define leftPinPort 2
#elif leftPin <= 13
#define leftPinPort 0
#else
#define leftPinPort 1
#endif

#if rightPin <= 7
#define rightPinPort 2
#elif rightPin <= 13
#define rightPinPort 0
#else
#define rightPinPort 1
#endif

static constexpr uint8_t leftPCICRbit = digitalPinToPCICRbit(leftPin);
static constexpr uint8_t rightPCICRbit = digitalPinToPCICRbit(rightPin);

static constexpr uint8_t leftPCMSKbit = digitalPinToPCMSKbit(leftPin);
static constexpr uint8_t rightPCMSKbit = digitalPinToPCMSKbit(rightPin);

static volatile uint16_t leftTicks;
static volatile uint16_t rightTicks;

static uint8_t prevPinStates = 0;

#if rightPinPort != leftPinPort
static uint8_t prevPinStates2 = 0;
#endif

void Encoders::init() {
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);

    leftTicks = 0;
    rightTicks = 0;

    // enable pin change interrupts for relevant ports
    constexpr uint8_t PCICR_MASK = bit(leftPCICRbit) | bit(rightPCICRbit);
    PCICR |= PCICR_MASK;

    // set interrupt masks to allow left and right pins
    *digitalPinToPCMSK(leftPin) |= bit(leftPCMSKbit);
    *digitalPinToPCMSK(rightPin) |= bit(rightPCMSKbit);
}

uint16_t Encoders::getLeftTicks() {
    // disable interrupts
    cli();

    const uint16_t out = leftTicks;

    // re-enable interrupts
    sei();
    return out;
}

uint16_t Encoders::getRightTicks() {
    // disable interrupts
    cli();

    const uint16_t out = rightTicks;

    // re-enable interrupt
    sei();
    return out;
}

#if leftPinPort == 0
ISR(PCINT0_vect) {
    const uint8_t pinChanges = PINB ^ prevPinStates;
#elif leftPinPort == 1
ISR(PCINT1_vect) {
    const uint8_t pinChanges = PINC ^ prevPinStates;
#else
ISR(PCINT2_vect) {
    const uint8_t pinChanges = PIND ^ prevPinStates;
#endif

    if (pinChanges & bit(leftPCMSKbit)) {
        leftTicks++;
    }

#if rightPinPort == leftPinPort
    if (pinChanges & bit(rightPCMSKbit)) {
        rightTicks++;
    }
#endif

    prevPinStates ^= pinChanges;
}

#if rightPinPort != leftPinPort
#if rightPinPort == 0
ISR(PCINT0_vect) {
    const uint8_t pinChanges = PINB ^ prevPinStates2;
#elif rightPinPort == 1
ISR(PCINT1_vect) {
    const uint8_t pinChanges = PINC ^ prevPinStates2;
#else
ISR(PCINT2_vect) {
    const uint8_t pinChanges = PIND ^ prevPinStates2;
#endif

    if (pinChanges & bit(rightPCMSKbit)) {
        Encoders::rightTicks++;
    }

    prevPinStates2 ^= pinChanges;
}
#endif