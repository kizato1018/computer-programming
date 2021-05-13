del_all(_, [], []).
del_all(X, [X| L], L1) :- del_all(X, L, L1).
del_all(X, [Y| L], [Y| L1]) :- del_all(X, L, L1).