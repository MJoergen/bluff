#include <vector>
#include "player.h"
#include "player_simple.h"
#include "player_basic.h"
#include "tournament.h"

const int numGames = 1000;

int main()
{

   std::vector<Player *> players;

   players.push_back(new PlayerSimple());
   players.push_back(new PlayerBasic());

   Tournament t(players, numGames);
   
   t.play();

} // end of main


