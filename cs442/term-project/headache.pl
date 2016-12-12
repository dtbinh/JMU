%
% Headache diagnosis
% Conner Turnbull
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Rules

temperature :- write('Is your temperature 100 degrees F or above? (y./n.)\n'),
  read(Input), Input = 'y' -> severe_pain, !;
  (Input = 'n' -> injured_head, !).

severe_pain :- write('Is the pain severe? (y./n.)\n'),
  read(Input), Input = 'y' -> bend_painful, !;
  Input = 'n' -> write('Headaches are a common symptom of feverish illnesses.\nSee chart 5 (Fever).\n').

injured_head :- write('Have you injured your head within the past few days? (y./n.)\n'),
  read(Input), Input = 'y' -> drowsy_vomit, !;
  (Input = 'n' -> nauseated_vomit, !).

bend_painful:- write('Is it painful to bend your head forward AND/OR does light hurt your eyes? (y./n.)\n'),
  read(Input), Input = 'y' -> write('Call your physician now!\nThis suggests the possibility of an infection of the membranes around the brain.\nSee MENINGITIS, p.273\n');
  Input = 'n' -> write('Headaches are a common symptom of feverish illnesses.\nSee chart 5 (Fever).\n').

drowsy_vomit :- write('Are you feeling unusually drowsy AND/OR have you felt nauseated or been vomiting? (y./n.)\n'),
  read(Input), Input = 'y' -> write('EMERGENCY\nGet medical help now!\nThis suggests the possibility of a brain hemorrhage.\nSee EXTRADURAL HEMORRHAGE, p.272.\n');
  Input = 'n' -> write('A persistent headache is common following a head injury.\nSee BRAIN INJURY, p. 276.\n').

nauseated_vomit :- write('Have you felt nauseated or been vomiting (y./n.)\n'),
  read(Input), Input = 'y' -> pain_blurred, !;
  Input = 'n' -> medicine, !.

pain_blurred :- write('Do you have severe pain in and around one eye AND is your vision in that eye blurred? (y./n.)\n'),
  read(Input), Input = 'y' -> write('Call your physician now!\nThis suggests the possibility of raised pressure inside the eye.\nSee ACUTE GLAUCOMA, p. 320.\n');
  Input = 'n' -> one_of_three, !.

one_of_three :- write('Do you have one or more of the following symptoms?\n + pain when you bend your head forward\n + dislike of bright light\n + drowsiness or confusion (y./n.)\n'),
  read(Input), Input = 'y' -> write('EMERGENCY\nGet medical help now!\nThese symptoms suggest the possibility of a brain hemorrhage.\nSee SUBARACHNOID HEMORRHAGE, p. 271.\n');
  Input = 'n' -> pain_relieved, !.

pain_relieved :- write('Was the pain preceded by disturbed vision or relieved by vomiting? (y./n.)\n'),
  read(Input), Input = 'y' -> write('You may have a MIGRAINE, p.285.\n');
  Input = 'n' -> similar_headache, !.

similar_headache :- write('Have you had a similar headache on waking several days out of the past week or more? (y./n.)\n'),
  read(Input), Input = 'y' -> alcohol, !;
  Input = 'n' -> medicine, !.

alcohol :- write('Do the headaches only occur when you have drunk a lot of alcohol the night before? (y./n.)\n'),
  read(Input), Input = 'y' -> write('You probably have a hangover. See HEADACHE, p. 284.\n');
  Input = 'n' -> write('Consult your physician.\nDo not delay!\nSuch headaches may be a symptom of tension or HIGH BLOOD PRESSURE, p. 382, but in very rare cases may indicate a BRAIN TUMOR, p. 282.\n').

medicine :- write('Are you currently taking any medicines? (y./n.)\n'),
  read(Input), Input = 'y' -> write('Some drugs can cause headaches. Discuss with your physician.\n');
  Input = 'n' -> nose, !.

nose :- write('Have you recently had or do you now have a runny or stuffy nose? (y./n.)\n'),
  read(Input), Input = 'y' -> dull_tenderness, !;
  Input = 'n' -> tense_stress, !.

dull_tenderness :- write('Do you have dull pain and tenderness around the eyes and cheek-bones that worsens when you bend forwards? (y./n.)\n'),
  read(Input), Input = 'y' -> write('You may have an infection of the sinuses.\nSee SINUSITIS, p. 347.\n');
  Input = 'n' -> write('Headache is a common symptom of a COLD, p. 342.\n').

tense_stress :- write('Are you feeling tense or under stress AND/OR are you sleeping poorly? (y./n.)\n'),
  read(Input), Input = 'y' -> write('Anxiety often causes headaches.\nSee ANXIETY, p. 300, and HEADACHE, p. 284.\n');
  Input = 'n' -> reading_work, !.

reading_work :- write('Did the headache occur after you had been reading or doing close work such as sewing? (y./n.)\n'),
  read(Input), Input = 'y' -> write('Strain on your neck muscles may have caused the headache.\nSee HEADACHE, p. 284.\n');
  Input = 'n' -> one_of_four, !.

one_of_four :- write('Did any of the following apply in the 12 hours before the headache started?\n + you were exposed to strong sunlight\n + you were in stuffy, smoky or noisy surroundings\n + you drank more alcohol than usual\n + you missed a meal (y./n.)\n'),
  read(Input), Input = 'y' -> write('Headaches are often brought on by such circumstances, and are usually no cause for concern.\nSee HEADACHE, p. 284.\n');
  Input = 'n' -> write('If you are unable to make a diagnosis from this chart and the headache persists overnight or if you develop other symptoms, consult your physician.\n').

start :- temperature.
