# Bluff

This program holds a round-robin tournament of different bots playing against
each other one-on.one. The game played is a dumbed.down version of poker.

# Rules of the game
A round is played by two players only.  Each player starts a 'match' with 100
credits. A match consists of a number of 'rounds'. The players keep playing
rounds until one player runs out of credits.  This ends the match between the
two players.

A round starts by the players being dealt a single card each (values 0 to 12).
Both players must pay 1 credit to start the round.

The players take turns betting. This is done by paying a number of credits to
the pot. Possible betting options are:
* FOLD. This loes the current round, and the opponent gets the pot.
* CALL. Ends the round. Whichever play has the highest card wins and receives
  the pot. If the two cards are equal, the pot is left unchanged.
* RAISE. Forces the opponent to pay more credits to stay in the round.
* CHECK. Forfeits the move. (Only valid on the first bet of a round)

Note: The total amount of credits remains constant throughout a match.
Therefore, when one player has lost, the other player owns all the credits.½
