# CS4250 Homework 0
## Overview
The instructions "Choose any of the example programs in /home/cs425/code-egs/lec08 as a
starting point. Make a significant modification to the program" were given. The two dimensional Sierpinsky gasket program was chosen for the project. The project flips the direction of the original structure, it adds in color to the structure, and it allows the user to pan and zoom through the structure.

## Installation Instructions
In the project root directory, the most common way to build and run a cmake project is to type:

mkdir build

cd build

cmake ..

make

cd ..

./build/hw0



But a makefile is provided in the project build directory just in case. NOTE: The project should be run from the project build directory, NOT the build directory, or else the shaders will not be able to be found, compiled, and linked.

## Usage Instructions
To zoom into the structure, press the spacebar. To zoom out of the structure, press the 'b' key on the keyboard. To pan around the structure, click on the part of the structure to focus towards with the mouse.

## Conclusions
I learned a lot about the glUniformxx function because the zoom feature was implemented using a glUniform1f in the vertex shader, and the translation was also implemented as a glUniform2f in the vertex shader. I was initially very confused on the difference between an attribute and a uniform, so I had a giant period of time working on this where I think my zoom was just stuck as a zero value, and I ended up nulling out all of the points that were generated. Once I figured out that I needed a uniform instead of an attribute, this project became much easier.

In hindsight, it would probably be better to make the zoom/translate into a homogeneous matrix transformation. That way it would be much easier to do things like rotations and to make the code more understandable. I didn't do that though because my program was simple enough to not need it.

The code could also benefit from being optimized for memory better. It would be much more interesting if you could zoom in indefinitely and watch the clarity increase and increase and increase. This currently isn't possible because all of the points in the whole program are constantly being stored in memory, and the program doesn't deallocate them, or get rid of them when theyre not on the screen. It also doesn't get rid of the excess once it becomes clear enough that points are more fine than a pixel. That is a whole other can of worms though and outside the scope of this project.
