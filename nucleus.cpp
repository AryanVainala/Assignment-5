// nucleus.cpp
// Implementation of the nucleus base class
// Student ID: j81369av
// Date: April 08, 2025

#include "nucleus.h"
#include <stdexcept>

// Implementation for Nucleus base class

Nucleus::Nucleus(double mass, int number, Nucleus_Type type)
  : atomic_mass(0.0), atomic_number(0), nucleus_type(type), has_decayed(false)
{
  // Validate and set atomic mass and number
  set_atomic_mass(mass);
  set_atomic_number(number);
}

Nucleus::~Nucleus() = default;

double Nucleus::get_atomic_mass() const
{
  return atomic_mass;
}

int Nucleus::get_atomic_number() const
{
  return atomic_number;
}

Nucleus_Type Nucleus::get_nucleus_type() const
{
  return nucleus_type;
}

bool Nucleus::get_has_decayed() const
{
  return has_decayed;
}

void Nucleus::set_atomic_mass(double mass)
{
  if (mass <= 0)
  {
    throw std::invalid_argument("Atomic mass must be positive");
  }
  atomic_mass = mass;
}

void Nucleus::set_atomic_number(int number)
{
  if (number <= 0)
  {
    throw std::invalid_argument("Atomic number must be positive");
  }
  if (number > atomic_mass)
  {
    throw std::invalid_argument("Atomic number cannot exceed atomic mass");
  }
  atomic_number = number;
}

void Nucleus::set_nucleus_type(Nucleus_Type type)
{
  nucleus_type = type;
}

void Nucleus::set_has_decayed(bool decayed)
{
  has_decayed = decayed;
}

std::string Nucleus::nucleus_type_to_string() const
{
  switch (nucleus_type)
  {
    case Nucleus_Type::Ne: return "Ne";
    case Nucleus_Type::Co: return "Co";
    case Nucleus_Type::Cs: return "Cs";
    case Nucleus_Type::Na: return "Na";
    case Nucleus_Type::Fe: return "Fe";
    default: return "Unknown";
  }
}