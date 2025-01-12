#ifndef LOGSCORE_H
#define LOGSCORE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

const std::string kScorePath{"score"};
const std::string kScoretempPath{"scoretemp"};

enum NamesEnum{
  NE_Name,
  NE_Version,
  NE_Language,
  NE_PrettyName,
  NE_Author,
  NE_SrcUrl,
  NE_ForkUrl,
  NE_HighestScore,
  NE_LastEnumNo
};

const std::string kNames[] {
"NAME" , "VERSION" , "LANGUAGE" , "PRETTY_NAME", "AUTHOR" , "SRC_URL" , "FORK_URL" , "HIGHEST_SCORE"
};


class LogScore
{
public:
  // member variables

  // member protoypes
  int GetHighestScore() ;

  void UpdateHighestScore(int score);

  void ReadHighestScoreFromfile();
  
private:

  // member variables

  int mHighestScore;

  // member protoypes

};

#endif  /* End of LOGSCORE_H */