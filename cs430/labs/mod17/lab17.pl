size([],0).
size([_|T],N) :- size(T,M), N is M+1.

end([],[]).
