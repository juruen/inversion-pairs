inversion-pairs
===============

C++ Inversion-pairs algorithm using some c++11 features.

Given a list or vector of elements, it will compute the
number of inversion pairs found on it.

This is useful to compare how close a user is to other users.

A user named Rachel orders her favourite books in a list:

1. Book A
2. Book B
3. Book C
4. Book D

If you want to compare Rachel with David, you take David's list.

Say David's list is:

1. Book C
2. Book B 
3. Book D
4. Book A

You would create a vector as follows:

[4, 2, 1, 3]

That is:

Rachel's most favourite book is in 4th position in David's list. So we add 4 in
the first position of the vector.

Rachel's second most favourite book is in 2nd position. So we add 2.

Rachel's third favourite book is in 1st postion. So we add 1.

And so forth.

We can then count the number of inversion pairs in this vector. This allows us
to order a set of users based on how close their book preferences are. The more
inversion pairs the more different they are.

