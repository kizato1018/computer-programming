add_end(X, [], [X]).
add_end(X, [A| L], [A| L1]) :- add_end(X, L, L1).
shiftNumber(L, 0, L).
shiftNumber([X|L1], N, L) :- P is N-1, add_end(X, L1, L2), shiftNumber(L2, P, L).   
ms(L, N, N, L).
ms(L, Num, N, _) :- N1 is N+1, shiftNumber(L, N1, L2), ms(L, Num, N1, L2). 
minshiftN(List, N) :- shiftNumber(List, 1, L1), ms(List, N, 1, L1).
