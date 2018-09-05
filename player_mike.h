#ifndef _PLAYER_MIKE_H_
#define _PLAYER_MIKE_H_

#include "player.h"

// This is a very basic player. It is not very smart, and it is
// only intended to beat the even dumber player DUMB.
template <int cutoff>
class PlayerMike : public Player
{
   public:
      unsigned bet(int myCard, unsigned callCost, unsigned bank, unsigned pot __attribute__((unused)))
      {
         // Estimate how likely we are to win,
         // based on the value of our card.
         bool willWeWin = (rand()%13) < myCard;

         // If opponent has bet/raised, then assume the opponent has a high card.
         if (callCost > 0)
         {
            willWeWin = (myCard > cutoff);
         }

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

      std::string name() const {return "MIKE_" + std::to_string(cutoff);}
}; // end of class PlayerMike

#endif // _PLAYER_MIKE_H_

