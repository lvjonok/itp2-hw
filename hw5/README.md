# ITP2 - Homework 5. Lev Kozlov BS20-03

## Task implementation:

All examples are placed in ```main.cpp```. Unlike the previous homework, I made login function more reasonable.

## Files description - only differences between previous homework

1. ```System.h``` - has gained AdminGateway class capable for managing admins decisions on changing permissions.
1. ```drivers.csv``` - now may contain multiple cars separated by ":".
1. ```Car.h``` - has gained property `validated` which can say whether a car was approved or not.
1. ```Passenger.h``` - has gained property `on a ride` which can tell whether he is already riding or not.
1. ```Admin.h``` - Core of Admin class who is capable for managing permissions in system.
1. ```Permission.h``` - Class of permissions for system. Also contains classes for Exceptions which can be thrown.
1. ```admins.csv``` - database for storing serialized Admin classes.
1. ```permissions.csv``` - database for storing serialized Permission classes.

## Environment description

I use Ubuntu 20.04 and `g++ --version` gives such an output:

`
g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 Copyright (C) 2019 Free Software Foundation, Inc. This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
`

## Project running:

You have to be in directory `hw4` and execute `g++ main.cpp && ./a.out`
Then you may just follow instruction from your terminal.
