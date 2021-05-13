cube1 :- read( X), process( X).

process( stop) :- !.
process( N) :- C is N * N * N, write( C), cube1.

cube :- read( stop), !.
cube :- read( N), C is N * N * N, write( C), cube.