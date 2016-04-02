# command-line-list

**list** is a simple command line application for keeping a list of anything relevant to you. It can be a todo list, a bucket list, or even a list of your favorite flavors of ice cream!

To get **list** setup on your UNIX machine, complete the following steps:

1. in your home directory, create a file named `.profile` if one does not already exist.

2. similarly, create a file named `.bash_aliases` if one does not exist.

3. in .profile, add the line `source ~/.bash_aliases`. This will tell your machine to read that file when you start up your terminal.

4. in `list.c`, alter the lines containing the path to the file named `list_save`. Make sure the new path you enter is relative to your home directory.

5. Restart Terminal

6. Navigate within Terminal to the directory holding the source code for list. Enter the command `make` to build the executable. 

7. list should now be accessible from anywhere within your directory. In Terminal, enter `list` to check if it is working.

Notes: A save file `.list_save`, with all of the list data, is stored in the same directory as the source and executable files.
