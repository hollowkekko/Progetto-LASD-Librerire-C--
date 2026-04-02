#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public ResizableContainer {
  // Must extend Set<Data>,
  //             ResizableContainer
protected:

  using Container::size; //numero di elementi attuali
  // elements.Size() sarebbe la capacità totale del buffer

  Vector<Data> elements;  
  ulong head = 0;    // inizio logico
  ulong tail = 0;    // fine logico 

public:

  // Default constructor
  SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data>&&);// A set obtained from a MappableContainer

  /* ************************************************************************ */

   // Copy constructor;
  SetVec(const SetVec<Data>&);

  // Move constructor;
  SetVec(SetVec<Data>&&) noexcept; 

  /* ************************************************************************ */

  // Destructor
  ~SetVec() = default; 

  /* ************************************************************************ */

  // Copy assignment
  SetVec<Data>& operator=(const SetVec<Data>&);

  // Move assignment
  SetVec<Data>& operator=(SetVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec<Data>&) const noexcept; // type operator==(argument) specifiers;
  bool operator!=(const SetVec<Data>&) const noexcept; // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  Data Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  Data Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](ulong); // Non-const version for internal use

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  
  // Resize the vector to a new capacity
  void Resize(ulong); 

  // Find the index of a value using binary search
  ulong BinarySearch(const Data&) const; 


};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif