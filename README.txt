2017 Caltech CS 2
NP-Compete
Karthik Karnik, Ray Sun
15 March 2017

##### CONTRIBUTIONS #####


##### IMPROVEMENTS #####

To improve our AI for the tournament, we implemented an alpha-beta-pruning
search based off of our previous minimax work. For the heuristic, we replaced
the naive heuristic with a composite one calculated by adding weighted
scores for the number of stones (the old naive heuristic), mobility, and
a base heuristic value for each square on the board. Additionally, we added a 
simple endgame strategy by checking whether we are in the endgame (when the number
of remaining squares is less than some cutoff threshold) and utilizing different
weight values in such a case, where the number of stones we possess is heavily
emphasized over mobility or inherent square heuristics.
