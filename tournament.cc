#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <functional>
#include "tournament.h"
#include "match.h"

void Tournament::play()
{
   for (size_t p1=0; p1<m_players.size(); ++p1)
   {
      for (size_t p2=p1+1; p2<m_players.size(); ++p2)
      {
         Match match(m_players[p1], m_players[p2]);
         int res = match.play(m_numGames);

         if (m_biggest_competitor.find(m_players[p1]->name()) == m_biggest_competitor.end() || //If player one has not played a game before
               m_biggest_competitor[m_players[p1]->name()].second > res) { // If player two was a bigger competitor
            m_biggest_competitor[m_players[p1]->name()] = std::pair<std::string, int>(m_players[p2]->name(), res);
         }

         if (m_biggest_competitor.find(m_players[p2]->name()) == m_biggest_competitor.end() || //If player two has not played a game before
               m_biggest_competitor[m_players[p2]->name()].second > -res) { // If player one was a bigger competitor
            m_biggest_competitor[m_players[p2]->name()] = std::pair<std::string, int>(m_players[p1]->name(), -res);
         }

         if (res > 0)
            std::cout << "The winner is " << m_players[p1]->name() << " with " << res << " points";
         else if (res < 0)
            std::cout << "The winner is " << m_players[p2]->name() << " with " << -res << " points";
         else
            std::cout << "The match ended in a DRAW!";
         std::cout << std::endl;
         std::cout << std::endl;

         m_table[p1][p2] =  res / (float) m_numGames;
         m_table[p2][p1] = -res / (float) m_numGames;

         m_totals[p1] += res;
         m_totals[p2] -= res;
      }
   }
} // end of play

void Tournament::show()
{
   // Make a map of player score and player name
   std::multimap<int, std::string, std::greater<int> > result;
   for (size_t p1=0; p1<m_players.size(); ++p1)
   {
      result.insert(std::pair<int, std::string>(m_totals[p1], m_players[p1]->name()));
   }

   for (auto& line : result)
   {
      std::cout << std::setw(15) << line.second << " : "
         << std::setw(5) << line.first
         << " | Biggest competitor: " << m_biggest_competitor[line.second].first
         << "(" << m_biggest_competitor[line.second].second << ")" << std::endl;
   }

   std::cout << std::endl;

} // end of show

#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

void Tournament::showTable()
{
   // Make a map of player score and player number
   std::multimap<int, int, std::greater<int> > result;
   for (size_t p1=0; p1<m_players.size(); ++p1)
   {
      result.insert(std::pair<int, int>(m_totals[p1], p1));
   }

   for (auto& row : result)
   {
      int playerNumber = row.second;

      std::cout << std::setw(15) << m_players[playerNumber]->name() << " : ";

      for (auto& col : result)
      {
         int opponentNumber = col.second;

         if (playerNumber != opponentNumber)
            std::cout << std::setw(4) << round(m_table[playerNumber][opponentNumber]*100.0) << " ";
         else
            std::cout << "   . ";
      }
      std::cout << " : " << round(m_totals[playerNumber]*100.0/m_numGames) << std::endl;
   }

   std::cout << std::endl;
} // end of showTable

