#include "lib/DriverStation.h"
#include "lib/drivebase.h"

static ElegooCar *robot = new ElegooCar();
static DriverStation *ds = new DriverStation();

static constexpr uint8_t deadzone = 16;

void setup() {
    Serial.begin(115200);
    Drivebase::init(robot);
    Drivebase::setDeadzone(deadzone);
}

void autonomous() {}

void teleop() {
    // this gets called every time the robot receives data
    // from the driver station in teleop mode,
    // which should happen 10 times per second
    Drivebase::arcadeDrive(ds->getLY(), ds->getLX());
}

void loop() {
    // update the DriverStation class - this will check if there is new data
    // from the DriverStation application. ds.bUpdate() returns true if new data
    // has been received (10 times/second)
    if (ds->bUpdate()) {
        // now, handle the driver station data
        // depending on what game state we are in
        switch (ds->getGameState()) {
        case ePreGame:
        case ePostGame:
            // During Pre and Post game, the robot should not move
            Drivebase::stop();
            break;
        case eAutonomous:
            // Handle autonomous mode
            autonomous();
            break;
        case eTeleop:
            // Handle telop mode
            teleop();
            break;
        }
    }
}