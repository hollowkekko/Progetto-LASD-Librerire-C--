
namespace lasd {

/* ************************************************************************ */
// Specific constructors

// TraversableContainer constructor
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& Tcon) {
 
 elements= Vector<Data>(4);  // Inizializzo con una capacità iniziale di 4 elementi
  
  Tcon.Traverse([this](const Data& elem) {
      Insert(elem);
    });
}

// MappableContainer constructor
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& Mcon) {
    elements = Vector<Data>(4);  
    Mcon.Map([this](Data&& elem) {
        Insert(std::move(elem));
    });
}

// Copy constructor 
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other)
  : elements(other.elements), head(other.head), tail(other.tail) {
  this->size = other.size;
}


// Move constructor 
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept
  : elements(std::move(other.elements)), head(other.head), tail(other.tail) {
  size = other.size;
  other.head = other.tail = other.size = 0;
}

/* ************************************************************************** */
// Assignment operators

// Copy assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
    if (this != &other) {
        elements = other.elements;  
        head = other.head;
        tail = other.tail;
        size = other.size;
    }
    return *this;
}

// Move assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  std::swap(elements, other.elements);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  return *this;
}

/* ************************************************************************** */
// Comparison operators

template <typename Data>
inline bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  if (size != other.size)
    return false;
  for (ulong i = 0; i < size; ++i)
    if ((*this)[i] != other[i])
      return false;
  return true;
}

template <typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */
// OrderedDictionaryContainer specific functions

template <typename Data>
Data SetVec<Data>::Min() const {
  if (size == 0) throw std::length_error("Set is empty");
  return (*this)[0];  
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
  Data val = Min();
  RemoveMin();
  return val;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0) throw std::length_error("Set is empty");
  
  // Shift tutti gli elementi a sinistra
  for (ulong i = 0; i < size - 1; ++i) {
    (*this)[i] = std::move((*this)[i + 1]);
  }
  
  --size;
  
  // Caso speciale: se il container diventa vuoto, resetta head e tail
  if (size == 0) {
    head = tail = 0;
  } else {
    tail = (head + size) % elements.Size();
  }
}

template <typename Data>
Data SetVec<Data>::Max() const {
  if (size == 0) throw std::length_error("Set is empty");
  return (*this)[size-1]; 
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  Data val = Max();
  RemoveMax();
  return val;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0) throw std::length_error("Set is empty");
  --size;
  
  // Caso speciale: se il container diventa vuoto, resetta head e tail
  if (size == 0) {
    head = tail = 0;
  } else {
    tail = (head + size) % elements.Size();
  }
}

template <typename Data>
Data SetVec<Data>::Predecessor(const Data& val) const {
  if (size < 1) throw std::length_error("No predecessor");
  
  ulong index = BinarySearch(val);
  
  //  Se l'index è 0 o val non viene trovato, non c'è predecessore
  if (index == 0 || (index < size && !((*this)[index] < val) && !(val < (*this)[index]))) {
    if (index == 0) throw std::length_error("No predecessor");
    index--;
  } else {
    index--;
  }

  if (index >= size) throw std::length_error("Predecessor not found");
  
  return (*this)[index];  
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
  Data tmp = Predecessor(val);
  Remove(tmp);
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
  Remove(Predecessor(val));
}

template <typename Data>
Data SetVec<Data>::Successor(const Data& val) const {
  if (size < 1) throw std::length_error("No successor");
  
  ulong index = BinarySearch(val);
  
  // Se val è già presente, incrementa l'indice per trovare il successore
  if (index < size && !((*this)[index] < val) && !(val < (*this)[index])) {
    index++;
  }
  
  // Controlla se il successore esiste
  if (index >= size) throw std::length_error("No successor");
  
  return (*this)[index]; 
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& val) {
    Data tmp = Successor(val);
    Remove(tmp); 
    return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
  Remove(Successor(val));
}

/* ************************************************************************ */

// Operator[]
template <typename Data>
Data& SetVec<Data>::operator[](ulong index) {
  if (index >= size) throw std::out_of_range("Index out of range");
  return elements[(head + index) % elements.Size()];
}

/* ************************************************************************ */
// DictionaryContainer specific functions

template <typename Data>
bool SetVec<Data>::Insert(const Data& val) {
    // Usa BinarySearch per trovare sia la posizione che verificare l'esistenza
    ulong pos = BinarySearch(val);
    
    if (pos < size && !((*this)[pos] < val) && !(val < (*this)[pos])) {
        return false;
    }

    if (size >= elements.Size()) {
        Resize(elements.Size() == 0 ? 4 : elements.Size() * 2); // Meglio partire da 4
    }

    for (ulong i = size; i > pos; --i) {
        elements[(head + i) % elements.Size()] = std::move(elements[(head + i - 1) % elements.Size()]);
    }

    elements[(head + pos) % elements.Size()] = val;
    ++size;
    tail = (head + size) % elements.Size();
    
    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& val) {
    ulong pos = BinarySearch(val);
    
    if (pos < size && !((*this)[pos] < val) && !(val < (*this)[pos])) {
        return false;
    }

    if (size >= elements.Size()) {
        Resize(elements.Size() == 0 ? 4 : elements.Size() * 2);
    }

    for (ulong i = size; i > pos; --i) {
        elements[(head + i) % elements.Size()] = std::move(elements[(head + i - 1) % elements.Size()]);
    }

    elements[(head + pos) % elements.Size()] = std::move(val);
    ++size;
    tail = (head + size) % elements.Size();
    
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& val) {
    ulong pos = BinarySearch(val);
    
    // Verifica che l'elemento esista
    if (pos >= size || (*this)[pos] != val) {
        return false;
    }

    for (ulong j = pos; j < size - 1; ++j) {
        (*this)[j] = std::move((*this)[j + 1]);
    }

    --size;
    if (size == 0) {
        head = tail = 0;
    } else {
        tail = (head + size) % elements.Size();
    }
    
    return true;
}

/* ************************************************************************ */
// LinearContainer specific function

template <typename Data>
const Data& SetVec<Data>::operator[](ulong index) const {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[(head + index) % elements.Size()];
}

/* ************************************************************************ */
// TestableContainer specific function

template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept {
  if (size == 0) return false;
  
  ulong index = BinarySearch(val);
  
  return (index < size && !(val < (*this)[index]) && !((*this)[index] < val));
}

/* ************************************************************************ */
// ClearableContainer specific function

template <typename Data>
void SetVec<Data>::Clear() {
  elements.Clear();
  size = head = tail = 0;
}

/* ************************************************************************ */
// Auxiliary functions

template <typename Data>
void SetVec<Data>::Resize(ulong newCap) {
    if (newCap == 0) {
        Vector<Data> temp;
        std::swap(elements, temp);
        head = tail = size = 0;
        return;
    }

    Vector<Data> temp(newCap);
    
    for (ulong i = 0; i < size; i++) {
        temp[i] = elements[(head + i) % elements.Size()];
    }
    
    std::swap(elements, temp);
    head = 0;
    tail = size;
}

template <typename Data>
ulong SetVec<Data>::BinarySearch(const Data& val) const {
  ulong low = 0;
  ulong high = size;

  while (low < high) {
    ulong mid = low + (high - low) / 2;
    if ((*this)[mid] < val)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}
}

