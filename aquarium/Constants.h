#ifndef CONSTANTS_H
#define CONSTANTS_H

///coef
static const int coefOfPlancton = 1;
static const int coefOfHerbivore = 3;
static const int coefOfPredator = 4;
///Planktons
static const int radOfViewPlankton=3;
static const int radOfViewPlanktonDelta = 2;
static const int radOfDispPlankton=2;
static const int radOfDispPlanktonDelta = 1;
static const int lifeTimePlankton=4;
static const int lifeTimePlanktonDelta = 5;
static const int childrenOfPlankton = 7;
///Herbivores
static const int radOfViewHerbivore=7;
static const int radOfViewHerbivoreDelta = 3;
static const int radOfDispHerbivore=5;
static const int radOfDispHerbivoreDelta = 2;
static const int lifeTimeHerbivore=20;
static const int lifeTimeHerbivoreDelta = 10;
static const int eatTimeHerbivore = 7;
static const int eatTimeHerbivoreDelta = 2;
static const int childrenOfHerbivore = 3;

///Predators
static const int radOfViewPredator=8;
static const int radOfViewPredatorDelta = 5;
static const int radOfDispPredator=6;
static const int radOfDispPredatorDelta = 2;
static const int lifeTimePredator=15;
static const int lifeTimePredatorDelta = 5;
static const int eatTimePredator = 6;
static const int eatTimePredatorDelta = 3;
static const int childrenOfPredator = 2;
///
static const double speedPlancton = 0.003;
static const double speedHerbivore = 0.005;
static const double speedPredator = 0.008;
#endif