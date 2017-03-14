2017 Caltech CS 2
NP-Compete
Karthik Karnik, Ray Sun
15 March 2017

##### CONTRIBUTIONS #####

Over the past two weeks, we proceeded to complete each step of Part 1 of the 
assignment, in additionwrt to alpha-beta pruning, in concert. We discussed
strategies and implementation details together, and worked on the actual
code together. 

For Part 1, Karthik implemented the random and naive heuristic algorithms.
We then experimented together with various constant-time heuristics (including
the array of scores assigned to each square, and mobility) before implementing
minimax. We separately wrote minimax implementations and then took the better
one (Karthik's). We then each tested the implementation independently, verifying
that the test case was successful and observing that minimax could beat SimplePlayer
and ConstantTimePlayer more often than not.

For Part 2, Ray wrote the alpha-beta-pruning implementation and devised the
essence of the heuristic that we ended up using (weighted # stones + weighted
mobility + weighted square value). Karthik then refined these weights from
strategies that we discovered online, and implemented an endgame case within
the alpha-beta-pruning method. We then tuned our AI separately to empirically
find the best heuristics.


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
