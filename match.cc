#include <iostream>
#include <string>
#include "assert.h"
#include "match.h"

int Match::play(int numGames)
{
   std::cout << "Playing match between " << m_p1->name() << " and "
      << m_p2->name() << std::endl;

   int sum = 0;
   for (int g=0; g<numGames; ++g)
   {
      sum += playOneGame();
   } // end of for

   return sum;
} // end of play

int Match::playOneGame()
{
   // The players current bank accounts
   int bank1 = 100;
   int bank2 = 100;

   // Keep playing until one player runs out of money.
   while (bank1 > 0 && bank2 > 0)
   {
      // The players dealt card
      unsigned card1 = rand() % 13;
      unsigned card2 = rand() % 13;

      // The current value of the pot
      int pot = 0;
      // The current amount needed to call
      int callCost = 0;

      // Both players must pay 'ante' of 1 unit to the pot
      bank1 -= 1;
      bank2 -= 1;
      pot += 2;

      // The following while loop plays one round
      while (true)
      {
         int bet = m_p1->bet(card1, callCost, bank1, pot);
         if (bet < 0)
         {
            // Player 1 fold. Player 2 keeps the pot.
            bank2 += pot;
            pot = 0;
            break; // Go back and play another round.
         }

         if (bet == 0 && callCost == 0)
         {
            std::cerr << "Player 1 is cheating. Trying to call in the first move." << std::endl;
            return -1; // Player 1 loses immediately
         }

         if (bet >= 0 && bet < callCost)
         {
            std::cerr << "Player 1 is cheating. Trying to call without paying enoug money." << std::endl;
            return -1; // Player 1 loses immediately
         }

         if (bet > bank1)
         {
            // Player 1 is going ALL-IN
            // Reduce the pot accordingly
            pot -= (bet-bank1);
            bank2 += (bet-bank1);
            callCost -= (bet-bank1);
            bet = bank1;
         }

         // Player 1 pays to the pot.
         bank1 -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player 1 has CALL'ed.
            if (card1 > card2)
            {
               // Player 1 earns the pot.
               bank1 += pot;
               pot = 0;
            }
            else if (card1 < card2)
            {
               // Player 2 earns the pot.
               bank2 += pot;
               pot = 0;
            }
            // If the cards are the same, just leave the pot.
            break; // Play a new round
         }


         bet = m_p2->bet(card2, callCost, bank2, pot);
         if (bet < 0)
         {
            // Player 2 fold. Player 1 keeps the pot.
            bank1 += pot;
            pot = 0;
            break; // Go back and play another round.
         }

         if (bet == 0 && callCost == 0)
         {
            std::cerr << "Player 2 is cheating. Trying to call in the first move." << std::endl;
            return 1; // Player 2 loses immediately
         }

         if (bet >= 0 && bet < callCost)
         {
            std::cerr << "Player 2 is cheating. Trying to call without paying enoug money." << std::endl;
            return 1; // Player 2 loses immediately
         }

         if (bet > bank2)
         {
            // Player 2 is going ALL-IN
            // Reduce the pot accordingly
            pot -= (bet-bank2);
            bank1 += (bet-bank2);
            callCost -= (bet-bank2);
            bet = bank2;
         }

         // Player 2 pays to the pot.
         bank2 -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player 2 has CALL'ed.
            if (card2 > card1)
            {
               // Player 2 earns the pot.
               bank2 += pot;
               pot = 0;
            }
            else if (card2 < card1)
            {
               // Player 1 earns the pot.
               bank1 += pot;
               pot = 0;
            }
            // If the cards are the same, just leave the pot.
            break; // Play a new round
         }

         // Go back and continue with this round
      } // end of while (true)

      // This round has now finished. Go back and give players some new cards
   } // end of while (bank1 > 0 && bank2 > 0)

   // The game is finished.
   if (bank1 <= 0)   // Player 1 has lost
      return -1;
   if (bank2 <= 0)   // Player 2 has lost
      return 1;
   
   return 0; // This should never happen.
} // end of playOneGame

