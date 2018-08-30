#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include <vector>
#include <unordered_map>
#include "player.h"

class Tournament
{
public:
   Tournament(const std::vector<Player *> & players, int numGames) : 
      m_players(players),
      m_totals(players.size()),
      m_table(players.size(), std::vector<float>(players.size())),
      m_numGames(numGames)
   {
   }

   void play();

   void showTable();
   void show();

private:
   std::vector<Player *> m_players;
   std::vector<int> m_totals;
   std::vector<std::vector<float> > m_table;
   std::unordered_map< std::string, std::pair< std::string, int > > m_biggest_competitor;
   int m_numGames;
};

#endif // _TOURNAMENT_H_

