namespace lasd {

  /* ************************************************************************** */
  // Specific constructor

  // TraversableContainer constructor
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& Tcon) {
    Tcon.Traverse([this](const Data& dat) {
        this->Insert(dat); 
      });
  }
  
  // MappableContainer constructor
  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& Mcon) {
    Mcon.Map([this](Data& dat) {
        this->Insert(std::move(dat));
      });
  }
 
  /* ************************************************************************** */
  // Assignment operators
  
  // Copy assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
    List<Data>::operator=(other); // usa l'operatore di assegnazione di List
    return *this;
  }
  
  // Move assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other)); // usa l'operatore di move di List
    return *this;
  }
  
  /* ************************************************************************** */
  // Comparison operators
  
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
    return List<Data>::operator==(other); 
  }
  
  template <typename Data>
  bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
    return !(*this == other); 
  }

  /* ************************************************************************** */
  // OrderedDictionaryContainer specific functions
  
  template <typename Data>
  Data SetLst<Data>::Min() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Front();
  }
  
  template <typename Data>
  Data SetLst<Data>::MinNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Data min = this->Front(); 
    Remove(min); 
    return min;
  }
  
  template <typename Data>
  void SetLst<Data>::RemoveMin() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Front()); 
  }

  template <typename Data>
  Data SetLst<Data>::Max() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Back();
  }
  
  template <typename Data>
  Data SetLst<Data>::MaxNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Data max = this->Back(); 
    Remove(max); 
    return max;
  }
  
  template <typename Data>
  void SetLst<Data>::RemoveMax() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Back()); 
  }
  
  template <typename Data>
  Data SetLst<Data>::Predecessor(const Data& val) const {
      if (this->head == nullptr) throw std::length_error("The list is empty.");

      typename List<Data>::Node* cur = this->head;
      typename List<Data>::Node* prev = nullptr;

      while (cur != nullptr && cur->data < val) {
          prev = cur;
          cur = cur->next;
      }

      if (prev == nullptr) throw std::length_error("No predecessor found.");
      
      return prev->data;
  }
  
  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
    return predecessorElem;
  }
  
  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
  }
  
  template <typename Data>
  Data SetLst<Data>::Successor(const Data& elem) const {
    if (this->Empty()) 
        throw std::length_error("Empty set");

    typename List<Data>::Node* current = this->head;
    
    // Trova il primo elemento maggiore
    while (current != nullptr && current->data <= elem) {
        current = current->next;
    }
    
    if (current == nullptr)
        throw std::length_error("No successor found");
        
    return current->data;
  }
  
  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
    return successorElem;
  }
  
  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
  }
  
  /* ************************************************************************ */
  // DictionaryContainer specific functions
  
  template <typename Data>
  bool SetLst<Data>::Insert(const Data& elem) {
    typename List<Data>::Node* newNode = nullptr;
    typename List<Data>::Node* current = this->head;
    typename List<Data>::Node* previous = nullptr;
    
    while (current != nullptr && current->data < elem) {
        previous = current;
        current = current->next;
    }
    
    if (current != nullptr && current->data == elem) {
        return false;  // Elemento già presente
    }
    
    newNode = new typename List<Data>::Node(elem);
    
    if (previous == nullptr) {
        newNode->next = this->head;
        this->head = newNode;
    } else {
        newNode->next = current;
        previous->next = newNode;
    }
    
    if (current == nullptr) {
        this->tail = newNode;
    }
    
    this->size++;
    return true;
  }
  
  template <typename Data>
  bool SetLst<Data>::Insert(Data&& elem) {
      typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(elem));
   
      if (this->head == nullptr) {
          this->head = this->tail = newNode;  
          this->size = 1;
          return true;
      }
  
      typename List<Data>::Node* current = this->head;
      typename List<Data>::Node* previous = nullptr;
  
      while (current != nullptr && current->data < newNode->data) {
          previous = current;
          current = current->next;
      }
  
      if (current != nullptr && current->data == newNode->data) {
          delete newNode; 
          return false;
      }
  
      if (previous == nullptr) {
          newNode->next = this->head;
          this->head = newNode;
      }
      
      else if (current == nullptr) {
          previous->next = newNode;
          this->tail = newNode;
      }
      
      else {
          previous->next = newNode;
          newNode->next = current;
      }
  
      this->size++;
      return true;
  }
  
  template <typename Data>
  bool SetLst<Data>::Remove(const Data& elem) {
      if (this->head == nullptr) { 
          return false;
      }
  
      typename List<Data>::Node* current = this->head;
      typename List<Data>::Node* previous = nullptr;
  
      while (current != nullptr && current->data != elem) {
          previous = current;
          current = current->next;
      }
  
      if (current == nullptr) {
          return false;
      }
  
      if (previous == nullptr) {
          this->head = current->next;
          if (this->head == nullptr) { 
              this->tail = nullptr;
          }
      }
     
      else {
          previous->next = current->next;
          if (current == this->tail) {  
              this->tail = previous;
          }
      }
  
      typename List<Data>::Node* nodeToDelete = current;
      nodeToDelete->next = nullptr;  
      current = nullptr;
  
      delete nodeToDelete;
      this->size--;    
  
      return true;
  }
  
  /* ************************************************************************ */
  // LinearContainer specific function

  template <typename Data>
  const Data& SetLst<Data>::operator[](const ulong index) const {
      if (index >= this->size) throw std::out_of_range("Index out of range.");
    
      typename List<Data>::Node* current = this->head;
      for (ulong i = 0; i < index; ++i) {  
          current = current->next;
      }
  
      return current->data; 
  }

  /* ************************************************************************** */
  // TestableContainer specific function

  template <typename Data>
  bool SetLst<Data>::Exists(const Data& elem) const noexcept {
    return BinarySearch(elem) != nullptr;
}

  
  /* ************************************************************************ */
  // ClearableContainer specific function

  template <typename Data>
  void SetLst<Data>::Clear() noexcept {
      List<Data>::Clear();
    }
  

 /* ************************************************************************ */
//Auxiliary functions

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::Reach(typename List<Data>::Node* startNode, uint steps) const {
    if (startNode == nullptr) return nullptr;
    typename List<Data>::Node* current = startNode;
    for (uint i = 0; i < steps && current != nullptr; ++i) {
        current = current->next;
    }
    return current;
}

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::BinarySearch(const Data& data) const {
    if (this->size == 0) return nullptr;

    uint left = 0;
    uint right = this->size - 1;

    while (left <= right) {
        uint mid = left + (right - left) / 2;
        typename List<Data>::Node* midNode = Reach(this->head, mid);

        if (midNode == nullptr) break;  // sicurezza

        if (midNode->data == data) {
            return midNode;
        } else if (midNode->data < data) {
            left = mid + 1;
        } else {
            if (mid == 0) break; // per evitare underflow in unsigned
            right = mid - 1;
        }
    }
    return nullptr;
  }
}
