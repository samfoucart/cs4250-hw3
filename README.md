# CS4250 Homework 1
## Overview
An animated 3D drone with spinning rotors, the ability to click and drag to change viewing angle, and the ability to shoot a missle with the space bar.

## Installation Instructions
In the project root directory, the most common way to build and run a cmake project is to type:

mkdir build

cd build

cmake ..

make

./hw0



But a makefile is provided in the project build directory just in case. NOTE: The project should be run from the project build directory, NOT the root directory, or else the shaders will not be able to be found, compiled, and linked.

## Usage Instructions
Click and drag to change the viewing angle of the drone.

Push the spacebar to shoot a missle.

Push Q to exit the program.

## Conclusions
Homogeneous transformation matrices were used to translate, rotate, and scale the drone, rotors, and missles. I learned how to send a uniform 4x4 matrix to the GPU and apply it to points. A simple static array of vec4s was used to keep track of all the points. A cube was drawn out originally, then the transformation matrices are changed, and the original array is drawn again but translated, scaled, or rotated.

Since the project uses orthographic viewing and does not implement hidden surface removal, it was very difficult to keep track of where the rotors were on the drone. They would appear to phase in and out of the body and each other. The rotors would appear to be on different vertices, then when rotated, it would be difficult to return to the original orientation. This issue became much less noticable once the launcher was attached to the bottom of the drone. It was a much more unique shape that was easy to keep track of and tell whether it was pointing forwards or backwards. The missle launcher did highlight another problem of orthographic viewing though. When the missles are shot towards or away from the screen, they do not get bigger or smaller. It gives the appearance that the missles are hitting some sort of surface very close to the drone, but they aren't. The missles do make it relatively far away from the drone, but they don't seem like it because they don't change size.

