# ITP2 - Homework 4. Lev Kozlov BS20-03

## Task implementation:

For database implementation I used .csv files. You can find them in ```database``` folder. Also, in this folder there is an implmentation of parser of strings and database operations. As required, You can follow ```main``` function to see that homework is actually done. My assumption was that each driver takes first available ride if it exists.

## Files description

1. ```drivers.csv``` - File contains data with drivers for my system. Format: ```Name/Rating/Status/Car```
1. ```passengers.csv``` - File contains data with passengers for my system. Format: ```Name/Rating/PaymentMethods/PinnedAddresses```
1. ```rides_completed.csv``` - File contains such rides which were already completed. Format: ```AddressFrom/AddressTo/TimeSpent/Price/CarType/Passenger/Driver/NumberOfPaymentMethod```
1. ```rides_pending.csv``` - File contains such rides which were created, but nobody took it. Format is the same as in previous file.
1. ```database.h``` - Tools for operating with ```.csv``` files.
1. ```parser.h``` - Tools for parsing string by delimeter.

1. ```Addresss.h``` - Implementation of Address for System. In my system it is just a string.
1. ```Car.h``` - Implementation of Car for System.
1. ```Order.h``` - Wrapper for part of Ride entries, to store them for each Passenger.
1. ```Ride.h``` - Storage of Ride as in database.
1. ```Time.h``` - Implementation of Time spent for each ride. Simply, random float.
1. ```PaymentMethods.h``` - Implementation of different payment methods. In my system it can be either Card or Cash.
1. ```Passenger.h``` - Implementation of Passenger for System.
1. ```Driver.h``` - Implementation of Driver for System.
1. ```System.h``` - Core of system with 3 classes: ```PassengerGateway```, ```DriverGateway``` as required in task and ```Gateway``` as link between them.

## Environment description

I use Ubuntu 20.04 and `g++ --version` gives such an output:

`
g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 Copyright (C) 2019 Free Software Foundation, Inc. This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
`

## Project running:

You have to be in directory `hw4` and execute `g++ main.cpp && ./a.out`
Then you may just follow instruction from your terminal.
