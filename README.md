# (New) Collection of mcl's libraries (and small utils)

I enjoy building my own stuff, and (somewhat consequently) I'm bad at
using other people's stuff.  I also use these libraries across
multiple computers, and need practice with git anyway.

For the time being, none of these libraries are written with other
people's use in mind.  They are written to work with my specific
setup (Arch Linux with st for a terminal), so if, for some reason,
someone on Windows tries to use this, he will have a bad time
out-of-the-box.

***

## String Manipulation with strmanip.h

This is the library I use the most.  Anything that involves strings
(converting numbers to strings, strings to numbers, trimming strings,
reducing whitespace, etc.) goes in here.

In general, whenever it would make sense to do so, every function
which takes a string should be overloaded to also take begin and end
iterators.  The end iterator will always have type
`const const_iterator&`†, while there will be overloads
for the begin iterator having types `const_iterator`†,
`const_iterator&`†, and, if the function intends to
modify the string, `iterator`†, and
`iterator&`†.

> † *For the sake of brevity in documentation, assume an
`std::string` prefix.*


### Getting a String from a Number

There are various templates for converting from Naturals,
from Integers, from Floatings, etc. where the behavior of each
function is more or less independent of the number's type.

In addition to the number argument, these functions take:

- Output Base: An integer in [2, 36] (default = 10) that dictates
	what base the number will be represented in.  Note: this function
	does *not* add any prefixes (like 0x for hexadecimal).
- Minumum Width: An unsigned integer (default = 0).  If non-zero,
	the output will be padded (not with whitespace, but with
	unnecessary zeroes, or by messing with scientific notation) such
	that it is at least that long.
- Do Reversed: A boolean (default = 0) that, if true, causes the
	digits to be written (more consistently) from smallest largest
	place-value, rather than the usual largest to smallest order.


### Getting a Number from a String

Likewise, there are various templates for converting *to* Naturals,
Integers, Floating Points, etc. where, once again, the behavior of
each is relatively independent of the input type.  This time,
however, for each of these functions there is a twin that, instead
of returning a number, modifies a passed reference to a number.

In addition to the input string

***

## Terminal Manipulation with ttymanip.h

This is a new library (that's already being entirely reworked)
that I anticipate I will be using fairly often.
