// particle.cpp
// Implementation of the particle base class
// Student ID: j81369av
// Date: April 08, 2025

#include "particle.h"
#include <stdexcept>

// Implementation of Particle base class

Particle::Particle(double mass, double energy)
  : rest_mass(mass), energy(energy)
{
  if (mass < 0)
  {
    throw std::invalid_argument("Rest mass cannot be negative");
  }
  if (energy < 0)
  {
    throw std::invalid_argument("Energy cannot be negative");
  }
}

Particle::~Particle() = default;

double Particle::get_rest_mass() const
{
  return rest_mass;
}

double Particle::get_energy() const
{
  return energy;
}

void Particle::set_rest_mass(double mass)
{
  if (mass < 0)
  {
    throw std::invalid_argument("Rest mass cannot be negative");
  }
  rest_mass = mass;
}

void Particle::set_energy(double e)
{
  if (e < 0)
  {
    throw std::invalid_argument("Energy cannot be negative");
  }
  energy = e;
}