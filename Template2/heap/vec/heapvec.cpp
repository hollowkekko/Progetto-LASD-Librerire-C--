#include "heapvec.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : Vector<Data>(container) {
    BuildHeap();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {
    BuildHeap();
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other) : Vector<Data>(other) {
    // Il vettore copiato dovrebbe già essere un heap valido
}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {
    // Il vettore spostato dovrebbe già essere un heap valido
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
    Vector<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) {
    Vector<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
    return Vector<Data>::operator==(other);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (inherited from Heap)

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
    // Gestione dei casi limite
    if (elements == nullptr || size <= 1) {
        return true; // Vuoto o singolo elemento è sempre un heap valido
    }
    
    // Verifica la proprietà heap per tutti i nodi interni
    for (uint i = 0; i < size / 2; ++i) {
        uint leftChild = 2 * i + 1;
        uint rightChild = 2 * i + 2;
        
        // Controlla figlio sinistro
        if (leftChild < size && elements[i] < elements[leftChild]) {
            return false; // Proprietà max-heap violata
        }
        // Controlla figlio destro (se esiste)
        if (rightChild < size && elements[i] < elements[rightChild]) {
            return false; // Proprietà max-heap violata
        }
    }
    
    return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() noexcept {
    BuildHeap();
}

/* ************************************************************************** */

// Specific member function (inherited from SortableLinearContainer)

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    // Gestione dei casi limite
    if (elements == nullptr || size <= 1) {
        return; // Un heap vuoto o con un solo elemento è già ordinato
    }
    
    // Implementazione dell'algoritmo di ordinamento heap sort
    uint originalSize = size;
    
    // Costruisci il heap se non è già valido
    if (!IsHeap()) {
        BuildHeap();
    }
    
    // Estrai gli elementi uno per uno dal heap
    for (uint i = size - 1; i > 0; --i) {
        // Sposta l'elemento più grande alla fine
        std::swap(elements[0], elements[i]);
        
        // Riduci temporaneamente la dimensione del heap
        --size;
        
        // Ripristina la proprietà del heap
        DownHeap(0);
    }
    
    // Ripristina la dimensione originale
    size = originalSize;
}

template <typename Data>
void HeapVec<Data>::Clear() {
    Vector<Data>::Clear();
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void HeapVec<Data>::DownHeap(uint index) {
    uint largest = index;
    uint leftChild = 2 * index + 1;
    uint rightChild = 2 * index + 2;
    
    // Trova il più grande tra radice, figlio sinistro e figlio destro
    if (leftChild < size && elements[leftChild] > elements[largest]) {
        largest = leftChild;
    }
    
    if (rightChild < size && elements[rightChild] > elements[largest]) {
        largest = rightChild;
    }
    
    // Se il più grande non è la radice, scambia e continua
    if (largest != index) {
        std::swap(elements[index], elements[largest]);
        DownHeap(largest);
    }
}


template <typename Data>
void HeapVec<Data>::BuildHeap() {
    if (size <= 1) return;
    
    // Inizia dal primo nodo non foglia e scendi fino alla radice
    for (int i = (size / 2) - 1; i >= 0; --i) {
        DownHeap(i);
    }
}

/* ************************************************************************** */
}