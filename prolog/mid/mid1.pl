conc([], L, L).
conc([X|L1], L2, [X|L3]) :- conc(L1, L2, L3). 
pconstruction(List, Plist) :- reverse(List, RL), conc(List, RL, Plist).