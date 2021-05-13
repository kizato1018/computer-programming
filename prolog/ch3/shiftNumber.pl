add_end(X, [], [X]).
add_end(X, [A| L], [A| L1]) :- add_end(X, L, L1).
shiftNumber(L, 0, L).
shiftNumber([X|L1], N, L) :- P is N-1, add_end(X, L1, L2), shiftNumber(L2, P, L).