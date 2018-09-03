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
   TRACE("Starting new game" << std::endl);

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
      playOneRound(players, banks, pot, startingPlayer);

      TRACE("Current status: banks[0]=" << banks[0] << ", banks[1]=" <<
            banks[1] << ", pot=" << pot << std::endl << std::endl);

      startingPlayer = 1 - startingPlayer;
   } // end of while (banks[0] > 0 && banks[1] > 0)

   // The game is finished.
   if (banks[0] <= 0)   // Player 0 has lost
      return -1;
   if (banks[1] <= 0)   // Player 1 has lost
      return 1;
   
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

   TRACE("==============================" << std::endl);
   TRACE("Player 0's card: " << cards[0] << ",  Player 1's card: " <<
         cards[1] << std::endl);

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
      TRACE(std::endl << "Player " << curPlayer << "'s turn: callCost=" <<
            callCost << ", banks[0]=" << banks[0] << ", banks[1]=" << banks[1] <<
            ", pot=" << pot << std::endl);

      int bet = players[curPlayer]->bet(cards[curPlayer], callCost,
            banks[curPlayer], pot);
      if (bet < 0)
      {
         TRACE("Player " << curPlayer << " folds" << std::endl << std::endl);

         // Opponent keeps the pot.
         banks[1-curPlayer] += pot;
         pot = 0;
         return; // This round has now ended.
      }

      if (bet == 0 && callCost == 0)
      {
         TRACE("Player " << curPlayer << " is cheating. Trying to call in the first move." << std::endl);
         assert(false);
      }

      if (bet >= 0 && bet < callCost)
      {
         TRACE("Player " << curPlayer << " is cheating. Trying to call without paying enoug money." << std::endl);
         assert(false);
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

      if (bet > banks[curPlayer])
      {
         TRACE("Player " << curPlayer << " goes all in. Pot reduced by " << bet-banks[curPlayer] << std::endl);

         // Player is going ALL-IN
         // Reduce the pot accordingly
         pot -= (bet-banks[curPlayer]);
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
            TRACE("Player 0 WON" << std::endl);

            // Player 0 earns the pot.
            banks[0] += pot;
            pot = 0;
         }
         else if (cards[0] < cards[1])
         {
            TRACE("Player 1 WON" << std::endl);

            // Player 1 earns the pot.
            banks[1] += pot;
            pot = 0;
         }
         TRACE(std::endl);
         // If the cards are the same, just leave the pot.
         break; // Play a new round
      }

      curPlayer = 1-curPlayer;

      // Go back and continue with this round
   } // end of while (true)

} // end of playOneRound

