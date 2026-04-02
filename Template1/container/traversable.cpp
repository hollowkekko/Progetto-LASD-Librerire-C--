
namespace lasd {

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator accumulator) const {
    Traverse(
        [function, &accumulator](const Data& data) {
        accumulator = function(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;
    Traverse(
        [data, &exists](const Data& current) {
            exists |= (current == data);
        }
    );
    return exists;
}

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
    PreOrderTraverse(
        [function, &accumulator](const Data& data) {
        accumulator = function(data, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>    
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    PreOrderTraverse(function);
}

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
    PostOrderTraverse(
        [function, &accumulator](const Data& data) {
        accumulator = function(data, accumulator);
        }
    );
    return accumulator;
}

} 

