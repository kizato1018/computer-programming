square1(N) :- sq(N, N).
sq(_, 0) :- !.
sq(N, C) :- C > 0, stars(N), nl, C1 is C-1, sq(N, C1).
stars(0) :- !.
stars(N) :- N > 0, write(*), N1 is N-1, stars(N1).



| ?- square1(1).
*

yes
| ?- square1(0).

yes
| ?- square1(5).
*****
*****
*****
*****
*****

yes