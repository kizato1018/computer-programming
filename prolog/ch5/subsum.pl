sumlist([], 0).
sumlist([X|L], N) :- sumlist(L, Y), N is X+Y.
ss([], []).
ss([E| L], [E| L1]) :- ss(L, L1).
ss([_| L], L1) :- ss(L, L1).
subsum(L, N, Sub) :- ss(L, Sub), sumlist(Sub, N).

| ?- subsum([1,2,5,3,2], 5, Subset).

Subset = [1,2,2] ? ;

Subset = [2,3] ? ;

Subset = [5] ? ;

Subset = [3,2] ? ;

no
| ?- subsum([1,2,5,3,2], 8, Subset).

Subset = [1,2,5] ? ;

Subset = [1,2,3,2] ? ;

Subset = [1,5,2] ? ;

Subset = [5,3] ? ;

(15 ms) no

| ?- subsum([1,2,5,3,2], A, [_,_,_]).

A = 8 ? ;

A = 6 ? ;

A = 5 ? ;

A = 9 ? ;

A = 8 ? ;

A = 6 ? ;

A = 10 ? ;

A = 9 ? ;

A = 7 ? ;

A = 10 ? ;

(31 ms) no