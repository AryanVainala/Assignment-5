// particle.h
// Provides the abstract base class for all particles
// Student ID: j81369av
// Date: April 08, 2025

#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>

// Abstract base class for all particles
class Particle 
{
protected:
  double rest_mass; // in MeV
  // Since particle phys. experiments measure the relativistic energy
  // the 'energy' variable is the the: total energy =  rest mass + kinetic
  double energy; // in MeV
  
public:
  // Constructor
  Particle(double mass, double energy);
  
  // Pure virtual destructor to make class abstract
  virtual ~Particle() = 0;
  
  // Getters
  double get_rest_mass() const;
  double get_energy() const;
  
  // Setters
  void set_rest_mass(double mass);
  virtual void set_energy(double e);
  
  // Pure virtual function to make class abstract
  virtual void print_data() const = 0;
};

#endif // PARTICLE_H