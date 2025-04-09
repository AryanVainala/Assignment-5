// electron.cpp
// Implementation of the electron class
// Student ID: j81369av
// Date: April 08, 2025

#include "electron.h"
#include "photon.h"
#include "constants.h"
#include <random>
#include <iostream>

// Implementation of Electron class

Electron::Electron(double energy)
  : Particle(Constants::ELECTRON_MASS, energy)
{
  // Initialise with some radiation photons
  // In a real simulation, these might be generated based on the electron energy

  if (energy < Constants::ELECTRON_MASS)
  {
    throw std::invalid_argument("Electron total energy cannot be less than rest mass (0.511 MeV)");
  }
  
  // Create a few photons with random energies (much smaller than electron energy)
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0.001, 0.1 * energy); // 0.1% to 10% of electron energy
  
  // Add 1-3 radiation photons
  int num_photons = 1 + gen() % 3;
  for (int i = 0; i < num_photons; ++i)
  {
    double photon_energy = dist(gen);
    auto photon = std::make_shared<Photon>(photon_energy);
    radiation_photons.push_back(photon);
  }
}

Electron::~Electron() = default;

void Electron::set_energy(double e)
{
  if (energy < Constants::ELECTRON_MASS)
  {
    throw std::invalid_argument("Electron total energy cannot be less than rest mass (0.511 MeV)");
  }
}

void Electron::add_radiation_photon(std::shared_ptr<Photon> photon)
{
  if (photon)
  {
    radiation_photons.push_back(photon);
  }
}

const std::vector<std::shared_ptr<Photon>>& Electron::get_radiation_photons() const
{
  return radiation_photons;
}

void Electron::print_data() const
{
  std::cout << "Electron with rest mass: " << rest_mass << " MeV, energy: " << energy << " MeV" << std::endl;
  std::cout << "  Number of radiation photons: " << radiation_photons.size() << std::endl;
}

// Electron radiation function
std::shared_ptr<Photon> radiate(Electron& electron)
{
  /* 
   * This function simulates an electron radiating a photon.
   * In a real simulation, this would involve complex physics, but for this assignment
   * we'll use a simpler approach where:
   * 1. The electron radiates a random photon from its radiation_photons vector
   * 2. The electron loses energy equal to the photon's energy
   * 3. The photon is removed from the electron's radiation_photons vector
   *
   * If the electron has no radiation photons, or if releasing a photon would
   * reduce the electron's energy below its rest mass, no radiation occurs.
   */
  
  std::shared_ptr<Photon> radiated_photon = nullptr;
  
  // Check if the electron has any radiation photons
  if (electron.radiation_photons.empty())
  {
    std::cout << "Electron cannot radiate: No radiation photons available" << std::endl;
    return radiated_photon;
  }
  
  // Choose a random photon from the vector
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, electron.radiation_photons.size() - 1);
  int index = dist(gen);
  
  radiated_photon = electron.radiation_photons[index];
  
  // Check if radiating this photon would reduce the electron's energy below rest mass
  if (electron.energy - radiated_photon->get_energy() < electron.rest_mass)
  {
    std::cout << "Electron cannot radiate: Insufficient energy" << std::endl;
    return nullptr;
  }
  
  // Remove the photon from the electron's radiation_photons vector
  electron.radiation_photons.erase(electron.radiation_photons.begin() + index);
  
  // Reduce the electron's energy
  electron.energy -= radiated_photon->get_energy();
  
  std::cout << "Electron radiated a photon with energy " << radiated_photon->get_energy() 
            << " MeV. Electron energy now: " << electron.energy << " MeV" << std::endl;
  
  return radiated_photon;
}