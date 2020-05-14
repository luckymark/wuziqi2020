#pragma once
//struct
typedef struct {
	int x,y,direction;
} TupleFivePoint;


//prototype
Score getScoreByFiveTuple(GameEngine* engine);
int scoreSingleFiveTuple(GameEngine* engine, TupleFivePoint point);
void addTmpScoreFiveTuple(Score* score, TupleFivePoint point, int tmpScore);
int isOutOfTupleStartRange(TupleFivePoint point);
