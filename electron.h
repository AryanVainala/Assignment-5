// electron.h
// Concrete class for electrons (and positrons)
// Student ID: j81369av
// Date: April 08, 2025

#ifndef ELECTRON_H
#define ELECTRON_H

#include "particle.h"
#include "constants.h"
#include <memory>
#include <vector>

// Forward declaration
class Photon;

// Concrete class for electrons (and positrons)
class Electron : public Particle 
{
private:
  // Vector of smart pointers to photons for radiation
  std::vector<std::shared_ptr<Photon>> radiation_photons;
  
public:
  // Constructor with only energy parameter (mass is fixed to ELECTRON_MASS)
  explicit Electron(double energy);
  
  // Destructor
  ~Electron() override;

  //Setters
  void set_energy(double e) override;
  
  // Radiation functions
  void add_radiation_photon(std::shared_ptr<Photon> photon);
  const std::vector<std::shared_ptr<Photon>>& get_radiation_photons() const;
  
  // Print data
  void print_data() const override;
  
  // Friend function for radiation
  friend std::shared_ptr<Photon> radiate(Electron& electron);
};

// Electron radiation function declaration
std::shared_ptr<Photon> radiate(Electron& electron);

#endif // ELECTRON_H
