# ITP2 - Homework 2. Lev Kozlov BS20-03

## Task implementation:

### Difference between previous homework:

1. new "blue" level of access for guests
1. "emergency" button for simulation added for all users. All users can toggle emergency button 
and enable access for ALL rooms in university
1. "disable emergency" action for admin. Only admin can disable emergency in case when everything is okay.

#### Changes in simulation:
1. Now it displays before each room or user its type. Helps for better understanding and testing.
2. Added 4 guests with special property: purpose of visiting.

## Evething later is the same as in the previous homework

### In my system there is the following hierarchy of access:

1. "no_level" - access only to ClassRoom
1. "green" - access to LabCabinet, ClassRoom, LectureRoom
1. "yellow" - access to ClassRoom, LectureRoom, ConferenceRoom, Cabinet
1. "red" - access to all rooms

If a person wants to access some room, the system checks if his level of access is higher or equal to level of access of
room. LabCabinet and Cabinet are special rooms, so person should be in list of granted_users to have access even if
their level is higher.

### By default users have these levels of access:

1. Student - `yellow`
1. Professor - `yellow`
1. Director - `yellow`
1. LabEmployee - `green`
1. Admin - `red`

In current system there are several rooms (cabinet for each professor, robotics laboratory, software development
laboratory, conference room, lecture room and one study room) which can be extended later.

## Environment description

I use Ubuntu 20.04 and `g++ --version` gives such an output:

`
g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 Copyright (C) 2019 Free Software Foundation, Inc. This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
`

## Project running:

You have to be in directory `hw2` and execute `g++ main.cpp && ./a.out`
Then you may just follow instruction from your terminal.

## User-interaction description

On each step of interaction you will be asked to input an integer from parenthesis `(idx)`. This will guide you through
available actions.

Short description of available actions:

1. You should select user from the list you will be given If you have selected an admin (Andrew Korobov or Nikita Takov)
   you should enter the password which is ```gde_stipa```
2. After this you will see list of actions you can do:
    1. ```exit (stop simulation)``` - you will simply end execution of this program
    1. ```change user``` - you will return to step ```1```
    1. ```access to certain room``` - you will be given a list of rooms in building and can try to access them. If your
       attempt was unsuccessful (access denied), you will see the message.
    1. ```get user name and surname``` - you will refresh who you are
    1. ```get user property``` - you will see property of current user (description of each property is inside class
       description)
    1. ```get user level``` - you will see level of access of current user
    1. ```grant access``` - (available only for admin users) For this action you should select pair (```user```, ```room```) to
       grant ```user``` an access to ```room```