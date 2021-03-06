#ifndef PhotoSelector_H
#define PhotoSelector_H

#include <queue>
#include <algorithm>
#include <random>
#include <math.h>
#include <chrono>

#include "Photo.h"
#include "Slide.h"
#include "Individual.h"

class PhotoSelector
{
    int heuristic;

    int currentScore = 0;
    int initialScore = 0;
    long stateChanges = 0;
    long nAttempts = 0;
    long maxAttempts;

    double T = 1;         // initial and final temperature
    double Tmin = 0.0001; // temperature at which iteration terminates
    double alpha = 0.9;   // decrease in temperature
    long numIterations;   // number of iterations of annealing before decreasing temperature;

    queue<string> tabuList;
    queue<string> tabuAux;
    size_t tabuListSize;

    vector<Individual> population;
    int populationSize;
    int maxGenerations;

    vector<Photo> vPhotos;
    vector<Photo> hPhotos;
    vector<Slide> currentSlides;
    size_t lastSlideIndex;

public:
    // Constructor
    PhotoSelector(vector<Photo> vp, vector<Photo> hp);
    // Getters
    int getCurrentScore();
    vector<Photo> getVertical();
    vector<Photo> getHorizontal();
    vector<Slide> getCurrentSlides();
    int getInitialScore();
    // Setters
    void setVertical(vector<Photo> vp);
    void setHorizontal(vector<Photo> hp);
    void setHeuristic(int heuristic);
    void setMaxAttempts(int maxAttempts);
    void setTemperature(double temperature);
    void setTmin(double Tmin);
    void setAlpha(double alpha);
    void setNumIterations(int numIterations);
    void setTabuListSize(size_t size);
    void setPopulationSize(int populationSize);
    void setMaxGenerations(int maxGenerations);
    // Main Functions
    void makeSlides();
    void findVerticalPair(Photo &photo, Slide &slide);
    void getRandomIndexes(size_t &firstSlideIndex, size_t &secondSlideIndex, mt19937 generator);
    void genPairVerticalSlides(Slide &s1, Slide &s2, Slide firstSlide, Slide secondSlide, mt19937 generator);
    int getTransitionScore(unordered_set<string> currentSlide, unordered_set<string> nextSlide);
    void compareScores(Slide &firstSlide, Slide &secondSlide, int &scoreBefore, int &scoreAfter, size_t firstSlideIndex, size_t secondSlideIndex);
    string tabuEntry(size_t firstIndex, size_t secondIndex, int kind);
    bool isTabu(string entry);
    vector<int> createChromosome(size_t range);
    size_t parentRoulette(vector<Individual> &population, int i);
    // Heuristics
    void hillClimbing();
    void simulatedAnnealing();
    void tabuSearch();
    void geneticAlgorithm();
    // Neighbouring Functions
    void neighbouringHC(); //neighbour function for hill climbing
    void neighbouringSA(); //neighbour function for simulated annealing
    void neighbouringTS(); //neighbour function for tabu search
    // Evaluation Function
    int calculateFitness(Individual individual);
    void evaluateScore();
    int evaluateScore(vector<Slide> &v);
};

#endif //PhotoSelector_H
