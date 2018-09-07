# Bluff

This program holds a round-robin tournament of different bots playing against
each other one-on-one. The game played is a dumbed-down version of poker, where
each player is only dealt one card.

The object of this project is to pitch different bots against each other, and
to experiment with different bot strategies.

# Rules of the game
A 'match' is played by two players only.  Each player starts a match with 100
credits. A match consists of a number of 'rounds'. The players keep playing
rounds until one player runs out of credits.  This ends the match between the
two players.

A round starts by the players being dealt a single card each (values 0 to 12).
Both players must pay 1 credit to start the round.

The players take turns betting. This is done by paying a number of credits to
the pot. Possible betting options are:
* FOLD. This loses the current round, and the opponent gets the pot.
* CHECK. Forfeits the move. Only valid on the first bet of a round, and if the
  other player has not made a bet.
* CALL/ALL-IN. Ends the round. Whichever player has the highest card wins and
  receives the pot. If the two cards are equal, the pot is left unchanged.
* BET/RAISE. Forces the opponent to pay more credits to stay in the round.

Invariant: The total amount of credits remains constant throughout a match.
Therefore, when one player has lost the match, the other player owns all the
credits.

The above rules are inspired by the betting rules for poker described
[here](https://en.wikipedia.org/wiki/Betting_in_poker).

See [here](http://www.firsttimepokerplayer.com/how-to-play/strategy/betting-guide/) for a description of different betting strategies.

