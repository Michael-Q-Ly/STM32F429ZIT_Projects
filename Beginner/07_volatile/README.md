Quickfix to Project 6, where we use the volatile qualifier
and optimize our program. Why do we use the volatile qualifier, though?

"volatile helps prevent the compiler from applying
optimization on objects that can be changed by ways
that cannot be determined by the compiler."

In other words, volatile objects may have their value
changed at any time by the user, or by another thread
is running and using the same variable.

This program essentially adds the volatile qualifier wherever
necessary.
