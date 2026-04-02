namespace lasd {

    /* ************************************************************************** */
    // LINEARCONTAINER IMPLEMENTATION 
    
    // Equality operator
    template <typename Data>
    inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& other) const noexcept {
      if (size != other.size)
        return false;
      for (ulong i = 0; i < size; ++i)
        if ((*this)[i] != other[i])
          return false;
      return true;
    }
    
    // Inequality operator
    template <typename Data>
    inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& other) const noexcept {
      return !(*this == other);
    }
    
    
    // Front (const)
    template <typename Data>
    inline const Data& LinearContainer<Data>::Front() const {
      if (size == 0)
        throw std::length_error("Front on empty container");
      return (*this)[0];
    }
    
    // Back (const)
    template <typename Data>
    inline const Data& LinearContainer<Data>::Back() const {
      if (size == 0)
        throw std::length_error("Back on empty container");
      return (*this)[size - 1];
    }
    
    // Traverse (calls PreOrder by default)
    template <typename Data>
    inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
      PreOrderTraverse(fun);
    }
    
    // PreOrderTraverse
    template <typename Data>
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
      for (ulong i = 0; i < size; ++i)
        fun((*this)[i]);
    }
    
    // PostOrderTraverse
    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
      for (ulong i = size; i > 0; --i)
        fun((*this)[i - 1]);
    }
    
    /* ************************************************************************** */
    // MUTABLELINEARCONTAINER IMPLEMENTATION 
    
    // Front (mutable)
    template <typename Data>
    inline Data& MutableLinearContainer<Data>::Front() {
      if (size == 0)
        throw std::length_error("Front on empty container");
      return (*this)[0];
    }
    
    // Back (mutable)
    template <typename Data>
    inline Data& MutableLinearContainer<Data>::Back() {
      if (size == 0)
        throw std::length_error("Back on empty container");
      return (*this)[size - 1];
    }
    
    // Map (calls PreOrderMap by default)
    template <typename Data>
    inline void MutableLinearContainer<Data>::Map(MapFun fun) {
      PreOrderMap(fun);
    }
    
    // PreOrderMap
    template <typename Data>
    inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
      for (ulong i = 0; i < size; ++i)
        fun((*this)[i]);
    }
    
    // PostOrderMap
    template <typename Data>
    inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
      for (ulong i = size; i > 0; --i)
        fun((*this)[i - 1]);
    }
    
    /* ************************************************************************** */
    // SORTABLELINEARCONTAINER IMPLEMENTATION 
    
    // Sort (calls QuickSort)
    template <typename Data>
    void SortableLinearContainer<Data>::Sort() noexcept {
      if (size > 1)
        QuickSort(0, size - 1);
    }
    
    // QuickSort implementation
    template <typename Data>
    void SortableLinearContainer<Data>::QuickSort(ulong left, int right) noexcept {
      if (left < (ulong)right) {
        ulong pivotIndex = Partition(left, right);
        if (pivotIndex > 0) QuickSort(left, pivotIndex - 1);
        QuickSort(pivotIndex + 1, right);
      }
    }
    
    // Partition function for QuickSort
    template <typename Data>
    ulong SortableLinearContainer<Data>::Partition(ulong left, int right) noexcept {
      Data& pivot = (*this)[right];
      ulong i = left;
    
      for (ulong j = left; j < (ulong)right; ++j) {
        if ((*this)[j] < pivot) {
          std::swap((*this)[i], (*this)[j]);
          ++i;
        }
      }
      std::swap((*this)[i], (*this)[right]);
      return i;
    }
    
    }
    