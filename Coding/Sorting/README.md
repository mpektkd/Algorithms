## Car Rental
We are going to rent a car and travel by road from the city of Sort to the city of Selection for
the Binary Search algorithm birthday party. The road connecting the cities is a long distance D kilometers.

Between the cities, there are intermediate stations which are the only places
where one can refuel one's car.
In particular, station _j_ is located _dj_ km from the city of Selection.

Let's say that our hero, called Dimitris, arrived late at the car rental office and is planning his trip to the 
city of Selection, in order to catch the start of the party, in exactly _T_ minutes.

For your trip, you will rent one of the N available cars. Each car _i_ is characterized by the rental cost _p<sub>i</sub>_ and its capacity
in fuel _c<sub>i</sub>_. All the cars have two modes:
 - the economic one:
   - they cover a kilometer in _T<sub>s</sub>_ minutes and the consumption of _C<sub>s</sub>_ liters per km
 - sport one:
   - they cover one kilometer in _T<sub>f</sub>_ <_T<sub>s</sub>_ minutes and fuel consumption _C<sub>f</sub>_> _C<sub>s</sub>_
     liters of fuel per kilometer.
     
The switching time from one mode of operation to another is zero and the driver can change as many times as he wants the
operation of his vehicle.

Dimitris loves sport and is in a hurry to get to his destination, but he wants to be sure that he will not run out of
fuel in the middle of the road.

You should help Dimitris and to write a program that calculates the minimum cost of renting a car that can cover the
distance between the cities in no more than _T_ minutes. 

**Input Data**:
The program will initially read from the standard input four positive integers:
 - the number N of the available ones
 - the number K of the intermediate stations
 - the distance D of the cities in kilometers
 - the time margin T 
 
In each of the remaining N lines:
 - _p<sub>i</sub>_: the rental cost of car _i_ ( > 0 )
 - _c<sub>i</sub>_: the capacity of car _i_ ( > 0 )
  

In the next line, there will be _K_ integers _d<sub>1</sub>_ , ..., _d<sub>k</sub>_ that correspond to the distances (in km) of the stations
inbetween from the original city of Sort. 

In the last line of the input, there will be four positive integers _T<sub>s</sub>_, _C<sub>s</sub>_, _T<sub>f</sub>_, _C<sub>f</sub>_
that correspond to the time performance and consumption of the input economic and sporty pace of operation instead.

**Output Data**: 
The program must print in the standard output an integer, the minimum cost
of renting a car that can cover the distance from the city of Sorting to the city of Selection in
time no bigger than T minutes. In case there is no such car, the program must print -1.

**Notes**: 
 - The numbering of cars is arbitrary, while there may be cars _i_ and _j_ where _p<sub>i</sub>_ > _p<sub>j</sub>_ and _c<sub>i</sub>_ < _c<sub>j</sub>_.
 - The numbering of intermediate stations is arbitrary (ie the intermediate stations are not necessarily numbered in ascending or descending
   distance from the city of Selection), while there may be _i_ ≠ _j_ stations with _d<sub>i</sub>_ = _d<sub>j</sub>_. 

## Teleports
Morty stole Rick's portal gun to impress Jessica. But, without noticing, he was teleported to
another parallel universe.

We know that _M<sub>i</sub>_, Morty of universe _I_, teleported to universe _c<sub>i</sub>_ in _{1, ..., Ν}_.
After all these unfortunate teleports, we continue to have a single Morty in each of the _N_ parallel universes 
(i.e. the sequence _c_ = (_c<sub>1</sub>_ , ..., _c<sub>N</sub>_) is a transposition of _{1, …, N}_).

However, _M_ portals were left open between some universies which two Mortys can use to exchange worlds.
Each open portal _j_ connects two parallel universes _a<sub>j</sub>_ , _b<sub>j</sub>_ , has width _w<sub>j</sub>_ and
can be used infinite times. The Mortys must return to the correct universes (ie restore the _c_ sequence to its original form) before the
Ricks notice!

The Mortys are grumpy in all _N_ universies and don’t want to get crammed into open portals that are narrow. 

Write a program that helps the Mortys return comfortably to their (correct) parts, ie. to
restore the _c_ sequence to its original form, calculating the maximum width of the narrowest
portal they need to use for this purpose.

**Input Data**:
At first, read from the standard input two positive integers:
- the number N of the parallel universes 
- the number M of portals that have been left opened

In the next line, a transposition _c_ = _(_c<sub>1</sub>_ , …, _c<sub>N</sub>_)_ of the set _{1, …, N}_ is given,
in which _c<sub>i</sub>_ indicates the parallel universe that Morty of the _i_<sup>th</sup>_ universe ended up in.

In the next M lines, _M_ triads of natural numbers are given, which indicate the portals that
have been left opened. To be more precise, each open portal _j_ is described by 3 natural
numbers:

 - the first universe _a<sub>j</sub>_
 - the second universe _b<sub>j</sub>_
 - the corresponding width _w<sub>j</sub>_


**Output Data**:
Your program must print in the standard output a natural number, that
describes the maximum width of the narrowest portal that needs to be used, so the input
sequence _c_ = _(_c<sub>1</sub>_ , …, _c<sub>N</sub>_)_ can be restored in its initial form. In all given inputs, the sequence _c_
will be able to be restored to its initial form.
