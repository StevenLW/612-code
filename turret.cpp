#include "turret.h"
#include "vision_alt.h"
#include "ports.h"

#include <PIDController.h>
#include <Counter.h>
#if DEBUG_612
#include <SmartDashboard/SendablePIDController.h>
#include <SmartDashboard/SmartDashboard.h>
#endif

#include "612.h"
#include "ports.h"
#include "two_jags.h"
#include "shooter.h"

#include <cstdlib>

turret::turret(Jaguar& rotate, Jaguar& winch, Jaguar& launcha, Jaguar& launchb, Counter& count) {
    rotation_jag = &rotate;
    winch_jag = &winch;

    shooter_wheels = new shooter(count, launcha, launchb);

    cur_target = NULL;
}

turret::~turret() {
    delete shooter_wheels;
}

void turret::align(target& t) {
    cur_target = &t;
}
void turret::align(target& t, int distance = vision_processing::target_distance_from_center(t)) {
    if (distance < ZERO_MIN) {
        turn(RIGHT);
    }
    else if (distance > ZERO_MAX) {
        turn(LEFT);
    }
    else {
        rotation_jag.Set(0.0);
    }
}

void turret:turn(DIRECTION direction) {
    if(direction == LEFT) {
        rotation_jag.Set(TURN_SPEED);
    }
    else { // RIGHT is implied (not assumed)
        rotation_jag.Set(-TURN_SPEED);
    }
}

//turret robot_turret(turret_rotation_jag, turret_winch_jag, left_launcher_jag, right_launcher_jag
