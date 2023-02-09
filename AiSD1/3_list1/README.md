LinkedList (1)
==============

#### Advantages of pointer and of array implementations

In array version certain operations can be faster (e.g. `find(index)` will be constant time) and uses less memory (when filled enough).
Pointer version doesn't have size constraint (except of the machine memory capacity) and can easily remove elements from the middle.

#### How to implement double-linked list with only one pointer per node?

https://en.wikipedia.org/wiki/XOR_linked_list

#### Difference between _forward reference_ and _r-value reference_

_Forward reference_ can be both to l-value and r-value (hence the other name is _universal reference_).
