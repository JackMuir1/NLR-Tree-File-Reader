# NLR-Tree-File-Reader
This project reads a txt file and places its values in an avl tree, then prints the tree in NLR Format

The format of the file that is read is as follows:
(a, d, or e)(space)(integer)

The program will read either a for add the subsequent integer to the tree, d for delete the subsequent integer, or e for ending the program.

For example,
a 3
a 10
a 45
d 10
a 9
e

The result will be: 9 3 45

The file path is set to be read from "c:\\temp\\input.txt"

This file path can be changed within the AVL class
