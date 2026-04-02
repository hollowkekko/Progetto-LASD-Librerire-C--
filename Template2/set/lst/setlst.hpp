
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>,
               virtual public List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:
   using List<Data>::Node;
   using List<Data>::head;
   using List<Data>::tail;
   using Container::size;
   
   

public:

  // Default constructor
    SetLst() = default;


  /* ************************************************************************ */

  // Specific constructors
    SetLst(const TraversableContainer<Data>&);// A set obtained from a TraversableContainer
    SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
    SetLst(const SetLst<Data>& val) : List<Data>(val) {
      // Non serve nulla in più, poiché List<Data>(other) copia già tutto in ordine e senza duplicati.
    }


  // Move constructor

    SetLst(SetLst<Data>&& val) noexcept : List<Data>(std::move(val)) {
      // Anche qui: nulla di aggiuntivo, il move di List si occupa di tutto
    }

    

  /* ************************************************************************ */

  // Destructor
    ~SetLst() = default;


  /* ************************************************************************ */

  // Copy assignment
  SetLst& operator=(const SetLst<Data>&);

  // Move assignment
  SetLst& operator=(SetLst<Data>&&) noexcept;

  // Comparison operators
  bool operator==(const SetLst<Data>&) const noexcept;
  bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

    Data Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    Data Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    Data Predecessor(const Data&) const; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data PredecessorNRemove(const Data&); // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemovePredecessor(const Data&); // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    Data Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemoveSuccessor(const Data&) override;  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
    bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
    bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

    const Data& operator[](const ulong index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

    bool Exists(const Data&) const noexcept override;// Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override;// Override ClearableContainer member

protected:

  // Funzione ausiliaria per raggiungere un nodo a una certa distanza
  typename List<Data>::Node *Reach(typename List<Data>::Node* startNode, uint steps) const;
        
  typename List<Data>::Node *BinarySearch(const Data& data) const;


};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif