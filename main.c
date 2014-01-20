/* ////////////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////// Written by Micky Abir ///////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////////// */
/* /// Although it is messy, this will be written in as little files as possible. /// */
/* ////// This is a simple Solar System simulation, don't expect much. ////////////// */
/* ////////////////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////// v0.01 Copyright <c> 2013 /////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////////// */

#include "stdio.h"
#include "math.h"

typedef struct
{
  double px, py, pz, vx, vy, vz,  mass;  

} Object;

double sun_sgp; // Standard Gravitational Parameter of the Sun
double pi;
double theta;

Object Earth, Sun;

int warp = 1000000;

void updateEarthPosition()
{
  Earth.px += Earth.vx;
  Earth.py += Earth.vy;
}

void updateEarthVelocity()
{
  double distance = sqrt(pow(Earth.px, 2) + pow(Earth.py, 2));
  double a = 1.496 * pow(10.0, 11.0);
  theta = atan(Earth.py / Earth.px);

  if(Earth.px < 0) theta += pi;
//if(Earth.py < 0) theta += 2 * pi;

  double speed = sqrt(sun_sgp * (2/distance - 1/a));
  
  Earth.vx = - speed * sin(theta);
  Earth.vy = speed * cos(theta);
  Earth.vz = 0;
}

void earthOrbit()
{
  updateEarthPosition();
  updateEarthVelocity();
}

void orbit()
{
  int i;
  for(i = 0; i < warp; i++)
    {
      earthOrbit();
    }
}

void initSolarSystem()
{
  /* Initialize Universal Constants */
  sun_sgp = 1.989 * pow(10.0, 30.0) * 6.67384 * pow(10.0, -11.0);
  pi = 3.1416;

  /* 
     Assumptions:
     
     Earth's orbit is in the x-y plane.
     Everything is relative to Earth's orbit.
     Heliocentric; Sun position (0,0,0);
  */

  // Earth Initialization

  /* Position Initialization */
  Earth.px = 147098291000; // m
  Earth.py = 0;
  Earth.pz = 0;

  /* Velocity Initialization */
  Earth.vx = 0;
  Earth.vy = 30300; // m/s 
  Earth.vz = 0;

  /* Mass */
  Earth.mass = 5.972  * pow(10.0, 24.0);
}

int main()
{
  initSolarSystem();

  for(;;)
    {
      orbit();
      printf("PX: %e\n", Earth.px);
      printf("PY: %e\n", Earth.py);
      printf("Distance: %e\n", sqrt(pow(Earth.px, 2) + pow(Earth.py, 2)));
      printf("VX: %e\n", Earth.vx);
      printf("VY: %e\n", Earth.vy);
      printf("Speed: %e\n", sqrt(pow(Earth.vx, 2) + pow(Earth.vy, 2)));
      printf("Theta: %e\n", theta);
      printf("\033[2J");
    }

  return 0;
}
