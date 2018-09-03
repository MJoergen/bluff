#ifndef _MATCH_H_
#define _MATCH_H_

#include "player.h"

class Match
{
   public:
      Match(Player *p1, Player *p2) :
         m_p1(p1),
         m_p2(p2)
      {}

      int play(int numGames);

   private:
      int playOneGame();

      void playOneRound(const std::vector<Player*>& players, 
            std::vector<int>& banks, int& pot, int startingPlayer);

      Player *m_p1;
      Player *m_p2;

}; // end of class Match

#endif // _MATCH_H_

