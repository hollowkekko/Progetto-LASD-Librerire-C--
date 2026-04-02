namespace lasd {

    /* ************************************************************************** */
    // VECTOR IMPLEMENTATION 

    // Costruttore con dimensione
    template <typename Data>
    Vector<Data>::Vector(const ulong newSize) {
      size = newSize;
      elements = new Data[size]{}; // inizializzati con default constructor
    }
    
    // TraversableContainer constructor
    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& container) {
      size = container.Size();
      elements = new Data[size];
      ulong index = 0;
      container.Traverse([&](const Data& val) {
        elements[index++] = val;
      });
    }
    
    // MappableContainer constructor
    template <typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& container) {
      size = container.Size();
      elements = new Data[size];
      ulong index = 0;
      container.Map([&](Data& val) {
        elements[index++] = std::move(val);
      });
    }
    
    // Copy constructor
    template <typename Data>
    Vector<Data>::Vector(const Vector& other) {
      size = other.size;
      elements = new Data[size];
      for (ulong i = 0; i < size; ++i)
        elements[i] = other.elements[i];
    }
    
    // Move constructor
    template <typename Data>
    Vector<Data>::Vector(Vector&& other) noexcept {
      std::swap(size, other.size);
      std::swap(elements, other.elements);
    }
    
    // Destructor
    template <typename Data>
    Vector<Data>::~Vector() {
      delete[] elements;
    }
    
    // Copy assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector& other) {
      if (this != &other) {
        Vector tmp(other); 
        std::swap(*this, tmp);
      }
      return *this;
    }
    
    // Move assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector&& other) noexcept {
      std::swap(size, other.size);
      std::swap(elements, other.elements);
      return *this;
    }
    
    // Comparison operators
    template <typename Data>
    bool Vector<Data>::operator==(const Vector& other) const noexcept {
      if (size != other.size)
        return false;
      for (ulong i = 0; i < size; ++i)
        if (elements[i] != other.elements[i])
          return false;
      return true;
    }
    
    template <typename Data>
    inline bool Vector<Data>::operator!=(const Vector& other) const noexcept {
      return !(*this == other);
    }
    
    // Operator[] const
    template <typename Data>
    const Data& Vector<Data>::operator[](ulong index) const {
      if (index >= size)
        throw std::out_of_range("Index out of range");
      return elements[index];
    }
    
    // Operator[] non-const
    template <typename Data>
    Data& Vector<Data>::operator[](ulong index) {
      if (index >= size)
        throw std::out_of_range("Index out of range");
      return elements[index];
    }
    
    // Front() const
    template <typename Data>
    const Data& Vector<Data>::Front() const {
      if (size == 0)
        throw std::length_error("Accessing Front of empty vector");
      return elements[0];
    }
    
    // Front() non-const
    template <typename Data>
    Data& Vector<Data>::Front() {
      if (size == 0)
        throw std::length_error("Accessing Front of empty vector");
      return elements[0];
    }
    
    // Back() const
    template <typename Data>
    const Data& Vector<Data>::Back() const {
      if (size == 0)
        throw std::length_error("Accessing Back of empty vector");
      return elements[size - 1];
    }
    
    // Back() non-const
    template <typename Data>
    Data& Vector<Data>::Back() {
      if (size == 0)
        throw std::length_error("Accessing Back of empty vector");
      return elements[size - 1];
    }
    
    // Resize
    template <typename Data>
    void Vector<Data>::Resize(const ulong newSize) {
      if (newSize == size)
        return;
    
      Data* newElements = new Data[newSize];
      ulong minSize = (newSize < size) ? newSize : size;
      for (ulong i = 0; i < minSize; ++i)
        newElements[i] = std::move(elements[i]);
    
      delete[] elements;
      elements = newElements;
      size = newSize;
    }
    
    // Clear
    template <typename Data>
    void Vector<Data>::Clear() {
      delete[] elements;
      elements = nullptr;
      size = 0;
    }
    
    /* ************************************************************************** */
    // SORTABLEVECTOR IMPLEMENTATION 
    
    // Costruttore con dimensione
    template <typename Data>
    SortableVector<Data>::SortableVector(const ulong newSize)
      : Vector<Data>(newSize) {}
    
    // Costruttore da TraversableContainer
    template <typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& container)
      : Vector<Data>(container) {}
    
    // Costruttore da MappableContainer
    template <typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& container)
      : Vector<Data>(std::move(container)) {}
    
    // Copy constructor
    template <typename Data>
    SortableVector<Data>::SortableVector(const SortableVector<Data>& other)
      : Vector<Data>(other) {}
    
    // Move constructor
    template <typename Data>
    SortableVector<Data>::SortableVector(SortableVector<Data>&& other) noexcept
      : Vector<Data>(std::move(other)) {}
    
    // Copy assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& other) {
        Vector<Data>::operator=(other);
        return *this;
    }
    
    // Move assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& other) noexcept {
      Vector<Data>::operator=(std::move(other));
      return *this;
    }
    
    } 
    