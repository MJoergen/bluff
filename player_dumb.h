#ifndef _PLAYER_DUMB_H_
#define _PLAYER_DUMB_H_

#include "player.h"

// This is a very simple and dumb player. It pays absolutely no attention to the value
// of his own card!!!
class PlayerDumb : public Player
{
   public:
      unsigned bet(int myCard __attribute__((unused)), unsigned callCost, unsigned bank, unsigned pot __attribute__((unused)))
      {
         if (callCost == 0)
         {
            // It is the beginning of the game.
            // Always bet 10 % of my current bank.
            return (bank+9)/10;   // Make sure value is not zero.
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

      std::string name() const {return "DUMB";}
}; // end of class PlayerDumb

#endif // _PLAYER_DUMB_H_

