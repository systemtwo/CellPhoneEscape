#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>

enum directions {up, down, left, right};


class Player {
	private:
		sf::Sprite satSprite;
		directions dir;
		double fh; //Horizontal force in the x component (in the direction of the arc as it bends) (net force)
		double fv; //Verical force in component of radius (net force)
		
		double arcspeed; //Speed of orbit around star
		
		double angle; //Where is the satelite around star
		double angspeed; //Rate of change of sat rotation
		
		double rotangle; //How much is the satellite rotated?
		double rotspeed; //How fast is the satellite rotating?
		
		double radius; //How high above star
		double radiusspeed; //Speed of the sat in the radius direction
		double centerx; //Center of orbit
		double centery; //Center of orbit
		
		static const double MASS = 1000; //Mass of the satellite (kg)s
		static const double THRUST = 1000; //Thrust from the engine
		static const double ROT_FORCE = 0.1; //Force (moment) for rotating satellite
		
		bool engineOn;
		//Functions
		
		double degToRad(double); //Degrees to radians
	public:
		Player(double, double, double);
		sf::Sprite * getSprite();
		void turnOnEngine(); //Turn on thrust (Called when accel is pressed)
		void turnOffEngine(); //Turn off engine
		void rotateSatellite(int); //Turn on forces to rotate satellite
		void updateSatelliteRotation(); //Calculate angular velosity
		void calcForces(); //Calculate the sum of the forces
		void calcSpeeds(); //Calculate the speed from forces
		void updatePosition();
		void setPlayer(int);
};
