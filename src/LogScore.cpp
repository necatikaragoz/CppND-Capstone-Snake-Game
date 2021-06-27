/*
    This file wirte score the file and feth from the file.
*/

#include <LogScore.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <cstdio>



//Constructor
    //CheckScorefileIsExist
        //get scores
//Destructor

//GetHighestScore
    //ReadFromFile

//GetScores
//WriteScore

/*

*/

using std::string;

void LogScore::UpdateHighestScore(int score)
{
  if(score > mHighestScore)
  {

    mHighestScore = score;
    
    string line;
    string key;
    string value;
    std::ifstream inputFile(kScorePath);
    std::ofstream modifiedFile(kScoretempPath);

    int lines = 0;
    int maxlines = 0;

    if (inputFile.is_open()) 
    {
      while (std::getline(inputFile, line)) 
      {
        string templine = line;
        bool modification = false;

        std::replace(line.begin(), line.end(), ' ', '_');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), '"', ' ');

        std::istringstream linestream(line);

        std::ostringstream outlinestream;

        while (linestream >> key >> value) {

          std::replace(value.begin(), value.end(), '_', ' ');

          if (key == kNames[NE_HighestScore] ) {

            outlinestream << key << "=\""  << score << "\""<<"\n";
 
            std::cout << outlinestream.str();

            modification = true;
            
          }
          
        }

        if(!modification)
        {
            modifiedFile << templine << std::endl;
        }
        else
        {
            modifiedFile <<  outlinestream.str() << std::endl;
        }
        modification = false;
    
      }
    }
    else{
      std::cout << "file not found = " << std::endl;
    }

    inputFile.close();
    modifiedFile.close();
    remove(kScorePath.c_str());
    rename(kScoretempPath.c_str(), kScorePath.c_str());
  }
  
}

int LogScore::GetHighestScore() 
{
  return mHighestScore;
}

void LogScore::ReadHighestScoreFromfile() 
{ 

  string line;
  string key;
  string value;
  std::ifstream filestream(kScorePath);

  mHighestScore = 0;

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');

      std::istringstream linestream(line);
      while (linestream >> key >> value) {

        std::replace(value.begin(), value.end(), '_', ' ');
        if (key == kNames[NE_HighestScore] ) {
          std::replace(value.begin(), value.end(), '_', ' ');
         mHighestScore =  stoi(value);
        }
      }
    }
  }
  else{
    std::cout << "file not found = " << std::endl;

  }

}