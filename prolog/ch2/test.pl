point(1,1).
point(1,2).
point(1,3).
point(2,1).
point(2,2).
point(2,3).
point(3,1).
point(3,2).
point(3,3).

rectangle(point(X1, Y1), point(X1, Y2), point(X2, Y1), point(X2, Y2)).
test(A, B, C, D) :- rectangle(A,B,C,D).