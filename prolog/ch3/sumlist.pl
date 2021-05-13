sumlist([], 0).
sumlist([X|L], N) :- sumlist(L, Y), N is X+Y.