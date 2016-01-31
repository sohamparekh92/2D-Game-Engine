// Brian Malloy        Game Construction
#include "manager.h"

int main(int, char*[]) {
   try {
     // Manager manager;
     // manager.play();
      Manager* manager;
      do
      {
       manager = new Manager();
       manager->play();
      }while(manager->getRestart());
   delete manager;
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
