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
   int startingPlayer = 0;
   std::vector<int> bank({100, 100});
   std::vector<Player*> player({m_p1, m_p2});

   TRACE("Starting new game" << std::endl);

   // The current value of the pot
   int pot = 0;

   // Keep playing until one player runs out of money.
   while (bank[0] > 0 && bank[1] > 0)
   {
      // The players dealt card
      std::vector<unsigned> card({rand()%13U, rand()%13U});

      TRACE("==============================" << std::endl);
      TRACE("Player 0's card: " << card[0] << ",  Player 1's card: " << card[1] << std::endl);

      // The current amount needed to call
      int callCost = 0;

      // Both players must pay 'ante' of 1 unit to the pot
      bank[0] -= 1;
      bank[1] -= 1;
      pot += 2;

      TRACE("Both players ante" << std::endl);

      int curPlayer = startingPlayer;

      // The following while loop plays one round
      while (true)
      {
         TRACE(std::endl << "Player " << curPlayer << "'s turn: callCost=" << callCost <<
               ", bank[0]=" << bank[0] << ", bank[1]=" << bank[1] << ", pot=" << pot << std::endl);

         int bet = player[curPlayer]->bet(card[curPlayer], callCost, bank[curPlayer], pot);
         if (bet < 0)
         {
            TRACE("Player " << curPlayer << " folds" << std::endl << std::endl);

            // Opponent keeps the pot.
            bank[1-curPlayer] += pot;
            pot = 0;
            break; // Go back and play another round.
         }

         if (bet == 0 && callCost == 0)
         {
            TRACE("Player " << curPlayer << " is cheating. Trying to call in the first move." << std::endl);
            return -1; // Player loses immediately
         }

         if (bet >= 0 && bet < callCost)
         {
            TRACE("Player " << curPlayer << " is cheating. Trying to call without paying enoug money." << std::endl);
            return -1; // Player loses immediately
         }

         if (bet > 0 && callCost == 0)
         {
            TRACE("Player " << curPlayer << " bets " << bet << std::endl);
         }
         else if (bet > callCost && callCost > 0)
         {
            TRACE("Player " << curPlayer << " raises " << bet - callCost << std::endl);
         }
         else if (bet == callCost)
         {
            TRACE("Player " << curPlayer << " calls" << std::endl);
         }

         if (bet > bank[curPlayer])
         {
            TRACE("Player " << curPlayer << " goes all in. Pot reduced by " << bet-bank[curPlayer] << std::endl);

            // Player is going ALL-IN
            // Reduce the pot accordingly
            pot -= (bet-bank[curPlayer]);
            bank[1-curPlayer] += (bet-bank[curPlayer]);
            callCost = bank[curPlayer];
            bet = bank[curPlayer];
         }

         // Player pays to the pot.
         bank[curPlayer] -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player has CALL'ed.
            if (card[0] > card[1])
            {
               TRACE("Player 0 WON" << std::endl);

               // Player 0 earns the pot.
               bank[0] += pot;
               pot = 0;
            }
            else if (card[0] < card[1])
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

         curPlayer = 1-curPlayer;

         // Go back and continue with this round
      } // end of while (true)

      TRACE("Current status: bank[0]=" << bank[0] << ", bank[1]=" << bank[1] <<
            ", pot=" << pot << std::endl << std::endl);

      startingPlayer = 1 - startingPlayer;
      // This round has now finished. Go back and give players some new cards
   } // end of while (bank[0] > 0 && bank[1] > 0)

   // The game is finished.
   if (bank[0] <= 0)   // Player 0 has lost
      return -1;
   if (bank[1] <= 0)   // Player 1 has lost
      return 1;
   
   return 0; // This should never happen.
} // end of playOneGame

