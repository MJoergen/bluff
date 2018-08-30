#ifndef _PLAYER_SIMPLE_H_
#define _PLAYER_SIMPLE_H_

#include "player.h"

// This is a very simple and dumb player. It pays absolutely no attention to the value
// of his own card!!!
class PlayerSimple : public Player
{
   public:
      unsigned bet(int myCard, unsigned callCost, unsigned bank, unsigned pot)
      {
         if (callCost == 0)
         {
            // It is the beginning of the game.
            // Always bet 10 % of my current bank.
            return bank/10;
         }
         else
         {
            // The game is in progress
            // Choose randomly between CALL, RAISE, and FOLD.

            switch (rand()%3)
            {
               case 0 : // CALL
                  return callCost;
               case 1 : // RAISE
                  // Do we have enough money in the bank?
                  if (callCost <= bank)
                  {
                     // Raise with 10 % of what is left.
                     return callCost + (bank-callCost)/10;
                  }
                  else
                  {
                     return callCost;
                  }
               default : // FOLD
                  return -1;
            }
         }
      }

      std::string name() const {return "SIMPLE";}
}; // end of class PlayerSimple

#endif // _PLAYER_SIMPLE_H_

