# CodeGen

CodeGen is a simple C code generator. It pick a random version of a function to build an unique project.

## Synopsis

```bash
./codeGen [-l|--list] [--no-flag]... [--force-flag]... project_name
```

Option **-l** will display the list of all the available projects, located in *projects*.  
Each function has some flag defined. You can avoid some functions by using the appropriate **--no-flag**. However, you can force the use of a flag with the appropriate **--force-flag**.  
The generating project will be located in **target/project_name/**.

## CodeGen standard functions

They are located in *sources*. The name of the file is the name of the function you have to use in the rest of your code. It will be automatically replaced.  
Each function must have a name looking like **__codeGen__NAME** to avoid any conflict.  
Before each version of the function, A comment of this form is mandatory:

```c
/* function flag1 flag2... */
```

The keyword **function** is parsed by the generator to recognize the beginning of a function. The flags are those described above.  
If the function need some special include , they have to be specified in a comment after the prototype of the function, but in the same line.

## CodeGen projects

A project is divided in two directories:
- *files*, that contain the project's files, with the names of the functions that will be replaced. It correspond to the the name of the file in **CodeGen** will search the sources. Only lines which start by **__codeGen__** will be replaced.
- *sources*, that contain sources specific to the project. They use the same format as the CodeGen standard functions described above. If some sources of the CodeGen standard functions doesn't correspond to your project, you can replace them by putting your own ones in this directory.

### Author

Emeraude
