conc( [], L, L).
conc( [X| L1], L2, [X| L3]) :- conc( L1, L2, L3).
sort1([], []).
sort1([A], [A]).
sort1([E| U], S) :- qs(A, B, U, E), sort1(A, S1), sort1(B, S2), conc(S1, S2, S).
qs([Key], [], [], Key).
qs([E| A], B, [E| L], Key) :- E =< Key, !, qs(A, B, L, Key).
qs(A, [E| B], [E| L], Key) :- qs(A, B, L, Key).

| ?- sort1([1,2,3,4,5], S).

S = [1,2,3,4,5] ? 

yes
| ?- sort1([7,6,1,2,3,4,5], S).

S = [1,2,3,4,5,6,7] ? 

yes
| ?- sort1([3,1,41,7,15], S).

S = [1,3,7,15,41] ? 

yes