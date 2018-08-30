#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

class Player
{
   public:
      // At the beginning of the game, the parameter 'callCost' is zero.
      // Valid responses are:
      // * folding (returning a negative value),
      // * betting (returning a positive value).
      // It is not permitted to return 0 in this case.
      //
      // When the game is in progress, the parameter 'callCost' is the value
      // the player must pay to stay in the game.
      // Valid responses are:
      // * folding (returning a negative value),
      // * calling (returning a value equal to 'callCost',
      // * raising (returning a value larger than 'callCost'.
      // It is not permitted to return a value between 0 and 'callCost'-1 in this case.
      //
      // The 'bank' contains the amount of money left in your account.
      // If a player bets more than he has in the 'bank' then this is considered ALL-IN,
      // and both players bets are reduced to match the smaller 'bank' value.
      //
      // The 'pot' contains the current amount of money on the table.
      // This is the amount of money credited your account, if your
      // opponent folds.
      //
      // The 'myCard' contains a value between 0 and 12, where 0 is the worst card,
      // and 12 is the best card.
      //
      virtual unsigned bet(int myCard, unsigned callCost, unsigned bank, unsigned pot) = 0;

      virtual std::string name() const = 0;
}; // end of class Player

#endif // _PLAYER_H_

