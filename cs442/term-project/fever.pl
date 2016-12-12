%
% Headache diagnosis
% Conner Turnbull
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Rules

cough :- write('Do you have a cough? (y./n.)\n'),
  read(Input), Input = 'y' -> short_breath, !;
  Input = 'n' -> headache, !.

short_breath :- write('Are you short of breath even when resting? (y./n.)\n'),
  read(Input), Input = 'y' -> write_pneumonia, !;
  Input = 'n' -> phlegm, !.

phlegm :- write('Have you been coughing up grayish-yellow phlegm, AND/OR have you been wheezing? (y./n.)\n'),
  read(Input), Input = 'y' -> write_bronchitis, !;
  Input = 'n' -> headache_aching, !.

headache_aching :- write('Do you have a headache AND/OR aching joints or bones? (y./n.)\n'),
  read(Input), Input = 'y' -> write_influenza, !;
  Input = 'n' -> headache, !.

headache :- write('Do you have a headache? (y./n.)\n'),
  read(Input), Input = 'y' -> one_of_four, !;
  Input = 'n' -> aching, !.

one_of_four :- write('Do you have one or more of the following symptoms?\n + pain when bending the head forward\n + nausea or vomiting\n + dislike of bright light\n + drowsiness or confusion (y./n.)\n'),
  read(Input), Input = 'y' -> write_meningitis, !;
  Input = 'n' -> vomit_diarrhea, !.

vomit_diarrhea :- write('Have you vomited or had diarrhea? (y./n.)\n'),
  read(Input), Input = 'y' -> write_gastroenteritis, !;
  Input = 'n' -> aching, !.

aching :- write('Do you have aching joints or bones? (y./n.)\n'),
  read(Input), Input = 'y' -> write_influenza, !;
  Input = 'n' -> rash, !.

rash :- write('Do you have a rash? (y./n.)\n'),
  read(Input), Input = 'y' -> write_rash_with_fever, !;
  Input = 'n' -> sore_throat, !.

sore_throat :- write('Do you have a sore throat? (y./n.)\n'),
  read(Input), Input = 'y' -> write_pharyngitis_tonsillitis, !;
  Input = 'n' -> small_back_pain, !.

small_back_pain :- write('Do you have pain in the small of your back on one side just above the waist? (y./n.)\n'),
  read(Input), Input = 'y' -> write_acute_pyelonephritis, !;
  Input = 'n' -> urinate, !.

urinate :- write('Do you have pain when you urinate AND/OR are you urinating more frequently than usual? (y./n.)\n'),
  read(Input), Input = 'y' -> write_cystitis, !;
  Input = 'n' -> sunlight_hot, !.

sunlight_hot :- write('Have you spent most of the day in strong sunlight or in very hot conditions? (y./n.)\n'),
  read(Input), Input = 'y' -> write_sunstroke, !;
  Input = 'n' -> write_no_diagnosis, !.

write_pneumonia :- write('Call your physician now!\nThese symptoms suggest the possibility of PNEUMONIA, p. 359.\n').
write_bronchitis :- write('You may have an infection of the airways in the lung.\nSee ACUTE BRONCHITIS, p. 353.\n').
write_influenza :- write('You may have INFLUENZA, p. 559.\n').
write_meningitis :- write('Call your physician now!\nThese symptoms suggest the possibility of MENINGITIS, p. 273.\n').
write_gastroenteritis :- write('You may have an infection of the digestive tract.\nSee GASTROENTERITIS, p. 459.\n').
write_rash_with_fever :- write('See chart 28: Rash with fever.\n').
write_pharyngitis_tonsillitis :- write('You may have a throat infection. See PHARYNGITIS p. 350, and TONSILLITIS, p. 351.\n').
write_acute_pyelonephritis :- write('You may have a kidney infection. See ACUTE PYELONEPHRITIS, p. 502.\n').
write_cystitis  :- write('You may have a urinary-tract infection. See CYSTITIS, p. 505.\n').
write_sunstroke :- write('You may have a sunstroke or heatstroke. See p. 801 for first aid and consult your physician without delay.\n').
write_no_diagnosis :- write('If you are unable to make a diagnosis from this chart and your temperature has not returned to normal within 24 hours or rises again, consult your physician\n').

start :- cough.
