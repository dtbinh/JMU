%
% Module 16 PA
% Conner Turnbull
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Facts

% spouse(X,Y) is symmetric
spouse(mary,edward).
spouse(edward,mary).
spouse(mike,terry).
spouse(terry,mike).
spouse(gail,phil).
spouse(phil,gail).
spouse(ethel,tom).
spouse(tom,ethel).
spouse(john,ann).
spouse(ann,john).
spouse(edith,larry).
spouse(larry,edith).
spouse(jean,frank).
spouse(frank,jean).
spouse(tina,tim).
spouse(tim,tina).
spouse(andrea,molly).
spouse(molly,andrea).

male(bill).
male(edward).
male(john).
male(phil).
male(chuck).
male(tom).
male(mike).
male(barry).
male(carl).
male(dennis).
male(larry).
male(frank).
male(jack).
male(brian).
male(tim).
male(josh).
male(zach).
male(orem).
male(harry).
male(travis).

% Parents are biological parents
% parents(X,Y,Z) is read X has parents Y and Z.
parents(john,bill,mary).
parents(kelly,bill,mary).
parents(gail,mary,edward).
parents(ethel,mary,edward).
parents(mike,mary,edward).
parents(barry,john,ann).
parents(carl,john,ann).
parents(dennis,john,ann).
parents(edith,john,ann).
parents(jean,gail,phil).
parents(jack,gail,phil).
parents(brian,gail,phil).
parents(maggie,grace,chuck).
parents(tina,chuck,ethel).
parents(edna,mike,terry).
parents(molly,mike,terry).
parents(nina,edith,larry).
parents(orem,edith,larry).
parents(harry,jean,frank).
parents(tricia,tina,tim).
parents(travis,tina,tim).
parents(sarah,zach,molly).
parents(cathy,josh,edna).

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Rules

% Anyone who is not a male is a female (this makes unknown people female)
female(X) :- \+male(X).
test_female :- female(mary), female(edith), \+female(travis), female(zeus).

% A parent is either one of a person's biological parents
% parent(X,Y) is read X has parent Y
parent(X,Y) :- parents(X,Y,_).
parent(X,Y) :- parents(X,_,Y).
test_parent :- parent(tricia,tina), parent(tricia,tim),
		\+parent(tricia,chuck), \+parent(X,X), \+parent(mary,_).

% A father is a male biological parent
% father(X,Y) is read X has father Y
father(X,Y) :- parent(X,Y),male(Y).
test_father :- father(tricia,tim), \+father(tricia,tina),
		\+father(X,X), \+father(mary,_), \+father(_,mary).

% A mother is a female biological parent
% mother(X,Y) is read X has mother Y
mother(X,Y) :- parent(X,Y), female(Y).
test_mother :- mother(tricia,tina), \+mother(tricia,tim),
		\+mother(X,X), \+mother(mary,_), \+mother(_,edward).

% A step father is a non-biological parent who is a male spouse of a biological parent
% step_father(X,Y) is read X has step_father Y
step_father(X,Y) :- male(Y), spouse(Y,Z), parent(X,Z), \+parent(X,Y).
test_step_father :- step_father(tina,tom), \+step_father(tina,chuck),
			\+step_father(X,X), \+step_father(_,andrea),
			\+step_father(ethel,_).

% A step parent is a non-biological parent of a spouse of a biological parent
% step_parent(X,Y) is read X has step_parent Y
%step_parent(X,Y) :- spouse(Y,Z), parent(X,Z), \+parent(X,Y).
test_step_parent :- step_parent(kelly,edward), step_parent(sarah,andrea),
			\+step_parent(tina,grace), \+step_parent(X,X),
			\+step_parent(_,mary), \+step_parent(mary,_).

% Siblings are distinct people who share a biological parent
% sibling(X,Y) is symmetric
sibling(X,Y) :- parent(X,Z), parent(Y,Z), X \== Y.
test_sibling :- sibling(tricia,travis), sibling(kelly,ethel),
		sibling(tina,maggie), \+sibling(harry,_), \+sibling(X,X).

% A sister is a female sibling
% sister(X,Y) is read X has sister Y
sister(X,Y) :- sibling(X,Y), female(Y).
test_sister :- sister(travis,tricia), sister(mike,kelly),
		\+sister(X,X), \+sister(harry,_), \+sister(tricia,travis).

% An aunt is a sister of a parent or the female spouse of a sibling of a parent
% aunt(X,Y) is read X has aunt Y
aunt(X,Y) :- parent(X,A), sister(A,Y); parent(X,A), sibling(A,B), spouse(B,Y), female(Y).
test_aunt :- aunt(tina,kelly), aunt(tina,gail), aunt(cathy,andrea),
		\+aunt(X,X), \+aunt(sarah,andrea), \+aunt(_,john), \+aunt(mary,_).

% A grandparent is a biological parent of a biological parent
% grandparent(X,Y) is read X has grandparent Y
grandparent(X,Y) :- parent(X,Z), parent(Z,Y).
test_grandparent :- grandparent(travis,ethel), grandparent(dennis,bill),
			\+grandparent(X,X), \+grandparent(tricia,tom),
			\+grandparent(ethel,_).

% A grandfather is a male grandparent
% grandfather(X,Y) is read X has grandfather Y
grandfather(X,Y) :- grandparent(X,Y), male(Y).
test_grandfather :- grandfather(tricia,chuck), grandfather(tina,edward),
			\+grandfather(X,X), \+grandfather(ethel,_),
			\+grandfather(_,mary).

% An ancestor is the transitive closure of biological parenthood
% ancestor(X,Y) is read X has ancestor Y
ancestor(X,Y) :- parent(X,Y); parent(X,Z), ancestor(Z,Y).
test_ancestor :- ancestor(tricia,mary), ancestor(orem,bill), \+ancestor(tricia,bill),
			\+ancestor(X,X), \+ancestor(tom,_), \+ancestor(_,tom).

% A (blood) relative of a person is anyone else that is either an ancestor, has a common
% ancestor, or is a descendant of the person; nobody is a relative of themselves
% relative(X,Y) is read X has relative Y
relative(X,Y) :- ancestor(X,Y).
relative(X,Y) :- ancestor(Y,X).
relative(X,Y) :- ancestor(X,Z), ancestor(Y,Z), X \== Y.
test_relative :- relative(ethel,tricia), relative(ethel,nina), relative(molly,harry),
			relative(mary,orem), \+relative(X,X), \+relative(tim,phil),
			\+relative(tom,_).

% An in-law of a person is any relative of that person's spouse that is not their relative
% in_law(X,Y) is read X has in-law Y
in_law(X,Y) :- spouse(X,Z), relative(Z,Y), \+relative(X,Y).
test_in_law :- in_law(tom,carl), in_law(andrea,harry),
		\+in_law(X,X), \+in_law(andrea,josh), \+in_law(mike,_).

test :- test_female, test_parent, test_father, test_mother, test_step_father, 
	test_sibling, test_sister, test_aunt, test_grandparent, test_grandfather,
	test_ancestor, test_relative, test_in_law, !.
