// stable_nucleus.cpp
// Implementation of stable nucleus class
// Student ID: j81369av
// Date: April 08, 2025

#include "stable_nucleus.h"
#include <iostream>

// Implementation for Stable_Nucleus class

Stable_Nucleus::Stable_Nucleus(double mass, int number, Nucleus_Type type)
  : Nucleus(mass, number, type)
{
  // Nothing specific to do for stable nuclei
}

Stable_Nucleus::~Stable_Nucleus() = default;

void Stable_Nucleus::print_data() const
{
  std::cout << "Stable nucleus: " << nucleus_type_to_string() << "-" << atomic_mass 
            << " (Z=" << atomic_number << ")" << std::endl;
  std::cout << "  This nucleus is stable and does not decay." << std::endl;
}