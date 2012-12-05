#include "playerClass.h"

#define CENTER 400;
#define PI 3.14159265

Player::Player(double _cenx, double _ceny, double _radius) {
	centerx = _cenx;
	centery = _ceny;
	radius = _radius;
	arcspeed = 0;
	angle = 45;
	radiusspeed = 0;
	rotangle = 0;
	
	return;
}

double Player::degToRad(double deg) {
	return deg*(PI/180);
}

void Player::turnOnEngine() {
	//Turn on thrust
	std::cout << "Engine on\n";
	engineOn = true;
}

void Player::turnOffEngine() {
	std::cout << "Engine off\n";
	engineOn = false;
}

void Player::calcForces() {
	//Calculate the sum of the forces
	//Reset forces for each frame
	fh = 0;
	fv = 0;
	
	//Calculate the horizonal arc force (+ = counter clockwise)
	//From the thrusters
	double forceang; //Angle of engine forces
	forceang = 90+(angle-rotangle);
	if (engineOn) {	
		fh += sin(degToRad(forceang)) * THRUST;
	}
	
	//Calculate the vertical forces (+ = away from center of star/planet)
	//From the Thrusters (uses forceang from above)
	if (engineOn) {
		fv += cos(degToRad(forceang)) * THRUST;
	}
	//From gravity
	fv -= 9.81 * MASS;
	
	//From centrifugal force
	fv += (MASS * arcspeed * arcspeed)/radius;	
	std::cout << "fh=" << fh << " fv=" << fv << std::endl;
}

void Player::rotateSatellite(int dirchoice) {
	if (dirchoice == left) {
		rotspeed += ROT_FORCE;
	} else if (dirchoice == right) {
		rotspeed -= ROT_FORCE;
	}
}

void Player::calcSpeeds() {
	//Calculate the speed of the sat from forces
	double arcaccel = fh/MASS; //Accelleration in arc direction
	arcspeed += arcaccel;
	
	//Calculate velosity of sat in terms of angle/frame
	angspeed = arcspeed/radius;
	
	double radaccel = fv/MASS; //Accelleration in radius direction
	radiusspeed += radaccel;	
	std::cout << "arcs=" << arcspeed << " rads=" << radiusspeed << std::endl;
	
	std::cout << "rotspeed=" << rotspeed << std::endl;
	std::cout << "rotangle=" << rotangle << std::endl;
	return;
}

void Player::updateSatelliteRotation() {
	//Updates the rotation of the satellite
	rotangle += rotspeed;
	return;
}

void Player::updatePosition() {
	double rad = angle*PI/180;
	satSprite.SetX((cos(rad) * radius) + centerx);
	satSprite.SetY((sin(rad) * radius) + centery);
	angle+=angspeed; //Rename to orbitspeed?
	
	std::cout 	<< "x=" << (cos(rad) * radius) + centerx
				<< " y="<< (sin(rad) * radius) + centery << std::endl
				<< " angle=" <<angle << std::endl;
	return;
}

sf::Sprite * Player::getSprite() {
	return &satSprite;
}

void Player::setPlayer(int num) {
	//Set player 1, 2, 3 or 4?
}
