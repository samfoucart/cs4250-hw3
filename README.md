# CS4250 Homework 3 - Space Exploration
## Overview
Explore a randomly generated solar system. 
The player is able to control a spaceship from a third person perspective to explore.



## Installation Instructions
In the project root directory, the most common way to build and run a cmake project is to type:

mkdir build

cd build

cmake ..

make

./hw3



But a makefile is provided in the project build directory just in case. 
NOTE: The project should be run from the project build directory, NOT the root directory, or else the shaders will not be able to be found, compiled, and linked.

## Usage Instructions
w - move forward

a - turn left

d - turn right

s - pitch down

space - pitch up

q - exit program

## Conclusions
I implemented this project with an abstract class called Drawable for each object. 
A spaceship object then inherits from the drawable. The spaceship is made of a cone, a cylinder, and two spheres.
Rectangular wings were originally going to be put on the space ship, 
but I chose not to in order to save a couple minutes working on the project.

The spaceship is controlled with normal wasd controls. 
The position of the spaceship is incremented every time the user pushes a key.
Originally, the spaceship was going to have velocity just like the asteroids,
but the camera was unable to track it.
I created a separate camera class just for it, but every time I would pass the information from the space ship,
the function would read them in as 0 no matter what. It was very strange.
I think it's because the std::unique_ptr was creating a new object from scratch instead of just letting me access it.

I learned about the OpenGL glBufferSubData command more than anything else. 
The biggest, most complicated piece of this project was getting multiple different shapes to be on screen at the same time.
