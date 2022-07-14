# TreeManager
### Task for the DSA course @ FMI.

Write a program that works with trees having arbitrary branching. 

The nodes are random **integers** and can be repeated in the tree. 
The only restriction is that a node _cannot_ have two direct descendants with the same value.

The program must be able to load trees and assign names to them. 
The _time complexity_ of finding a tree by its name should be no more than **O(k)**,
where k is the length of the longest tree name loaded into the program.

#### Commands


- **LOAD _name_ _file_**

    Reads a tree from a text file and stores it in memory, giving it a name.
    
    If an attempt is made to load a tree with an existing name, _overwrites_ the old tree.


- **SAVE _name_ _file_**

    Saves the tree _name_ in _file_. 


- **CONTAINS _tree1_ _tree2_**

    Checks if the _tree2_ is a subtree of _tree1_. 


- **REMOVE _tree1_ _tree2_**

    Removes every occurrence of _tree2_ in _tree1_.