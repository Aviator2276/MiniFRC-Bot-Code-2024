#include <PestoLink-Receive.h>
#include <Alfredo_NoU2.h>

NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(3);
NoU_Motor rearLeftMotor(2);
NoU_Motor rearRightMotor(4);
//NoU_Servo servo(1);

NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

void setup() {
	PestoLink.begin("TEST BOT");

    frontLeftMotor.setInverted(false);
    frontRightMotor.setInverted(false);
    rearLeftMotor.setInverted(true);
    rearRightMotor.setInverted(false);

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
	// Here we define the variables we use in the loop
    float throttle = 0;
    float rotation = 0;
    float servoAngle = 0;

	//When PestoLink.update() is called, it returns "true" only if the robot is connected to phone/laptop  
    if (PestoLink.update()) {
        
        if (PestoLink.keyHeld(Key::W)) {
            throttle = 1;
        }
        else if (PestoLink.keyHeld(Key::S)) {
            throttle = -1;
        } 
        if (PestoLink.keyHeld(Key::A)) {
            rotation = -1;
        }
        else if (PestoLink.keyHeld(Key::D)) {
            rotation = 1;
        }

        drivetrain.arcadeDrive(throttle, rotation);
		
		// Here we decide what the servo angle will be based on if a button is pressed ()
		// if (PestoLink.buttonHeld(0)) {
		// 	servoAngle = 50;
		// }
		// else {
		// 	servoAngle = 110;
		// }
		
		// Here we set the drivetrain motor speeds and servo angle based on what we found in the above code
		//servo.write(servoAngle);		
		
        RSL::setState(RSL_ENABLED);
    } else {
        RSL::setState(RSL_DISABLED);
    }

    RSL::update();
}
