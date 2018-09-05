#include <iostream>
#include <vector>
#include "player.h"
#include "player_dumb.h"
#include "player_basic.h"
#include "player_mike.h"
#include "tournament.h"
#include "trace.h"

#ifdef ENABLE_TRACE
std::ostream *gpTrace = 0;
#endif

int numGames = 1000;

int main(int argc, char **argv)
{
   int c;

   while ((c = getopt(argc, argv, "t:n:h")) != -1)
   {
      switch (c)
      {
#ifdef ENABLE_TRACE
         case 't' : gpTrace = new CTrace(optarg); break;
#else
         case 't' : std::cout << "Trace not supported" << std::endl; return 1;
#endif
         case 'n' : numGames = strtol(optarg, (char **) NULL, 10); break;
         case 'h' :
         default : {
                      std::cout <<  "Options:" << std::endl;
                      std::cout << "-t <file> : Trace search to file" << std::endl;
                      std::cout << "-n <num>  : Number of games to play (default 1000)" << std::endl;
                      std::cout << "-h        : Show this message" << std::endl;
                      exit(1);
                   }
      } // end of switch
   } // end of while

   srand(time(0));

   std::vector<Player *> players;

   players.push_back(new PlayerMike<8>());
   players.push_back(new PlayerMike<9>());
   players.push_back(new PlayerMike<10>());
   players.push_back(new PlayerBasic());
   players.push_back(new PlayerDumb());

   Tournament t(players, numGames);
   
   t.play();
   t.show();
   t.showTable();

} // end of main


