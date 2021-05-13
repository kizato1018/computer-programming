add_end(X, [], [X]).
add_end(X, [A| L], [A| L1]) :- add_end(X, L, L1).

reverse1([], []).
reverse1([X|List], ReverseList) :- reverse1(List, SubList), add_end(X, SubList, ReverseList).