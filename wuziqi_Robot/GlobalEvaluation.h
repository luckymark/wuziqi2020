#pragma once
#include "GameEngine.h"

//prototype
int getGlobalEvaluation(GameEngine engine);
int getGE_IntX(int line[15],int x,int playerColor);
int getHorizontalGE(GameEngine engine);
int getVerticalGE(GameEngine engine);
int getObliqueGE_A(GameEngine engine);
int getObliqueGE_B(GameEngine engine);
