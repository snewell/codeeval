# codeeval
This project is simply my solutions (in some cases partial) for the challenges
at CodeEval.  I make no claims that these solutions are ideal or bug-free.

For fun I'm trying to have each solution use `algorithm` whenever possible.

## Building
Run `cmake` with a path to the source tree.  In the interest of being portable
I don't assume what flags will put your compiler in C++11 mode so you'll have
to take care of that.

## Running Tests
Once the build is done run `test.sh` from the root of the build directory.  It
needs a copy of the input and output folders to be local but a symlink is fine.

## Known Issues
* Challenge 48 (Discount Offers) doesn't work.  I need to figure out a
  solution to handle checking for common factors.  Also, my greedy algorithm
  doesn't work so I need to permutate through all possible solutions.
* Challenge 64 (Climbing Stairs) fails on large inputs.  Off the top of my
  head it may be int overflow but I haven't done any investigation.
* Challenge 207 (Which Way is Faster?) is too slow to pass.  It currently
  uses an optimized brute force solution but I need to come up with a more
  intelligent way to find the path.
