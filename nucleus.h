// Nucleus base class implementation    
// Student ID: j81369av
// Date: April 08, 2025

#ifndef NUCLEUS_H
#define NUCLEUS_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>

// Enumeration for valid nucleus types
enum class Nucleus_Type { Ne, Co, Cs, Na, Fe };

// Abstract base class for all nuclei
class Nucleus 
{
protected:
  double atomic_mass;
  int atomic_number;
  Nucleus_Type nucleus_type;
  bool has_decayed;


  // Setters
  void set_atomic_mass(double mass);
  void set_atomic_number(int number);
  void set_nucleus_type(Nucleus_Type type);
  void set_has_decayed(bool decayed);

public:
  // Constructor
  Nucleus(double mass, int number, Nucleus_Type type);
  
  // Pure virtual destructor to make class abstract
  virtual ~Nucleus() = 0;
  
  // Getters
  double get_atomic_mass() const;
  int get_atomic_number() const;
  Nucleus_Type get_nucleus_type() const;
  bool get_has_decayed() const;
  
  // // Setters
  // void set_atomic_mass(double mass);
  // void set_atomic_number(int number);
  // void set_nucleus_type(Nucleus_Type type);
  // void set_has_decayed(bool decayed);
  
  // Convert enum to string for output
  std::string nucleus_type_to_string() const;
  
  // Pure virtual function to make class abstract
  virtual void print_data() const = 0;
};

#endif // NUCLEUS_H