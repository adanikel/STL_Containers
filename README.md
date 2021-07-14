# STL_Containers

Implementations for some standard library containers and some other data structures


## Vector

An implementation similar to the STL vector container. This implementation is built on top of an array. Whenever an element is inserted, the array needs to reallocate memory is there is not enough free space left in the array. By default, the array size always allocated double the size it currently holds (`_DEF_EXT_VAL`). The iterator is defined as T* type here, in order to allow easy iteration over the array.

#### Properties
* Access - O(1) assuming the element location is known.
* Insertion - O(1) using `push_back()` unless re-allocation is required in which case it would be up to O(n). using `insert()` would be up to O(n). Using `set()` method, insertion is always O(1), but the location index should be know and the existing value there will be overwritten.
* Deletion - Up to O(n) using the `erase()` or `pop_back()` method. 

Notes
1. `pop_back()` method simply reallocates a new array of the same size and copies all elements to that array, without the last element. Not very efficient.

## Queue
* Queue - An implementation of a queue, a data structure of a fixed size container where insertion / extraction works in FIFO order. `enqueue()` inserts an element, `dequeue()` extracts an element. Once the queue is filled (last element of the array has an element), the queue cannot receive any more insertions until the last element has been dequeued and the queue is reset.
* Circular Queue - an implementation of a circular queue, where insertion may take place even when the last array index has an element, assuming the first index has been freed up previously (dequeue). This class inherits from the aforementioned Queue class and has the relevant methods overwritten in order to allow the circular insertion feature, which was meant to make the implementation more memory efficient.

#### Properties

* FIFO order (first in first out)
* Insertion and deletion - O(1)
* Underlying implementation - array and two pointers to the first and last inserted elements

#### Notes
1. If the queue is full and `enqueue()` is called, an exception is thrown.
2. If the queue is empty and `dequeue()` is called, an exception is thrown.

## List

## Map

## Pair
