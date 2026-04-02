#include "pqheap.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>(container) {
    // Il costruttore di HeapVec già costruisce l'heap
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container) : HeapVec<Data>(std::move(container)) {
    // Il costruttore di HeapVec già costruisce l'heap
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap& other) : HeapVec<Data>(other) {
    // Copia dell'heap già valido
}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap&& other) noexcept : HeapVec<Data>(std::move(other)) {
    // Spostamento dell'heap già valido
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap& other) {
    HeapVec<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap&& other) noexcept {
    HeapVec<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Priority Queue specific member functions

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    return elements[0]; // L'elemento con priorità massima è sempre alla radice
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    
    // Sposta l'ultimo elemento alla radice
    elements[0] = std::move(elements[size - 1]);
    --size;
    
    // Ripristina la proprietà del heap se ci sono ancora elementi
    if (size > 0) {
        HeapVec<Data>::DownHeap(0);
    }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    
    // Salva l'elemento da restituire
    Data result = std::move(elements[0]);
    
    // Sposta l'ultimo elemento alla radice
    elements[0] = std::move(elements[size - 1]);
    --size;
    
    // Ripristina la proprietà del heap se ci sono ancora elementi
    if (size > 0) {
        HeapVec<Data>::DownHeap(0);
    }
    
    return result;
}

template <typename Data>
  void PQHeap<Data>::Insert(const Data& val) {
    Vector<Data>::Resize(size + 1);
    uint index = size - 1;
    elements[index] = val;

    HeapifyUp(index);
  }

  template <typename Data>
  void PQHeap<Data>::Insert(Data&& val) 
  {
    Vector<Data>::Resize(size + 1);
    uint index = size - 1;
    elements[index] = std::move(val);

    HeapifyUp(index);
  }



template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& val) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Data oldVal = elements[index];
    elements[index] = val;
    
    // Determina se dobbiamo fare heapify up o down
    if (val > oldVal) {
        HeapifyUp(index);
    } else if (val < oldVal) {
        HeapVec<Data>::DownHeap(index);
    }
    // Se val == oldVal, non è necessario fare nulla
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& val) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Data oldVal = elements[index];
    elements[index] = std::move(val);
    
    // Determina se dobbiamo fare heapify up o down
    if (elements[index] > oldVal) {
        HeapifyUp(index);
    } else if (elements[index] < oldVal) {
        HeapVec<Data>::DownHeap(index);
    }
    // Se elements[index] == oldVal, non è necessario fare nulla
}

/* ************************************************************************** */

// Specific member functions (inherited from PQ)

template <typename Data>
void PQHeap<Data>::Clear() {
    HeapVec<Data>::Clear();
}

/* ************************************************************************** */

// Auxiliary function

template <typename Data>
void PQHeap<Data>::HeapifyUp(ulong index) {
    while (index > 0) {
        ulong parent = (index - 1) / 2;
        
        // Se il genitore è già maggiore o uguale, l'heap è valido
        if (elements[parent] >= elements[index]) {
            break;
        }
        
        // Scambia con il genitore e continua verso l'alto
        std::swap(elements[index], elements[parent]);
        index = parent;
    }
}

/* ************************************************************************** */

}