# STL_Containers

Implementations for some standard library containers and some other data structures. Every implementation contains a `main()` functions that performs some basic tests. <br> The `Queue` data has all its tests inside the `CircularQueue` class, because it derives from `Queue` and therefore all tests can be performed in one place. <br> All implementations have `copy / move` constructors and assignment operators defined.


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

An implementation of a doubly Linked List data structure. Basically there's a struct `Link` that hold pointers to the previous and next links, with both are also of type `Link`. 
<br>Each link holds some value, and `List` type basically holds a list of many `Link` objects and allows insertion, deletion and iteration over them.</br>

#### Properties
* Insertion and deletion - O(1) using `pop_back() pop_front() push_back() push_front()`.
* Access to elements - O(n) unless an iterator is given (see notes).

#### Notes
1. Deletion of a Link iterator frees up the current memory allocated by the Link in that iterator (`current`)
2. Accessing is usually O(n) because performing `(itr + n)` where `n` is an integer is undefined behaviour. Iterating forward and backward is possible only by incrementing the iterator (`operator++` or `operator--`). <br> After the correct iterator has been found, you can pass it to the `erase()` method. </br>

## Map
An implementation of an Unorderd Map data structure. Elements are accesses by keys, which then undergo a hash operation that transforms the key into an integer value that goes through a modulus operation with the amount of buckets size (more on that later). <br>Basically, there's an array of Linked Lists (each list is called a bucket). The aforementioned integer result from the hashing and modulus operation, defines which bucket (array element index) from the array will be used to store the value.<br>The reason to use an array of buckets rather than an array of the values directly, is because some keys may produce the same hash and modulus result, and therefore collide. By using a list as a bucket, we can store several values in the same list, under the same hash result.<br>What this means, in order words, is that in order to access a key, we first need to find the correct list inside the array, and then the correct link (`std::pair` - see notes) inside the list.

#### Properties
* All operations, insertion deletion and access, are usually O(1) but theoretically can be up to O(n).

#### Notes
1. The buckets (lists) store `std::pair`-type links, where the `pair->first` is the original key, and `pair->second` is the stored value. This is needed in order to find the right value for buckets that have several values.

## Heap
An implementation of the Heap data structure. The elements of the container are stored inside a hidden array `_elem_arr`. The array is then sorted (`sort_heap()`) in such a way that represents a heap.<br>In a heap container, the elements are stored in nodes, where each node has a parent node (except for the top node) and either 0, 1 or 2 child nodes. The nodes are sorted in such a way (see note 2), where they have to follow some rules with their parent node, but not necessarily with the left / right nodes. For example, the "MaxHeap" is a type of heap where each node, has a bigger parent node.
<br><br>For element at index `i`, the corresponding parent/child nodes would be located as followed:<br>├ Parent - `floor((i-1)/2)`<br>├ Left Child - `2*i + 1`<br>├ Right Child - `2*i + 2`

#### Properties
* Insertion is basically O(1) because the value is inserted as the last underlying array element, but the process of heapifying (even after insertion) is O(nlog n)

#### Notes
1. Level-order-traversal is used to iteratore over the nodes in this implementation
2. In order to define the sorting algorithm, you need to pass a function pointer into the constructor that accepts (node index, parent_node index) as params and returns a bool value.<br>You can see the usage of `is_bigger()` as an example in the `main()` method.
3. The `has_*` methods, which are used to find out whether a node has parent/child nodes, return `-1` if no such nodes exist.

## Stack
An implementation of a Stack data structure container. A container that has an underlying array, and allows insertion / deletion of the top element in the array only.

#### Properties
* Access is LIFO - last in first out
* Insertion, deletion are always O(1) - see notes

#### Notes
1. `pop()` method simply decrements the pointer of the top element, but that element does not get removed. <br> it was considered at first to reallocate the array without the top element.
2. Using `pop()` on an empty Stack or `push()` on a full stack would throw an exception.

## Pair
An implementation of the Pair data structure container. Basically, a single class that has `this->first` and `this->second` members. This is mostly used in order to store values with some other values together. One example for the usage of `std::pair` can be seen in the `Unordered Map` implementation.

#### Properties
* Insertion, deletion and access are always O(1).

#### Notes
1. No dynamic memory allocation is used in this implementation.
