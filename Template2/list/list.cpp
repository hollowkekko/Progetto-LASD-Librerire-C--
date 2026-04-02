#include "list.hpp"
#include <stdexcept>

namespace lasd {

// Specific constructor (Node)
template<typename Data>
List<Data>::Node::Node(Data && dat) noexcept {
  std::swap(data, dat);
}

/* ************************************************************************** */

// Move constructor (Node)
template<typename Data>
List<Data>::Node::Node(Node && nod) noexcept {
  std::swap(data, nod.data);
  std::swap(next, nod.next);
}

/* ************************************************************************** */

// Destructor (Node)
template<typename Data>
List<Data>::Node::~Node() { 
    delete next; 
} 

/* ************************************************************************** */

// Node comparison operators
template <typename Data>
inline bool List<Data>::Node::operator==(const Node& node) const noexcept {
    return data == node.data;
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}

//Clone 
template <typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail){
    if(next == nullptr){
      return tail;
    } 
    else {
      Node * node = new Node(data);
      this->next = next->Clone(tail);
      return node;
    }
  }

/* ************************************************************************** */

// Specific constructors (List)
template <typename Data>
List<Data>::List(const TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& data) {
        InsertAtBack(data);
    });
}

template <typename Data>
List<Data>::List(MappableContainer<Data>&& container) {
    container.Map([this](Data& data) {
        InsertAtBack(std::move(data));
    });
}

/* ************************************************************************** */

// Copy constructor (List)
template <typename Data> 
List<Data>::List(const List<Data> &otherList) {
    if (!(size = otherList.size))
        return;
    head = new Node(*(otherList.head));
    tail = head;
    Node *temp = otherList.head->next;
    while (temp) {
        tail->next = new Node(*temp);
        tail = tail->next;
        temp = temp->next;
    }
}

// Move constructor (List)
template <typename Data>
List<Data>::List(List&& list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
List<Data>::~List() {
    Clear();
}

/* ************************************************************************** */

// Copy assignment
 template <typename Data>
  List<Data> &List<Data>::operator=(const List<Data> &l) {
  
    if (!l.size) {
      Clear();
      return *this;
    }
  
    if (!size) {
      List<Data> temp = l;
      std::swap(temp, *this);
      return *this;
    }
  
    Node *wl = l.head;
    tail = head;
  
    tail->data = wl->data;
  
    while (tail->next && wl->next) {
      tail = tail->next;
      wl = wl->next;
  
      tail->data = wl->data;
    }
  
    if (tail->next) {
      delete tail->next;
      tail->next = nullptr;
    } else
      for (wl = wl->next; wl; wl = wl->next) {
        InsertAtBack(wl->data);
      }
    size = l.size;
    return *this;
  }

// Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        std::swap(size, list.size);
    return *this;
}

/* ************************************************************************** */
// Comparison operators

template <typename Data>
inline bool List<Data>::operator==(const List& list) const noexcept {
    if (size != list.size) {
        return false;
    }
    
    Node* current1 = head;
    Node* current2 = list.head;
    
    while (current1 != nullptr) {
        if (current1->data != current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return true;
}

template <typename Data>
inline bool List<Data>::operator!=(const List& list) const noexcept {
    return !(*this == list);
}

/* ************************************************************************** */
// Specific member functions

template <typename Data>
void List<Data>::InsertAtFront(const Data& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
    ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& value) {
    Node* newNode = new Node(std::move(value));
    newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
    ++size;
}

template <typename Data> 
void List<Data>::RemoveFromFront() {
    if (!size) throw std::length_error("Cannot remove from Empty list");
    Node *temp{head};
    head == tail ? head = tail = nullptr : head = head->next;
    temp->next = nullptr;
    delete temp;
    --size;
}

template <typename Data> 
Data List<Data>::FrontNRemove() {
    if (!size) throw std::length_error("Cannot remove from Empty list");
    Node *temp{head};
    head == tail ? head = tail = nullptr : head = head->next;
    temp->next = nullptr;
    Data data{std::move(temp->data)};
    delete temp;
    --size; 
    return data; 
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& value) {
    Node* newNode = new Node(std::move(value));
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
    if (head == nullptr) {
        throw std::length_error("List is empty");
    }
    
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
}

  template <typename Data>
  Data List<Data>::BackNRemove() {
    if (!size)
      throw std::length_error("Cannot remove from Empty list");
  
    Data d;
  
    if (head == tail) {
      d = std::move(head->data);
      delete head;
      head = tail = nullptr;
    } else {
      Node* prev = head;
      while (prev->next != tail) {
        prev = prev->next;
      }
  
      d = std::move(tail->data);
      delete tail;
      tail = prev;
      tail->next = nullptr;
    }
  
    --size;
    return d;
  }
/* ************************************************************************** */

// MutableLinearContainer member overrides
template <typename Data>
Data& List<Data>::operator[](ulong index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (ulong i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename Data>
Data& List<Data>::Front() {
    if (head == nullptr) {
        throw std::length_error("List is empty");
    }
    return head->data;
}

template <typename Data>
Data& List<Data>::Back() {
    if (tail == nullptr) {
        throw std::length_error("List is empty");
    }
    return tail->data;
}

/* ************************************************************************** */

// LinearContainer member overrides
template <typename Data>
const Data& List<Data>::operator[](ulong index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (ulong i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename Data>
const Data& List<Data>::Front() const {
    if (head == nullptr) {
        throw std::length_error("List is empty");
    }
    return head->data;
}

template <typename Data>
const Data& List<Data>::Back() const {
    if (tail == nullptr) {
        throw std::length_error("List is empty");
    }
    return tail->data;
}


/* ************************************************************************** */

 //PreOrderMap
  template <typename Data>
  void List<Data>::PreOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    fun(curr->data);
    PreOrderMap(fun, curr->next);
  }

/* ************************************************************************** */

 //PostOrderMap
  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderMap(fun, curr->next);
    fun(curr->data);
    }
  
  

/* ************************************************************************** */

// PreOrderTraversableContainer member override
//PreOrderTraverse
  template <typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
  
    fun(curr->data);
    PreOrderTraverse(fun, curr->next);
  }
  

/* ************************************************************************** */

//PostOrderTraverse
  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderTraverse(fun, curr->next);
    fun(curr->data);
  }
  

/* ************************************************************************** */

// ClearableContainer member override
    template <typename Data>
    void List<Data>::Clear() noexcept{
    size = 0;
    delete head;
    head = tail = nullptr;
}

/* ************************************************************************** */

}