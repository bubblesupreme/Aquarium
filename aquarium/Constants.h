#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

///coef
static const int coefOfPlancton = 1;
static const int coefOfHerbivore = 3;
static const int coefOfPredator = 4;
static const std::string musicLive = "music water.wav";
static const std::string musicDied = "vertu.wav";
static const std::string mapPath = "waterR.png";

///Planktons
static const int radOfViewPlankton = 3;
static const int radOfViewPlanktonDelta = 2;
static const int radOfDispPlankton = 2;
static const int radOfDispPlanktonDelta = 1;
static const int lifeTimePlankton = 4;
static const int lifeTimePlanktonDelta = 2;
static const int childrenOfPlankton = 4;
static const int pauseReprOfPlankton = 3;

///Herbivores
static const int radOfViewHerbivore = 7;
static const int radOfViewHerbivoreDelta = 3;
static const int radOfDispHerbivore = 4;
static const int radOfDispHerbivoreDelta = 2;
static const int lifeTimeHerbivore = 6;
static const int lifeTimeHerbivoreDelta = 3;
static const int eatTimeHerbivore = 5;
static const int eatTimeHerbivoreDelta = 2;
static const int childrenOfHerbivore = 3;
static const int pauseReprOfHerbivore = 4;

///Predators
static const int radOfViewPredator = 8;
static const int radOfViewPredatorDelta = 5;
static const int radOfDispPredator = 6;
static const int radOfDispPredatorDelta = 2;
static const int lifeTimePredator = 10;
static const int lifeTimePredatorDelta = 5;
static const int eatTimePredator = 3;
static const int eatTimePredatorDelta = 2;
static const int childrenOfPredator = 3;
static const int pauseReprOfPredator = 6;
///
static const double speedPlancton = 0.015;
static const double speedHerbivore = 0.025;
static const double speedPredator = 0.04;
#endif