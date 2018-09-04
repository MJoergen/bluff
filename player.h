#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

class Player
{
   public:
      // At the beginning of the game, the parameter 'callCost' is zero.
      // Valid responses are:
      // * folding (returning a negative value),
      // * checking (returning zero).
      // * betting (returning a positive value).
      //
      // When the game is in progress, the parameter 'callCost' is the value
      // the player must pay to stay in the game.
      // Valid responses are:
      // * folding (returning a negative value),
      // * calling (returning a value equal to 'callCost',
      // * raising (returning a value larger than 'callCost'.
      // It is not permitted to return a value greater than 0 and but less than
      // 'callCost' in this case.
      //
      // The 'credits' contains the number of credits you have at your disposal.
      // If a player bets more than he has available credits, then this is
      // considered ALL-IN, and both players bets are reduced to match the
      // smaller 'credits' value.
      //
      // The 'pot' contains the current amount of money on the table.
      // This is the number of credits credited your account, if you win this round.
      //
      // The 'myCard' contains a value between 0 and 12, where 0 is the worst card,
      // and 12 is the best card.
      //
      virtual unsigned bet(int myCard, unsigned callCost, unsigned credits, unsigned pot) = 0;

      virtual std::string name() const = 0;

      virtual ~Player() {}
}; // end of class Player

#endif // _PLAYER_H_

