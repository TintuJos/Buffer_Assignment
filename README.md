# Assignment 1

In this assignment you are supposed to practice CI in order to develop a module
which has two functions to insert and extract data with a given length in bits and
a given start position to/from a buffer.

## Requirements

1.Make a private repository for the project on github.

2.You need to follow the Github Flow strategy.

3.Use TDD to develop the buffer module. The module shall fully be tested.

4.To build and test your code use make and a Makefile.

5.In Github Actions automate your workflow using

    a.A workflow which only is triggered when you make a pull request from yourfeature branch to the mainline inorder to build and test the module.

    b.A workflow which only is triggered when you push to the mainline in order to build, test and create a release. In the release you shall include the executable test files.

    c.The workflows shall be run on ubuntu and created by yourself.

6.Don’t change the header file of the module and don’t include any library or create new functions in the implementation file.

7.Generalize the Makefile in a way that if we add new modules and tests we don’t need to change the Makefile

8.Instead of having 2 workflows, you shall have only one workflow which is capable of the functionalities in 5.a, 5.b and 5.c
