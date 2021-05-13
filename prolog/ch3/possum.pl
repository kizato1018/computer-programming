possum([], 0, 0).
possum([X|L], N, Sum) :- X > 0, possum(L, P, Y), N is P+1, Sum is X+Y.
possum([X|L], N, Sum) :- X =< 0, possum(L, P, Sum), N is P+1.