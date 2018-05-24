#pragma config(Sensor, in1,    doorPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in2,    ballDetector,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  winchEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderResetSwitch, sensorTouch)
#pragma config(Sensor, dgtl4,  debugSwitch1,   sensorTouch)
#pragma config(Sensor, dgtl5,  debugSwitch2,   sensorTouch)
#pragma config(Motor,  port1,           winch,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           door,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float kWinchP = 0;
float kDoorP = 0;
float kBallDetectedThreshold = 0;
float kWinchUpPosition = 0;
float kWinchDownPosition = 0;
float kDoorOpenPosition = 0;
float kDoorClosedPosition = 0;
float kDoorTolerance = 10;
float kWinchTolerance = 10;

bool isWithinTolerance(float value, float tolerance) {
	if (abs(value) <= tolerance) {
		return true;
	}
	else {
		return false;
	}
}

float getWinchPosition() {
	return SensorValue[winchEncoder];
}

void resetWinchEncoder() {
	SensorValue[winchEncoder] = 0;
}

void setWinchPositionPID(float desiredPosition) {
	float error = desiredPosition - getWinchPosition();
	while(!isWithinTolerance(error, kWinchTolerance)) {
		error = desiredPosition - getWinchPosition();
		float power = error * kWinchP;
		startMotor(winch, power);
	}
}

float getDoorPosition() {
	return SensorValue[doorPotentiometer];
}

void resetDoorPotentiometer() {
	SensorValue[doorPotentiometer] = 0;
}

void setDoorPositionPID(float desiredPosition) {
	float error = desiredPosition - getDoorPosition();
	while(!isWithinTolerance(error, kDoorTolerance)) {
		error = desiredPosition - getDoorPosition();
		float power = error * kDoorP;
		startMotor(winch, power);
	}
}

float getBallDetectorValue() {
	return SensorValue[ballDetector];
}

bool hasBall() {
	if (getBallDetectorValue() > kBallDetectedThreshold) {
		return true;
	}
	else {
		return false;
	}
}

task whenResetSwitchPressed() {
	while(true) {
		if (SensorValue[encoderResetSwitch]) {
			resetWinchEncoder();
		}
	EndTimeSlice();
	}
}

task main() {
	/*
	startTask(whenResetSwitchPressed);
	while(true) {
		if (hasBall()) {
			setWinchPositionPID(kWinchUpPosition);
			setDoorPositionPID(kDoorOpenPosition);
		}
		else {
			setDoorPositionPID(kDoorClosedPosition);
			setWinchPositionPID(kWinchDownPosition);
		}
	}
	*/

	while (true) {
		if (SensorValue[debugSwitch1]) {
			//setWinchPositionPID(kWinchUpPosition);
			//setDoorPositionPID(kDoorOpenPosition);
			startMotor(winch, 50);
			//startMotor(door, 50);

		}
		else if (SensorValue[debugSwitch2]) {
			//setWinchPositionPID(kWinchDownPosition);
			//setDoorPositionPID(kDoorOpenPosition);
			startMotor(winch, -50);
			//startMotor(door, -50);
		}
	}
}
