square1(N) :- T is N*N, sq(T, N).
sq(0, _).
sq(T, N) :- T > 0, (mod(T, N) =:= 0, T =:= N, nl); write(*), T1 is T-1, sq(T1, N).
test(A, B) :- mod(T, N) =:= 1.