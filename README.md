# STL_Containers

Implementations for some standard library containers and some other data structures

## Queue
* Queue - An implementation of a queue, a data structure of a fixed size container where insertion / extraction works in FIFO order. `enqueue()` inserts an element, `dequeue()` extracts an element. Once the queue is filled (last element of the array has an element), the queue cannot receive any more insertions until the last element has been dequeued and the queue is reset.
* Circular Queue - an implementation of a circular queue, where insertion may take place even when the last array index has an element, assuming the first index has been freed up previously (dequeue). This class inherits from the traditional Queue class and has the relevant methods overwritten in order to allow the circular insertion feature, which was meant to make the implementation more memory efficient.

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

## Vector
