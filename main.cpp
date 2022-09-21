#include "Abbie/abbie.hpp"
#include <sstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

std::string getModelString(int i) {
   std::stringstream ss;
   ss << "models/model_" << i << ".csv";
   return ss.str();
}

bool getTrainingMode() {
   std::string response = "";
   std::cout << "Training mode (y/n): ";
   while (!(response == "y" || response == "n")) {
      if (response != "") {
         std::cout << "Invalid response. Training mode (y/n): ";
      }
      std::cin >> response;
      std::cout << "\033[F\33[2K"; // clear previous line
   }
   if (response == "y") {
      return true;
   } else {
      return false;
   }
}

int findModelMumber() {
   std::string path = "models";
   std::vector<int> iterations;
   for (const auto & entry : fs::directory_iterator(path)) {
      std::string pathstring = entry.path().string();
      pathstring = pathstring.substr(pathstring.find('_') + 1, pathstring.find('.'));
      iterations.push_back(std::stoi(pathstring));
   }
   if (iterations.size() != 0) {
      std::sort(iterations.begin(), iterations.end());
      return iterations.back();
   }
   std::stringstream outpath;
   Abbie bot;
   bot.saveModel(getModelString(0));
   return 0;
}



int main(int argc, char**argv) {
   bool training_mode;
   if (argc > 2) {
      std::cout << "Usage: opt [TRAINING_MODE(y/n)]\n";
      exit(0);
   }
   if (argc == 1) {
      training_mode = getTrainingMode();
   }
   if (argc == 2) {
      if (argv[1][0] == 'y') {
         training_mode = true;
      } else if (argv[1][0] == 'n') {
         training_mode = false;
      } else {
         std::cout << "Usage: opt [TRAINING_MODE(y/n)]\n";
         exit(0);
      }
   }
   int i = findModelMumber();

   if ( training_mode ) {
      Board board;
      Abbie bot(getModelString(i));
      
      int epoch_length = 500;
      std::cout<< "\n";

      while (true)
      {
         i++;
         std::cout << "Game " << i;
         bot.trainOneGame();
         if (i % epoch_length == 0)  {
            bot.saveModel(getModelString(i));
         }
      }
   } else {
      Abbie bot(getModelString(i));
      bot.playAgainst();
   }

   return 0;
}
