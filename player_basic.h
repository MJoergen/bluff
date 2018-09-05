#ifndef _PLAYER_BASIC_H_
#define _PLAYER_BASIC_H_

#include "player.h"

// This is a very basic player. It is not very smart, and it is
// only intended to beat the even dumber player DUMB.
class PlayerBasic : public Player
{
   public:
      unsigned bet(int myCard, unsigned callCost, unsigned bank, unsigned pot __attribute__((unused)))
      {
         // Estimate how likely we are to win,
         // based on the value of our card.
         bool willWeWin = (rand()%13) < myCard;

         if (!willWeWin)
         {
            // Our card is pretty small, so just give up. Don't want to lose
            // any more money.
            return -1;  // FOLD
         }
         else
         {
            // We have a good card!

            // Do we have enough money in the bank?
            if (callCost <= bank)
            {
               // Bet/raise half of what we have left.
               return callCost + (bank-callCost)/2;
            }
            else
            {
               return callCost;
            }
         }
      }

      std::string name() const {return "BASIC";}
}; // end of class PlayerBasic

#endif // _PLAYER_BASIC_H_

