// photon.h
// Concrete class for photons
// Student ID: j81369av
// Date: April 08, 2025

#ifndef PHOTON_H
#define PHOTON_H

#include "particle.h"
#include <memory>
#include <vector>

// Forward declaration
class Electron;

// Concrete class for photons
class Photon : public Particle 
{
private:
  // Vector of smart pointers to electrons for pair production
  std::vector<std::shared_ptr<Electron>> pair_production_electrons;
  
public:
  // Constructor (photons always have zero rest mass)
  explicit Photon(double energy);
  
  // Destructor
  ~Photon() override;
  
  // Add electrons from pair production
  void add_pair_production_electron(std::shared_ptr<Electron> electron);
  const std::vector<std::shared_ptr<Electron>>& get_pair_production_electrons() const;
  
  // Print data
  void print_data() const override;
  
  // Friend functions for photon interactions
  friend double photoelectric_effect(const Photon& photon);
  friend double compton_effect(Photon& photon, double theta);
  friend std::vector<std::shared_ptr<Electron>> pair_production(Photon& photon);
};

// Photon interaction function declarations
double photoelectric_effect(const Photon& photon);
double compton_effect(Photon& photon, double theta);
std::vector<std::shared_ptr<Electron>> pair_production(Photon& photon);

#endif // PHOTON_H