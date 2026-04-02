
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : public Heap<Data>, public Vector<Data>
{
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;

  // ...

public:

  // Default constructor
  // HeapVec() specifiers;
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // HeapVec(argument) specifiers;
  HeapVec(const TraversableContainer<Data>& container); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&& container); // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // HeapVec(argument) specifiers;
  HeapVec(const HeapVec<Data>& other);

  // Move constructor
  // HeapVec(argument) specifiers;
  HeapVec(HeapVec<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~HeapVec() specifiers;
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  HeapVec<Data>& operator=(const HeapVec<Data>& other);

  // Move assignment
  // type operator=(argument) specifiers;
  HeapVec<Data>& operator=(HeapVec<Data>&& other);

  /* ************************************************************************ */

  // Comparison operators

  // type operator==(argument) specifiers;
  bool operator==(const HeapVec<Data>& other) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator!=(const HeapVec<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // type IsHeap(argument) specifiers; // Override Heap member
  bool IsHeap() const noexcept override;

  // type Heapify(argument) specifiers; // Override Heap member
  void Heapify() noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)
  
  // type Sort(argument) specifiers; // Override SortableLinearContainer member
  void Sort() noexcept override;

  void Clear() override;

protected:

  // Auxiliary functions, if necessary!
  void DownHeap(uint index);
  void BuildHeap();

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif