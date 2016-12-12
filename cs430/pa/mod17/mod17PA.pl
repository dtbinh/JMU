%
% Hopscotch game: Imagine a version of hopscotch played on a linear course with markers in each square
% representing points. The goal is to hop through the course once, collecting a marker at each spot, to
% maximize the collected points. But there is a constraint: on each hop you must skip the next square or the
% next two squares. Hence from position i, the possible next position is either i+2 or i+3.
%
% Predicate hopscotch(X,R) is true if X is a list of integers representing score markers in the course and 
% R is a sequence of markers that leads to a maximum sequence of hops. Note that this predicate is expected
% to be used with a particular list for X and a variable or a list for R.
%
% This assignment is borrowed from Margaret Lamb, Queens University Computer Science Department, Ontario.
%
% Conner Turnbull

% hopscotch(X,R) is true if X is a list of numbers and R is the list of values from X that win the hopscotch game.

hopscotch([], []).
hopscotch([X], [X]).
hopscotch([X1,_], [X1]).
hopscotch([X1,_,X3], [X1,X3]).
hopscotch([X1,_,X3|XN],[X1|B]) :- hopscotch([X3|XN],A), hopscotch(XN,B), sum(A,X), sum(B,Y), X=<Y.
hopscotch([X1,_,X3|XN],[X1|B]) :- hopscotch(XN,A), hopscotch([X3|XN],B), sum(A,X), sum(B,Y), X<Y.

sum([], 0).
sum([X|T], S) :- sum(T, R), S is X + R.

%%%%%%%%%%%%%%%%% Tests

test_hopscotch :-
  hopscotch([],[]),
  hopscotch([1],[1]),
  hopscotch([1,2],[1]),
  hopscotch([1,2,3],[1,3]),
  hopscotch([1,2,4,1],[1,4]),
  hopscotch([1,3,2,6,5],[1,2,5]),
  hopscotch([7,4,5,9,6,1,2,3],[7,5,6,3]),
  hopscotch([6,2,4,8,3,2,3,4,3,5,2,5,3,5,9,1],[6,8,2,4,5,5,9]),
  hopscotch([6,2,4,8,3,2,3,4,3,5,2,5,3,5,9,5],[6,8,2,4,5,5,5,5]).

test :- test_hopscotch, !.
