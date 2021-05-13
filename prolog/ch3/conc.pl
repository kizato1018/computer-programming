conc( [], L, L).
conc( [X| L1], L2, [X| L3]) :- conc( L1, L2, L3).
last1(Item, List) :- conc(X, [Item], List).
conc1(L1, L2, L3) :- conc(L2, L1, L3).
