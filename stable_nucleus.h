// stable_nucleus.h
// Concrete class for stable nuclei
// Student ID: j81369av
// Date: April 08, 2025

#ifndef STABLE_NUCLEUS_H
#define STABLE_NUCLEUS_H

#include "nucleus.h"

// Concrete class for stable nuclei
class Stable_Nucleus : public Nucleus 
{
public:
  // Constructor
  Stable_Nucleus(double mass, int number, Nucleus_Type type);
  
  // Destructor
  ~Stable_Nucleus() override;
  
  // Print data
  void print_data() const override;
};

#endif // STABLE_NUCLEUS_H