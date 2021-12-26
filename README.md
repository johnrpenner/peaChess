# peaChess ©2021 by John Roland Penner
Simple Recursive Chess Engine written in C++


--| peaChess version 3.4 Readme |----- 

peaChess ©2021 by John Roland Penner

peaChess is a simple pedagogical chess engine written in C++ which should be easily comprehensible to anyone interested in getting started with chess programming — and provides an old-school terminal style ASCII interface which runs nicely in a 80x24 terminal window. use the ? command to get Help. prefix moves with a . for example: .e2e4 to make your first move then respond with: .e7e5 — if you dont enter anything at all, the peaBrain assumes you want it to make a move, and begins its recursive computation — and this can take a long time, since unlike pChess 2.0, there is no timer interupt support — you have to recurse all the way to the depths, even if it takes twenty minutes! therefore — the default DEPTH is set to: 3. set it exponentally higher. it will perform poorly but fast at the default depth of 3, it will play nominally at depth 5, and will run at about 1550 ELO when the depth is set to 7 (if you enable the quiescenceSearch() in the code!!). 

i wrote the first code for this C++ version of the peaBrain on december 10, 2011. the entire codebase is a functional port of an earlier chess engine i had written in 2010 in futureBasic called pChess 2.0 — which is still more advanced in its use of hash tables and support for fischer random chess than the C++ engine. 

peaChess 3.4 stands in the mid-point of development from the original (and more functionally complete) version of pChess 2.0 — and peaBrain5 — which was a total rewrite in Swift, and is used in my commercial Chess Meister product for the iPad and iPhone. 

pChess 2.0 came both with a graphical interface which allowed sound and graphic visualization of the moves as they were being processed by negamax as part of an iMac art installation, and also featured a UCI interface (which the C++ version lacks). implementation of a UCI interface still needs to be ported from pChess 2.0. 

over christmas i saw that i still had a functioning C++ chess engine sitting around, and  it compiles on macOS and Ubuntu Linux — check it out fellow nerds. if you run a terminal — compile this puppy with: 
 
g++ pea34.cpp -o p34

and see if you can beat the peabrain!  merry christmas 2021! 🎅🏻 

john roland penner


--| HISTORY peaBrain 1-5 |----- 

> Development Timeline: 
	| 2009 - pChess 1.0
	| 2010 - pChess 2.0; dropFour
	| 2011 - pChess UCI; port to C++
	| 2012 - pea3.4 C++ commandline; [freeSpace]
	| 2013 - peaBrain 4.3 C++ engine
	| 2014 - Chess Meister 1.0
	| 2015 - NEX4 1.0; [OMM elisa clone]
	| 2016 - Music Invaders 1.0
	| 2016 - peaBrain5 Swift Chess Engine
	| 2017 - Chess Meister II for iPhone
	| 2018 - Hnefatafl 0.9.0
	| 2021 - pea3 C++ commandline > GitHub


--| THANKS |----------------------------------------------

- Papa Penner Sr. for Games of Real Chess. 
- Robert Purves for Mentoring and Recursion. 
- Gregory Steiner and Brendan Ferguson for help with Code. 

