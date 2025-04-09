// radioactive_nucleus.h
// Concrete class for radioactive nuclei
// Student ID: j81369av
// Date: April 08, 2025

#ifndef RADIOACTIVE_NUCLEUS_H
#define RADIOACTIVE_NUCLEUS_H

#include "nucleus.h"
#include <memory>
#include <vector>

// Forward declaration of Photon class
class Photon;

// Concrete class for radioactive nuclei
class Radioactive_Nucleus : public Nucleus 
{
private:
  double half_life; // in years
  std::vector<double> decay_energies; // in MeV
  
  // Vector of smart pointers to Photon objects, created during decay
  std::vector<std::shared_ptr<Photon>> decay_photons;
  
public:
  // Constructor
  Radioactive_Nucleus(double mass, int number, Nucleus_Type type, double half_life, 
                     std::vector<double> decay_energies);
  
  // Destructor
  ~Radioactive_Nucleus() override;
  
  // Specific getters
  double get_half_life() const;
  const std::vector<double>& get_decay_energies() const;
  const std::vector<std::shared_ptr<Photon>>& get_decay_photons() const;
  
  // Setters
  void set_half_life(double hl);
  void set_decay_energies(const std::vector<double>& energies);
  
  // Print data
  void print_data() const override;
  
  // Decay function that creates photons
  std::vector<std::shared_ptr<Photon>> decay();
};

#endif // RADIOACTIVE_NUCLEUS_H