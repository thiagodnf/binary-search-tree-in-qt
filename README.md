Qt BST OpenGL
======
Binary Search Tree (BST) in Qt and OpenGL

Demo
-----------

http://www.youtube.com/watch?v=35tUnyhhF1U

How to use
-----------
Clone this repo, if you use git:

`git clone https://github.com/thiagodnf/QtBSTOpenGL.git`

If you don't know how to use git, just click on the ZIP button, on top of the page and download the source code as a ZIP file and extract it.

Once you get the code, go to the directory you've created

`cd QtBSTOpenGL`

Now, just run the command 'make', and the 'makefile' will do the compiling work for you:

`QtBSTOpenGL$ make`

If you get some error, please go to the Dependencies section, at the end of this file and download the dependecies of the project.

When the compiling is finished, you should get a file named 'QtBSTOpenGL', just run it:

`QtBSTOpenGL$ ./QtBSTOpenGL`

Cool Features
-----------

All the three main operations of the BST can be done by clicking in the buttons 'Add', 'Search' and 'Remove'.

To clear all nodes in the tree, press the 'Clear' button.

The 'Zoom in' and 'Zoom out' buttons are self explanatory.

Clicking on the 'Axis' button, the three axis (X, Y and Z) will be shown or hidden. This is usefull to realize the positions in the 3D space.

When the 'Random' button is toggled, randomic keys will be generated and inserted in the tree.

The info about the program is avaiable in the 'About' button.

The 'Exit' button closes the program.

There are some nice controllers on the right sidebar pane. 

The 'Information' section shows how many nodes are in the tree. 

In 'Rotate' section is possible to turn the tree around the tree axis. 

The 'Light' pane offers controllers to position the light source of the model, accordingly to the 3 axis.

Authors:
-----------
- Débora Martins (http://twitter.com/dehvmartins)
- Marcos Brizendo (http://about.me/marcosbrizeno)
- Thiago Nascimento (http://thiagodnf.com)

Dependencies:
-----------
`sudo apt-get install qtcreator g++ freeglut3-dev`