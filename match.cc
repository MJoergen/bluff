#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "match.h"
#include "trace.h"

// This plays a match between the two players, consisting of a number
// of independent games.
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

// This plays a single game between the two players. Both players are given
// an initial bank credit, and the game continues until one player runs 
// out of credit.
int Match::playOneGame()
{
   TRACE(std::endl);
   TRACE(std::endl);
   TRACE("============================" << std::endl);
   TRACE("Starting new game" << std::endl);
   TRACE("============================" << std::endl);
   TRACE(std::endl);

   std::vector<Player*> players({m_p1, m_p2});

   // The players current bank accounts
   std::vector<int> banks({100, 100});

   // The current value of the pot
   int pot = 0;

   // This is the player to make the first action in the next round.
   int startingPlayer = 0;

   // Keep playing until one player runs out of credit.
   while (banks[0] > 0 && banks[1] > 0)
   {
      TRACE(std::endl << std::endl);
      TRACE("Current credis: " << players[0]->name() << "=" << banks[0] <<
            ", " << players[1]->name() << "=" << banks[1] <<
            ", pot=" << pot << std::endl);

      playOneRound(players, banks, pot, startingPlayer);

      startingPlayer = 1 - startingPlayer;
   } // end of while (banks[0] > 0 && banks[1] > 0)

   // The game is finished.
   if (banks[0] <= 0)   // Player 0 has lost
   {
      return -1;
   }
   if (banks[1] <= 0)   // Player 1 has lost
   {
      return 1;
   }
   
   return 0; // Should never happen
} // end of playOneGame

// This plays a single round between the two players.
// See README.md for a description of the rules. See also
// https://en.wikipedia.org/wiki/Betting_in_poker for a description
// of the source of inspiration.
void Match::playOneRound(const std::vector<Player*>& players, 
      std::vector<int>& banks, int& pot, int startingPlayer)
{
   // The players dealt card
   std::vector<unsigned> cards({rand()%13U, rand()%13U});

   TRACE("+++++++++++++++++++++++++++++++++++++++" << std::endl);
   TRACE("" << players[0]->name() << "'s card: " << cards[0] <<
         ",  " << players[1]->name() << "'s card: " <<
         cards[1] << std::endl);

   // True if the current player has not made any action yet.
   std::vector<bool> firstAction({true, true});

   // The current amount needed to call
   int callCost = 0;

   // Both players must pay 'ante' of 1 unit to the pot
   banks[0] -= 1;
   banks[1] -= 1;
   pot += 2;

   TRACE("Both players ante" << std::endl);

   int curPlayer = startingPlayer;

   // The following while loop plays one round
   while (true)
   {
      TRACE(std::endl << players[curPlayer]->name() << "'s turn: callCost=" <<
            callCost << ", credits=" << banks[curPlayer] <<
            ", pot=" << pot << std::endl);

      // Get action from player
      int bet = players[curPlayer]->bet(cards[curPlayer], callCost,
            banks[curPlayer], pot);
      if (bet < 0)
      {
         TRACE("" << players[curPlayer]->name() << " folds." << std::endl);

         // Opponent keeps the pot.
         banks[1-curPlayer] += pot;
         pot = 0;
         return; // This round has now ended.
      }
      else if (bet == 0)
      {
         TRACE("" << players[curPlayer]->name() << " checks." << std::endl);

         // This is only allowed on the first round
         if (!firstAction[curPlayer])
         {
            TRACE("" << players[curPlayer]->name() << " is cheating: " <<
                  "Checking is only allowed on the first move." << std::endl);
            assert(false);
         }

         if (callCost > 0)
         {
            TRACE("" << players[curPlayer]->name() << " is cheating: " <<
                  "Checking is not allowed when there is a bet made already" <<
                  std::endl);
            assert(false);
         }
      }
      else // bet > 0
      {
         if (callCost == 0)
         {
            TRACE("" << players[curPlayer]->name() << " bets " << bet <<
                  "."  << std::endl);
         }
         else if (bet == callCost)
         {
            TRACE("" << players[curPlayer]->name() << " calls." << std::endl);
         }
         else if (bet > callCost)
         {
            TRACE("" << players[curPlayer]->name() << " raises " << bet-callCost <<
                  "."  << std::endl);
         }
         else
         {
            TRACE("" << players[curPlayer]->name() << " is cheating: " <<
                  "Trying to call without paying enough money." << std::endl);
            assert(false);
         }

         if (bet > banks[curPlayer])
         {
            TRACE("" << players[curPlayer]->name() << " goes all in. " <<
                  "Pot reduced by " << bet-banks[curPlayer] << std::endl);

            // Player is going ALL-IN
            // Reduce the pot accordingly
            pot                -= (bet-banks[curPlayer]);
            banks[1-curPlayer] += (bet-banks[curPlayer]);

            callCost = banks[curPlayer];
            bet = banks[curPlayer];
         }

         // Player pays to the pot.
         banks[curPlayer] -= bet;
         pot += bet;

         // Calculate the new value to pay for a call.
         callCost = bet - callCost;

         if (callCost == 0)
         {
            // Player has CALL'ed.
            if (cards[0] > cards[1])
            {
               // Player 0 earns the pot.
               TRACE("" << players[0]->name() << " wins the pot." << std::endl);

               banks[0] += pot;
               pot = 0;
            }
            else if (cards[0] < cards[1])
            {
               // Player 1 earns the pot.
               TRACE("" << players[1]->name() << " wins the pot." << std::endl);

               banks[1] += pot;
               pot = 0;
            }
            else
            {
               TRACE("Cards match. Pot remains." << std::endl);
            }

            // If the cards are the same, just leave the pot.
            return; // Play a new round
         }
      }

      firstAction[curPlayer] = false;
      curPlayer = 1-curPlayer;

      if (!firstAction[0] && !firstAction[1] && callCost == 0)
      {
         TRACE("Both players checked. Dealing new cards." << std::endl);
         return; // Play a new round
      }

   } // end of while (true)

} // end of playOneRound

