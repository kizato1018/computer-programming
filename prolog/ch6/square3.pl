square3 :- write('Please input square size N: '), read(N),( N =:= 0, !; write('Please input symbol S: '), get(S), sq(N, N, S), square3).
sq(_, 0, _) :- !.
sq(N, C, S) :- C > 0, stars(N, S), nl, C1 is C-1, sq(N, C1, S).
stars(0, _) :- !.
stars(N, S) :- N > 0, put(S), N1 is N-1, stars(N1, S).

| ?- square3.
Please input square size N: 5.
Please input symbol S: %
%%%%%
%%%%%
%%%%%
%%%%%
%%%%%
Please input square size N: 6.
Please input symbol S: G
GGGGGG
GGGGGG
GGGGGG
GGGGGG
GGGGGG
GGGGGG
Please input square size N: 0.

yes