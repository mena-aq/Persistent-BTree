## Persistent File-Based Implementation of B-Trees 

This is a module I made as part of my Data Structures Final Project.

It is a file-based implementation of B-Trees, in that the nodes are stored in files rather than memory. Thus, the nodes remain persistent.<br>
Basic functionalities include : adding keys, deleting keys and searching for keys.<br>
Keys are implemented as integer keys along with string records, where duplicate records producing the same key (in our hashing scheme) are also stored.<br>

Furthemore, while researching B-Tree implementations, I noticed most resources used a minimum degree,t, instead of a maximum degree, m. Thus, this issue has been addressed in this module, where keys with odd and even maximum degrees can both be handled.


