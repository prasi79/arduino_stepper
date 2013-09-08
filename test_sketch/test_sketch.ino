#include <MultiStepper.h>

int steps_per_rev = 200 * 32;
byte motor_count = 3;

//3 Motors on PORTA and no limit switches
//MultiStepper stepper_controller(&PORTA, &DDRA, motor_counte, steps_per_rev);

//3 Motors on PORTA and 3 limit switches on PORTC
MultiStepper stepper_controller(&PORTA, &DDRA, motor_count, &PINC, &DDRC, steps_per_rev);

void setup() {
  stepper_controller.setPrinter(Serial);
  stepper_controller.setSpeed();
  Serial.begin(9600);
}

void osscilate(long speed) {
  stepper_controller.setSpeed(speed);
  while (true) {
    long start_time = millis();
    stepper_controller.move(
      steps_per_rev,
      .5*steps_per_rev,
      steps_per_rev
    );
    Serial.println(millis() - start_time);
    start_time = millis();
    stepper_controller.move(
      -1 * steps_per_rev,
      -.5 * steps_per_rev,
      -1 * steps_per_rev
    );
    Serial.println(millis() - start_time);
  }
}

void two_steps_forward_one_step_backwards(){
  while (true) {
    stepper_controller.move(
      2 * steps_per_rev,
      2 * steps_per_rev,
      2 * steps_per_rev
    );

    stepper_controller.move(
      -1 * steps_per_rev,
      -1 * steps_per_rev,
      -1 * steps_per_rev
    );
  }

}

void rectangle(long width, long height){
  stepper_controller.move(width, height);
  stepper_controller.move(-width);
  stepper_controller.move(0, -height);
  stepper_controller.move(width);
  stepper_controller.move(0, height);
  stepper_controller.move(0, -height);
  stepper_controller.move(-width, -height);
  while (true) {};
}

void loop() {
  rectangle(30000L, 15000L);
//  osscilate(6);
}

