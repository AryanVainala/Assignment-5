// Main program demonstrating the simulation of radioactive nuclei decay
// and photon interactions with matter
// Student ID: j81369av
// Date: April 08, 2025

#include "nucleus.h"
#include "stable_nucleus.h"
#include "radioactive_nucleus.h"
#include "particle.h"
#include "photon.h"
#include "electron.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

int main()
{
  std::cout << "Nuclear Decay and Photon Interaction Simulation" << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  
  // Create the nuclei
  std::cout << "\nCreating nuclei..." << std::endl;
  
  // Create a stable Fe-56 nucleus
  auto fe56 = std::make_shared<Stable_Nucleus>(56.0, 26, Nucleus_Type::Fe);
  
  // Create radioactive nuclei
  // Cs-137 decay: produces a 661 keV photon
  auto cs137 = std::make_shared<Radioactive_Nucleus>(
    137.0, 55, Nucleus_Type::Cs, 30.17, std::vector<double>{0.661}
  );
  
  // Na-22 decay: produces a 1274.5 keV photon and positron emission
  auto na22 = std::make_shared<Radioactive_Nucleus>(
    22.0, 11, Nucleus_Type::Na, 2.6, std::vector<double>{1.2745}
  );
  
  // Co-60 decay: produces two photons with energies 1173 keV and 1333 keV
  auto co60 = std::make_shared<Radioactive_Nucleus>(
    60.0, 27, Nucleus_Type::Co, 5.27, std::vector<double>{1.173, 1.333}
  );
  
  // Create a vector of nuclei for polymorphic operations
  std::vector<std::shared_ptr<Nucleus>> nuclei;
  nuclei.push_back(fe56);
  nuclei.push_back(cs137);
  nuclei.push_back(na22);
  nuclei.push_back(co60);

  // Print information about all nuclei
  std::cout << "\nPrinting nuclei information:" << std::endl;
  for (const auto& nucleus : nuclei)
  {
    nucleus->print_data();
    std::cout << std::endl;
  }
  
  // Attempt to make stable nucleus decay (should not work)
  std::cout << "\nAttempting to make Fe-56 decay:" << std::endl;
  try
  {
    // Using dynamic_cast to check if this is a Radioactive_Nucleus
    auto radioactive_fe56 = std::dynamic_pointer_cast<Radioactive_Nucleus>(fe56);
    if (radioactive_fe56)
    {
      radioactive_fe56->decay();
    }
    else
    {
      std::cout << "Fe-56 is stable and cannot decay." << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
  
  // Make radioactive nuclei decay
  std::cout << "\nDecaying radioactive nuclei:" << std::endl;
  
  // Vector to store all photons from decays
  std::vector<std::shared_ptr<Photon>> all_photons;
  
  // Decay Cs-137
  std::cout << "\nDecaying Cs-137:" << std::endl;
  auto cs137_radioactive = std::dynamic_pointer_cast<Radioactive_Nucleus>(cs137);
  auto cs137_photons = cs137_radioactive->decay();
  all_photons.insert(all_photons.end(), cs137_photons.begin(), cs137_photons.end());
  
  // Decay Na-22
  std::cout << "\nDecaying Na-22:" << std::endl;
  auto na22_radioactive = std::dynamic_pointer_cast<Radioactive_Nucleus>(na22);
  auto na22_photons = na22_radioactive->decay();
  all_photons.insert(all_photons.end(), na22_photons.begin(), na22_photons.end());
  
  // Decay Co-60
  std::cout << "\nDecaying Co-60:" << std::endl;
  auto co60_radioactive = std::dynamic_pointer_cast<Radioactive_Nucleus>(co60);
  auto co60_photons = co60_radioactive->decay();
  all_photons.insert(all_photons.end(), co60_photons.begin(), co60_photons.end());
  
  // Print information about all photons
  std::cout << "\nAll photons from decays:" << std::endl;
  for (size_t i = 0; i < all_photons.size(); ++i)
  {
    std::cout << "Photon " << i+1 << ": ";
    all_photons[i]->print_data();
  }
  
  // Demonstrate photon interactions
  std::cout << "\nDemonstrating photon interactions:" << std::endl;
  
  // Photoelectric effect with the Cs-137 photon
  std::cout << "\nPhotoelectric effect with Cs-137 photon:" << std::endl;
  double absorbed_energy = photoelectric_effect(*all_photons[0]);
  std::cout << "Absorbed energy: " << absorbed_energy << " MeV" << std::endl;
  
  // Compton effect with one of the Co-60 photons
  std::cout << "\nCompton effect with Co-60 photon:" << std::endl;
  double scatter_angle = M_PI / 4.0; // 45 degrees
  double new_energy = compton_effect(*all_photons[3], scatter_angle);
  std::cout << "New photon energy after Compton scattering: " << new_energy << " MeV" << std::endl;

  // Try pair production with various photons

  // First with Cs-137 photon (should fail - energy too low)
  std::cout << "\nAttempting pair production with Cs-137 photon (0.661 MeV):" << std::endl;
  auto pairs_from_cs137 = pair_production(*all_photons[0]);
  std::cout << "There are " << pairs_from_cs137.size() << " electrons" << std::endl; // Returns empty array

  // Then with Na-22 photon (should succeed - energy is 1274.5 MeV)
  std::cout << "\nAttempting pair production with Na-22 photon (1274.5 MeV):" << std::endl;
  auto pairs_from_na22 = pair_production(*all_photons[1]);
  std::cout << "There are " << pairs_from_na22.size() <<  " electrons" <<std::endl; // Returns array of size 2

  // Demonstrate electron radiation
  if (!pairs_from_na22.empty())
  {
    std::cout << "\nDemonstrating electron radiation from pair-produced electron:" << std::endl;
    auto& electron = pairs_from_na22[0];
    electron->print_data();
    
    // Make the electron radiate a photon
    auto radiated_photon = radiate(*electron);
    if (radiated_photon)
    {
      std::cout << "Electron after radiation:" << std::endl;
      electron->print_data();
      
      std::cout << "Radiated photon:" << std::endl;
      radiated_photon->print_data();
    }
  }

  try
  {
    auto unphysical_electron = Electron(0.2); // Tests electron constructor
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
  
  
  std::cout << "\nTesting radiation with a manually created energetic electron:" << std::endl;

  // Create an electron with energy = 1.0 MeV
  auto energetic_electron = std::make_shared<Electron>(1.0);

  // Print starting state
  energetic_electron->print_data();

  int radiation_count = 0;

  // Loop: radiate until no photons left OR insufficient energy
  int max_iterations = 100; // This guarantees the while loop breaks if something goes wrong
  int current_iteration = 0;
  
  while (current_iteration++ < max_iterations)
  {
    std::shared_ptr<Photon> emitted = radiate(*energetic_electron);
    
    if (!emitted)
    {
      std::cout << "Radiation stopped: either no photons left or energy too low." << std::endl;
      break;
    }
    
    ++radiation_count;

    std::cout << "Photon " << radiation_count << " radiated with energy: "
              << emitted->get_energy() << " MeV" << std::endl;
  }

  std::cout << "\nFinal state of the electron after radiation:" << std::endl;
  energetic_electron->print_data();
  
  // Print final state of all nuclei
  std::cout << "\nFinal state of all nuclei:" << std::endl;
  for (const auto& nucleus : nuclei)
  {
    nucleus->print_data();
    std::cout << std::endl;
  }

  std::cout << "\nSimulation completed successfully." << std::endl;

  return 0;
}