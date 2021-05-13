trianglestars(N, S) :- tell('trianglefile.txt'), tri(N, S), told.
tri(0, _) :- !.
tri(N, S) :- N > 0, N1 is N - 1, tri(N1, S), stars(N, S), nl.
stars(0, _) :- !.
stars(N, S) :- N > 0, write(S), N1 is N-1, stars(N1, S).

| ?- trianglestars(3,1).

yes
1
11
111
| ?- trianglestars(5,&).

yes
&
&&
&&&
&&&&
&&&&&

| ?- trianglestars(10,0).

yes
0
00
000
0000
00000
000000
0000000
00000000
000000000
0000000000
