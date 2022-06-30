# Blocky Falls
My own take on "Falling columns of matching objects"

To build under Linux or OSX using SDL 1.2, run
$make -f Makefile.SDL1

To build under OSX (using SDL 2.0), run
$make -f Makefile.OSX

And why not use SDL 2.0 straight away? Emscripten makes it easier to port SDL1.
And why the strange architecture? This was a attempt to make it easier to port
to Android. I still have to sort it out a little better - but I do believe it 
will make it easier to port games to Android NDK.


How to play:
As the "frugal" title screen appears, just the press "Play" to start.
Clicking on matches should break the blocks and join the columns. Once the last
column reaches the red area, it's game over (and you're redirected to the title
screen after clicking the screen).

To request a new column to appear, just press space (or any other key).
To quit, press "q" from the game screen.

Unfortunately, this was a incredible rush and I wish I could give this game more
time. I know I can do better than this.
I know there are memory leaks due to cyclic dependencies and lots of inefficient
copies (since some things aren't using std::move) and thrashing due to the 
smart pointers doing their job. Again, I wish I could give it more time.

One thing I was really eager to try was to make things testable - I even tried to 
add support for CppUnit, but the architecture wasn't clear enough for me on how
to achieve it. Before the animations, things were a little simpler and easier. But
rather boring.
