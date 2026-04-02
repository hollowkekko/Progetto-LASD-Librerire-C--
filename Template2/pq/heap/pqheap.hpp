
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, public HeapVec<Data> 
{  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

protected:
  using HeapVec<Data>::size;
  using HeapVec<Data>::elements;

public:

  // Default constructor
  // PQHeap() specifiers;
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
   // PQHeap(argument) specifiers;
  PQHeap(const TraversableContainer<Data>& container);// A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data>&& container);  // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // PQHeap(argument) specifiers;
  PQHeap(const PQHeap& other);

  // Move constructor
  // PQHeap(argument) specifiers;
  PQHeap(PQHeap&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~PQHeap() specifiers;
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  PQHeap& operator=(const PQHeap& other);

  // Move assignment
  // type operator=(argument) specifiers;
  PQHeap& operator=(PQHeap&& other) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers;
  const Data& Tip() const override;      // Override PQ member (must throw std::length_error when empty)      

  // type RemoveTip(argument) specifiers; 
  void RemoveTip() override;      // Override PQ member (must throw std::length_error when empty)  
  
  // type TipNRemove(argument) specifiers;
  Data TipNRemove() override;      // Override PQ member (must throw std::length_error when empty)          


   // type Insert(argument) specifiers;
  void Insert(const Data& val) override;   // Override PQ member (Copy of the value)

  // type Insert(argument) specifiers;
  void Insert(Data&& val) override;     // Override PQ member (Move of the value)


   // type Change(argument) specifiers;
  void Change(ulong index, const Data& val) override;  // Override PQ member (Copy of the value)

  // type Change(argument) specifiers;
  void Change(ulong index, Data&& val) override; // Override PQ member (Move of the value)

/* ************************************************************************ */

  void Clear() override;

  void HeapifyUp(ulong index);

}; 

/* ************************************************************************** */

} // namespace lasd

#include "pqheap.cpp"

#endif