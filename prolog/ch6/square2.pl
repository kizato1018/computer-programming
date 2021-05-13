square2 :- write('Please input square size N: '), read(N), write('Please input symbol S: '), get(S), sq(N, N, S).
sq(_, 0, _) :- !.
sq(N, C, S) :- C > 0, stars(N, S), nl, C1 is C-1, sq(N, C1, S).
stars(0, _) :- !.
stars(N, S) :- N > 0, put(S), N1 is N-1, stars(N1, S).

| ?- square2.
Please input square size N: 3.
Please input symbol S: %
%%%
%%%
%%%

yes
| ?- square2.
Please input square size N: 5.
Please input symbol S: .
.....
.....
.....
.....
.....

(16 ms) yes
| ?- square2.
Please input square size N: 0.
Please input symbol S: a