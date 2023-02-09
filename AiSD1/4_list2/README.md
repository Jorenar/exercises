LinkedList (2)
==============

#### Advantages of pointer and of array implementations

In *array* version certain operations can be faster (e.g. `find(index)` will
be constant time) and uses less memory (when filled enough);
it is essentially a limited vector.

*Pointer* version doesn't have size constraint (except of the machine memory
capacity) and can easily remove elements from the middle.

#### Advantages of cursor-list implementation

It's a combination of array and pointer approaches. 
Still uses array, but entering element in the middle doesn't require shuffling.
