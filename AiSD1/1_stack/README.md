Stack
=====

#### What is a stack?

It's a simple data structure - a special case of a list - which utilizes LIFO strategy. \
Only two operations are essential: `push()` (put element on stack) and `pop()` (take element from stack). \
The name is an analogy to a set of physical items stacked one atop another, e.g. a stack of plates.

#### Examples of stack usage

* **backtracking**
* **undo**/**redo**
* **evaluation of arithmetic expressions** (often utilizing Reverse Polish Notation)
* **delimiter checking** during language parsing
* **function calls**

#### Why does `pop()` from `std::stack` not return the value of element?

Inner alia, efficiency issues - the return value of `pop()` wouldn't always
be stored, thus the copying of data would be a waste of time.

#### Why does `pop()` from `std::stack` not return the reference to element?

Reference to value which gets lost alongside popped node is obviously invalid

#### What's the usage of `std::queue::emplace`?

> Pushes a new element to the end of the queue. The element is constructed
> in-place, i.e. no copy or move operations are performed. The constructor
> of the element is called with exactly the same arguments as supplied to
> the function.
>
> Effectively calls `c.emplace_back(std::forward<Args>(args)...);`

~ https://en.cppreference.com/w/cpp/container/queue/emplace
