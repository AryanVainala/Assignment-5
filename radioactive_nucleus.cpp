// radioactive_nucleus.cpp
// Implementation of radioactive nucleus class
// Student ID: j81369av
// Date: April 08, 2025

#include "radioactive_nucleus.h"
#include "photon.h"
#include <stdexcept>
#include <iostream>

// Implementation for Radioactive_Nucleus class

Radioactive_Nucleus::Radioactive_Nucleus(double mass, int number, Nucleus_Type type, 
                                       double half_life, std::vector<double> decay_energies)
  : Nucleus(mass, number, type), half_life(half_life), decay_energies(decay_energies)
{
  if (half_life <= 0)
  {
    throw std::invalid_argument("Half life must be positive");
  }
}

Radioactive_Nucleus::~Radioactive_Nucleus() = default;

double Radioactive_Nucleus::get_half_life() const
{
  return half_life;
}

const std::vector<double>& Radioactive_Nucleus::get_decay_energies() const
{
  return decay_energies;
}

const std::vector<std::shared_ptr<Photon>>& Radioactive_Nucleus::get_decay_photons() const
{
  return decay_photons;
}

void Radioactive_Nucleus::set_half_life(double hl)
{
  if (hl <= 0)
  {
    throw std::invalid_argument("Half life must be positive");
  }
  half_life = hl;
}

void Radioactive_Nucleus::set_decay_energies(const std::vector<double>& energies)
{
  decay_energies = energies;
}

void Radioactive_Nucleus::print_data() const
{
  std::cout << "Radioactive nucleus: " << nucleus_type_to_string() << "-" << atomic_mass 
            << " (Z=" << atomic_number << ")" << std::endl;
  std::cout << "  Half-life: " << half_life << " years" << std::endl;
  std::cout << "  Decay state: " << (has_decayed ? "Has decayed" : "Has not decayed") << std::endl;
  
  if (!decay_energies.empty())
  {
    std::cout << "  Decay energies:";
    for (const auto& energy : decay_energies)
    {
      std::cout << " " << energy << " MeV";
    }
    std::cout << std::endl;
  }
  
  if (!decay_photons.empty())
  {
    std::cout << "  Decay photons: " << decay_photons.size() << " photons produced" << std::endl;
    for (size_t i = 0; i < decay_photons.size(); ++i)
    {
      std::cout << "    Photon " << i+1 << ": ";
      decay_photons[i]->print_data();
    }
  }
}

std::vector<std::shared_ptr<Photon>> Radioactive_Nucleus::decay()
{
  if (has_decayed)
  {
    std::cout << "This nucleus has already decayed." << std::endl;
    return decay_photons;
  }
  
  // Create photons with appropriate energies
  decay_photons.clear();
  
  for (const auto& energy : decay_energies)
  {
    // Create a photon with the given energy
    auto photon = std::make_shared<Photon>(energy);
    decay_photons.push_back(photon);
    
    // Print the photon data
    std::cout << "Photon created with energy " << energy << " MeV" << std::endl;
    photon->print_data();
  }
  
  // Special case for Na-22 (challenge implementation)
  if (nucleus_type == Nucleus_Type::Na)
  {
    // In Na-22 decay, a positron is emitted which then annihilates with an electron
    // to produce two 511 keV photons (pair production in reverse)
    std::cout << "Na-22 decay: Positron emission followed by annihilation with electron" << std::endl;
    
    // Create two photons of 511 keV each (electron-positron annihilation)
    auto annihilation_photon1 = std::make_shared<Photon>(0.511); // 511 keV
    auto annihilation_photon2 = std::make_shared<Photon>(0.511); // 511 keV
    
    decay_photons.push_back(annihilation_photon1);
    decay_photons.push_back(annihilation_photon2);
    
    std::cout << "Two annihilation photons created (511 keV each)" << std::endl;
    annihilation_photon1->print_data();
    annihilation_photon2->print_data();
  }
  
  // Mark the nucleus as decayed
  has_decayed = true;
  
  return decay_photons;
}