#ifndef CONSTANTS_H
#define CONSTANTS_H

///coef
static const int coefOfPlancton = 1;
static const int coefOfHerbivore = 3;
static const int coefOfPredator = 4;

///Planktons
static const int radOfViewPlankton = 3;
static const int radOfViewPlanktonDelta = 2;
static const int radOfDispPlankton = 2;
static const int radOfDispPlanktonDelta = 1;
static const int lifeTimePlankton = 8;
static const int lifeTimePlanktonDelta = 2;
static const int childrenOfPlankton = 2;
static const int pauseReprOfPlankton = 3;

///Herbivores
static const int radOfViewHerbivore = 7;
static const int radOfViewHerbivoreDelta = 3;
static const int radOfDispHerbivore = 5;
static const int radOfDispHerbivoreDelta = 2;
static const int lifeTimeHerbivore = 6;
static const int lifeTimeHerbivoreDelta = 3;
static const int eatTimeHerbivore = 5;
static const int eatTimeHerbivoreDelta = 2;
static const int childrenOfHerbivore = 6;
static const int pauseReprOfHerbivore = 5;

///Predators
static const int radOfViewPredator = 8;
static const int radOfViewPredatorDelta = 5;
static const int radOfDispPredator = 6;
static const int radOfDispPredatorDelta = 2;
static const int lifeTimePredator = 13;
static const int lifeTimePredatorDelta = 4;
static const int eatTimePredator = 3;
static const int eatTimePredatorDelta = 3;
static const int childrenOfPredator = 3;
static const int pauseReprOfPredator = 7;
///
static const double speedPlancton = 0.03;
static const double speedHerbivore = 0.05;
static const double speedPredator = 0.08;
#endif