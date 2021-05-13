jump(X/Y, S) :- member(X, [1,2,3,4,5,6,7,8]), member(Y, [1,2,3,4,5,6,7,8]), jp(X/Y, S).
jp(X/Y, X1/Y1) :- 
    member(Dx, [-2,-1,1,2]), member(Dy, [-2,-1,1,2]), 3 =:= abs(Dx)+abs(Dy), X1 is X+Dx, Y1 is Y+Dy, member(X1, [1,2,3,4,5,6,7,8]), member(Y1, [1,2,3,4,5,6,7,8]).
knightpath([_]).
knightpath([J1, J2| Others]) :- jump(J1, J2), knightpath([J2| Others]). 