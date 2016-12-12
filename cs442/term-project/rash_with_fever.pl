%
% Rash with Fever diagnosis
% Conner Turnbull
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Rules

blotches :- write('Do you have any red spots or blotches? (y./n.)\n'),
  read(Input), Input = 'y' -> one_of_three, !;
  Input = 'n' -> blisters, !.

one_of_three:- write('Do you have two or more of the following symptoms?\n + runny nose\n + sore red eyes\n + dry cough (y./n.)\n'),
  read(Input), Input = 'y' -> write_measles, !;
  Input = 'n' -> swelling, !.

swelling :- write('Is there any abnormal swelling down the sides of your neck or at the base of your skull? (y./n.)\n'),
  read(Input), Input = 'y' -> write_german_measles, !;
  Input = 'n' -> blisters, !.

blisters :- write('Do you have raised red and itchy spots that turn into blisters? (y./n.)\n'),
  read(Input), Input = 'y' -> write_chickenpox, !;
  Input = 'n' -> rash, !.

rash :- write('Do you have a rash of purple spots? (y./n.)\n'),
  read(Input), Input = 'y' -> one_of_four, !;
  Input = 'n' -> write_no_diagnosis, !.

one_of_four :- write('Do you have two or more of the following symptoms?\n + vomiting\n + headache\n + dislike of strong light\n + pain when trying to bend your head forward (y./n.)\n'),
  read(Input), Input = 'y' -> write_emergency, !;
  Input = 'n' -> write_physician, !.

write_measles :- write('You may have MEASLES, p. 699, especially if the rash is mainly on your face or trunk, or a similar viral infection.\nSee also Visual aids to diagnosis, 26, p. 239.\n').
write_german_measles :- write('You may have GERMAN MEASLES, p. 699.\nSee also Visual aids to diagnosis, 27, p. 239.\n').
write_chickenpox :- write('This may be CHICKENPOX, p. 700.\nSee also Visual aids to diagnossi, 28, p. 239.\n').
write_emergency :- write('EMERGENCY\nGet medical help now!\nThese symptoms suggest the possibility of MENINGITIS, p. 273.\n').
write_physician :- write('Call your physician now!\nYou may have a serious disorder, ALLERGIC PURPURA, p. 681.\n').
write_no_diagnosis :- write('If you are unable to make a diagnossi from this chart, consult your physician.\n').

start :- blotches.
