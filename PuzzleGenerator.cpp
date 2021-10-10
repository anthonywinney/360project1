#include "PuzzleGenerator.h"
#include <limits>
#include <ctime>

using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	
	srand(time(0));

	timer.StartTimer();
	maxtime = 59.9;	// To make sure we don't exceed a minute
	
	double random_walk_time = 59;	// 5 seconds.
	
	return RandomWalk(random_walk_time);	// Do a random walk for some time and return the solution.



}

Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that start at a random configuration and keeps randomly modifying it
	// until t hits the time limit. Returns the best solution found so far.

	/*Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	int bestInitialValue = p.GetValue();
	for(int i = 0; i < 20; i++){
		Puzzle temp = Puzzle(nRows, nColumns, minVal, maxVal);
		int tempValue = temp.GetValue();
		if(temp.HasSolution() && tempValue > bestInitialValue){
			p = temp;
			bestInitialValue = tempValue;
		}
	}*/



	Puzzle p(nRows, nColumns, minVal, maxVal);
	
	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;		
	Puzzle initialPuzzle = p;
	Puzzle currentPuzzle = p;
	Puzzle bestPuzzleOverall = p;

	int bestValueOverall = 0;
	int bestValue = 0;

	printf("Starting value: %d", bestValue);
	
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();

	//vector<Puzzle> goodSuccessors;
	
	// Loop until we hit the time limit.

	int checkIf1 = 1;

	//vector<vector<Puzzle>> goodSuccessors;
	//vector<vector<int>> goodSuccessorWeights;
	int goodSuccessorIndex = 0;


	

		


	for(int restart = 1; restart <= 100 && t.GetElapsedTime() < timelimit-0.1; restart++){

		p = Puzzle (nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
		int bestInitialValue = p.GetValue();
		for(int i = 0; i < 20; i++){
			Puzzle temp = Puzzle(nRows, nColumns, minVal, maxVal);
			int tempValue = temp.GetValue();
			if(temp.HasSolution() && tempValue > bestInitialValue){
				p = temp;
				bestInitialValue = tempValue;
			}
		}

		bestPuzzle = p;		
		initialPuzzle = p;
		currentPuzzle = p;
		
		bestValue = bestInitialValue;

		vector<vector<Puzzle>> goodSuccessors;
		vector<vector<int>> goodSuccessorWeights;
		goodSuccessorIndex = 0;

		while (t.GetElapsedTime() < restart*timelimit/10.0-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{

		// Generate a successor of p by randomly changing the value of a random cell 
		// (since we are doing a random walk, we just replace p with its successor).

		//currentPuzzle = initialPuzzle;
		vector<Puzzle> successors;
		vector<Puzzle> goodSuccessors1;
		vector<Puzzle> goodSuccessors2;
		vector<int> goodSuccessorWeights1;
		vector<int> goodSuccessorWeights2;




		int value = bestPuzzle.GetValue();


		for(int i = 0; i < 50; i++){
			successors.push_back(bestPuzzle.GetRandomSuccessor());
		}

		

		int bestTempValue = value;
		int totalTempDifference = 0;

		for(int i = 0; i < successors.size(); i++){
			Puzzle currentSuccessor = successors[i];

			if(!currentSuccessor.HasSolution()){
			 	continue;
			}
			else{
				int tempValue = currentSuccessor.GetValue();

				//int indexMinValue = 0;
				//int minValue = 1000;

				/*for(int j = 0; j < goodSuccessors.size(); j++){
					if(goodSuccessors[j].GetValue() < minValue){
						indexMinValue = j;
					}
				}

				if(goodSuccessors.size() <= 50){
					goodSuccessors.push_back(currentSuccessor);
				}
				else if(tempValue > minValue){
					goodSuccessors.insert(goodSuccessors.begin() + indexMinValue, currentSuccessor);
				}*/

				if(tempValue > bestValue){

					totalTempDifference += (tempValue-bestValue);

					goodSuccessors2.push_back(currentSuccessor);
					goodSuccessorWeights2.push_back(totalTempDifference);
					// printf("totalTempDifference: %d\n", totalTempDifference);

					//bestPuzzle = currentSuccessor;
					//bestValue = tempValue;
				}
				if(tempValue > bestValueOverall){
					bestPuzzleOverall = currentSuccessor;
					bestValueOverall = tempValue;
				}

				
				
			}

		}

		// if(checkIf1 == 1){
		// 	goodSuccessors1 = goodSuccessors2;
		// 	goodSuccessorWeights1 = goodSuccessorWeights2;
		// }
		
		int randomIndex = (rand() % (totalTempDifference+1));

		if(goodSuccessors2.size() > 0){
			goodSuccessors.push_back(goodSuccessors2);
			goodSuccessorWeights.push_back(goodSuccessorWeights2);
			goodSuccessorIndex++;
			//printf("%d\n",goodSuccessorIndex);
		}
		else if(goodSuccessors.size() == 0){
			continue;
		}
		else{
			goodSuccessorIndex--;
		}

		//bool useGoodSuccessor2 = checkIf1 > 1 && goodSuccessors2.size() > 0;
		vector<Puzzle> toEvaluateSuccessors = goodSuccessors[goodSuccessorIndex-1]; //useGoodSuccessor2 ? goodSuccessors2 : goodSuccessors1;
		vector<int> toEvaluateWeights = goodSuccessorWeights[goodSuccessorIndex-1]; //useGoodSuccessor2 ? goodSuccessorWeights2: goodSuccessorWeights1;
		// if(goodSuccessors2.size() == 0){
		// 	toEvaluateSuccessors = goodSuccessors1;
		// 	toEvaluateWeights = goodSuccessorWeights1;
		// }

		for(int k = 0; k < toEvaluateSuccessors.size(); k++){

			if(randomIndex <= toEvaluateWeights[k]){
				// printf("k: %d, randomIndex: %d, toEvaluateWeights[k]: %d\n", k, randomIndex, toEvaluateWeights[k]);
				bestPuzzle = toEvaluateSuccessors[k];
				bestValue = bestPuzzle.GetValue();
				//printf("best value: %d\n", bestValue);
				break;
			}

		}

		if (goodSuccessors2.size() > 0)
		{
			goodSuccessors1 = goodSuccessors2;
			goodSuccessorWeights1 = goodSuccessorWeights2;
		}
		//}
		
		
		// Update the current best solution.
		/*if (value > bestValue)	// Calling GetValue() for the first time is costly
										// since the puzzle has to be evaluated first.
		{
			bestValue = value;	// Calling it a second time simply returns the value that was computed before.
			bestPuzzle = p;
		}*/
		checkIf1++;
	}
	}
	
	return bestPuzzleOverall;
	
	// The following code is not executed in this function. It exists just as an example for getting all the successors of a puzzle.
	
}
