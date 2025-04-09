// photon.cpp
// Implementation of the photon class
// Student ID: j81369av
// Date: April 08, 2025

#include "photon.h"
#include "electron.h"
#include "constants.h"
#include <iostream>
#include <cmath>

// Implementation of Photon class

Photon::Photon(double energy)
  : Particle(0.0, energy) // Photons always have zero rest mass
{
  // No additional initialisation needed
}

Photon::~Photon() = default;

void Photon::add_pair_production_electron(std::shared_ptr<Electron> electron)
{
  if (electron)
  {
    pair_production_electrons.push_back(electron);
  }
}

const std::vector<std::shared_ptr<Electron>>& Photon::get_pair_production_electrons() const
{
  return pair_production_electrons;
}

void Photon::print_data() const
{
  std::cout << "Photon with energy: " << energy << " MeV" << std::endl;
  std::cout << "  Number of pair-produced electrons: " << pair_production_electrons.size() << std::endl;
}

// Photon interaction functions

double photoelectric_effect(const Photon& photon)
{
  // Simple implementation that just returns the photon energy
  std::cout << "Photoelectric effect: Photon with energy " << photon.energy 
            << " MeV transfers all its energy" << std::endl;
  return photon.energy;
}

double compton_effect(Photon& photon, double theta)
{
  // Compton effect formula: E' = E / (1 + (E/m_e c^2) * (1 - cos(theta)))
  // Using m_e = 0.511 MeV and c = 1 as specified
  const double electron_mass = Constants::ELECTRON_MASS;
  
  double initial_energy = photon.energy;
  double denominator = 1.0 + (initial_energy / electron_mass) * (1.0 - std::cos(theta));
  double final_energy = initial_energy / denominator;
  
  std::cout << "Compton effect: Photon with energy " << initial_energy 
            << " MeV scattered at angle " << theta * 180.0 / M_PI 
            << " degrees, new energy: " << final_energy << " MeV" << std::endl;
  
  // Update the photon's energy
  photon.energy = final_energy;
  
  return final_energy;
}

std::vector<std::shared_ptr<Electron>> pair_production(Photon& photon)
{
  std::vector<std::shared_ptr<Electron>> produced_electrons;
  
  // Pair production requires at least 2 * electron rest mass energy
  const double electron_mass = Constants::ELECTRON_MASS;
  const double threshold_energy = 2.0 * electron_mass;
  
  if (photon.energy < threshold_energy)
  {
    std::cout << "Error: Photon energy (" << photon.energy 
              << " MeV) is below pair production threshold (" 
              << threshold_energy << " MeV)" << std::endl;
    return produced_electrons; // Return empty vector
  }
  
  // Create an electron and a positron (represented as another Electron)
  auto electron = std::make_shared<Electron>(Constants::ELECTRON_MASS);
  auto positron = std::make_shared<Electron>(Constants::ELECTRON_MASS);
  
  // Add the electrons to the photon's pair production electrons
  photon.add_pair_production_electron(electron);
  photon.add_pair_production_electron(positron);
  
  // Add them to the return vector
  produced_electrons.push_back(electron);
  produced_electrons.push_back(positron);
  
  std::cout << "Pair production: Photon with energy " << photon.energy 
            << " MeV produced electron-positron pair " << std::endl;
  
  return produced_electrons;
}