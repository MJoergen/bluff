#include <iostream>
#include <string>
#include <vector>
#include "assert.h"
#include "match.h"
#include "trace.h"

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
   int startingPlayer = 1;
   std::vector<int> bank({0, 100, 100});

   TRACE("Starting new game" << std::endl);

   // Keep playing until one player runs out of money.
   while (bank[1] > 0 && bank[2] > 0)
   {
      // The players dealt card
      std::vector<unsigned> card({0, rand()%13U, rand()%13U});

      TRACE("==============================" << std::endl);
      TRACE("Player 1: " << card[1] << ",  Player 2: " << card[2] << std::endl);

      // The current value of the pot
      int pot = 0;
      // The current amount needed to call
      int callCost = 0;

      // Both players must pay 'ante' of 1 unit to the pot
      bank[1] -= 1;
      bank[2] -= 1;
      pot += 2;

      TRACE("Both players ante" << std::endl);

      int curPlayer = startingPlayer;

      // The following while loop plays one round
      while (true)
      {
         TRACE(std::endl << "Player 1's turn: callCost=" << callCost << ", bank1=" << bank[1] <<
            ", bank2=" << bank[2] << ", pot=" << pot << std::endl);

         int bet = m_p1->bet(card[1], callCost, bank[1], pot);
         if (bet < 0)
         {
            TRACE("Player 1 folds" << std::endl << std::endl);

            // Player 1 fold. Player 2 keeps the pot.
            bank[2] += pot;
            pot = 0;
            break; // Go back and play another round.
         }

         if (bet == 0 && callCost == 0)
         {
            TRACE("Player 1 is cheating. Trying to call in the first move." << std::endl);
            return -1; // Player 1 loses immediately
         }

         if (bet >= 0 && bet < callCost)
         {
            TRACE("Player 1 is cheating. Trying to call without paying enoug money." << std::endl);
            return -1; // Player 1 loses immediately
         }

         if (bet > 0 && callCost == 0)
         {
            TRACE("Player 1 bets " << bet << std::endl);
         }
         else if (bet > callCost && callCost > 0)
         {
            TRACE("Player 1 raises " << bet - callCost << std::endl);
         }
         else if (bet == callCost)
         {
            TRACE("Player 1 calls" << std::endl);
         }

         if (bet > bank[1])
         {
            TRACE("Player 1 goes all in. Pot reduced by " << bet-bank[1] << std::endl);

            // Player 1 is going ALL-IN
            // Reduce the pot accordingly
            pot -= (bet-bank[1]);
            bank[2] += (bet-bank[1]);
            callCost = bank[1];
            bet = bank[1];
         }

         // Player 1 pays to the pot.
         bank[1] -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player 1 has CALL'ed.
            if (card[1] > card[2])
            {
               TRACE("Player 1 WON" << std::endl);

               // Player 1 earns the pot.
               bank[1] += pot;
               pot = 0;
            }
            else if (card[1] < card[2])
            {
               TRACE("Player 2 WON" << std::endl);

               // Player 2 earns the pot.
               bank[2] += pot;
               pot = 0;
            }
            TRACE(std::endl);
            // If the cards are the same, just leave the pot.
            break; // Play a new round
         }

         TRACE(std::endl << "Player 2's turn: callCost=" << callCost << ", bank1=" << bank[1] <<
            ", bank2=" << bank[2] << ", pot=" << pot << std::endl);

         bet = m_p2->bet(card[2], callCost, bank[2], pot);
         if (bet < 0)
         {
            TRACE("Player 2 folds" << std::endl << std::endl);

            // Player 2 fold. Player 1 keeps the pot.
            bank[1] += pot;
            pot = 0;
            break; // Go back and play another round.
         }

         if (bet == 0 && callCost == 0)
         {
            TRACE("Player 2 is cheating. Trying to call in the first move." << std::endl);
            return 1; // Player 2 loses immediately
         }

         if (bet >= 0 && bet < callCost)
         {
            TRACE("Player 2 is cheating. Trying to call without paying enoug money." << std::endl);
            return 1; // Player 2 loses immediately
         }

         if (bet > 0 && callCost == 0)
         {
            TRACE("Player 2 bets " << bet << std::endl);
         }
         else if (bet > callCost && callCost > 0)
         {
            TRACE("Player 2 raises " << bet - callCost << std::endl);
         }
         else if (bet == callCost)
         {
            TRACE("Player 2 calls" << std::endl);
         }

         if (bet > bank[2])
         {
            TRACE("Player 2 goes all in. Pot reduced by " << bet-bank[2] << std::endl);

            // Player 2 is going ALL-IN
            // Reduce the pot accordingly
            pot -= (bet-bank[2]);
            bank[1] += (bet-bank[2]);
            callCost = bank[2];
            bet = bank[2];
         }

         // Player 2 pays to the pot.
         bank[2] -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player 2 has CALL'ed.
            if (card[2] > card[1])
            {
               TRACE("Player 2 WON" << std::endl);

               // Player 2 earns the pot.
               bank[2] += pot;
               pot = 0;
            }
            else if (card[2] < card[1])
            {
               TRACE("Player 1 WON" << std::endl);

               // Player 1 earns the pot.
               bank[1] += pot;
               pot = 0;
            }
            TRACE(std::endl);
            // If the cards are the same, just leave the pot.
            break; // Play a new round
         }

         // Go back and continue with this round
      } // end of while (true)

      TRACE("Current status: bank1=" << bank[1] <<
         ", bank2=" << bank[2] << std::endl << std::endl);

      // This round has now finished. Go back and give players some new cards
   } // end of while (bank[1] > 0 && bank2 > 0)

   // The game is finished.
   if (bank[1] <= 0)   // Player 1 has lost
      return -1;
   if (bank[2] <= 0)   // Player 2 has lost
      return 1;
   
   return 0; // This should never happen.
} // end of playOneGame

