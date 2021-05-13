add_end(X, [], [X]).
add_end(X, [A| L], [A| L1]) :- add_end(X, L, L1).