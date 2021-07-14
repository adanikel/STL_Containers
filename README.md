# STL_Containers

Implementations for some standard library containers and some other data structures


## Vector

An implementation similar to the STL vector container. This implementation is built on top of an array. Whenever an element is inserted, the array needs to reallocate memory is there is not enough free space left in the array. By default, the array size always allocated double the size it currently holds (`_DEF_EXT_VAL`).  <br>The iterator is defined as T* type here, in order to allow easy iteration over the array. </br>

#### Properties
* Access - O(1) assuming the element location is known.
* Insertion - O(1) using `push_back()` unless re-allocation is required in which case it would be up to O(n). <br> Using `insert()` would be up to O(n).</br>  Using `set()` method, insertion is always O(1), but the location index should be known and the existing value there will be overwritten.
* Deletion - Up to O(n) using the `erase()` or `pop_back()` method. 

Notes
1. `pop_back()` method simply reallocates a new array of the same size and copies all elements to that array, without the last element. Not very efficient.
2. Access element location using `at()`, `get()` or `set()` would throw an exception if no element exists there.
3. Accessing element location using `[]` does not check whether the index location is correct and therefore leads to possibly undesired bevahiour but is faster performance-wise than `get() set() at()` methods.  <br>The following line in `main()` illustrates defining an array index that is above the vector size: `var[8] = 8` </br>
4. Reallocation to new array (for example in `pop_back()` uses `std::move`() instead of `std::copy()` to move all elements to the new array

## Queue
* Queue - An implementation of a queue, a data structure of a fixed size container where insertion / extraction works in FIFO order.  <br>`enqueue()` inserts an element, `dequeue()` extracts an element. Once the queue is filled (last element of the array has an element), the queue cannot receive any more insertions until the last element has been dequeued and the queue is reset.  </br>
* Circular Queue - an implementation of a circular queue, where insertion may take place even when the last array index has an element, assuming the first index has been freed up previously (dequeue). This class inherits from the aforementioned Queue class and has the relevant methods overwritten in order to allow the circular insertion feature, which was meant to make the implementation more memory efficient.

#### Properties

* FIFO order (first in first out)
* Insertion and deletion - O(1)
* Underlying implementation - array and two pointers to the first and last inserted elements

#### Notes
1. If the queue is full and `enqueue()` is called, an exception is thrown.
2. If the queue is empty and `dequeue()` is called, an exception is thrown.

## List

An implementation of a doubly Linked List data type. Basically there's a struct `Link` that hold pointers to the previous and next links, with both are also of type `Link`. 
<br>Each link holds some value, and `List` type basically holds a list of many `Link` objects and allows insertion, deletion and iteration over them.</br>

### Properties
* Insertion and deletion - O(1) using `pop_back() pop_front() push_back() push_front()`
* Access to elements - O(n) unless iterator location is known.

## Map

## Pair
