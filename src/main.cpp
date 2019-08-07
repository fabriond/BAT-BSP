#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../include/matrix.h"
#include "../include/bat_swarm.h"
#include "../include/random_engine.h"

using namespace std;

#define T_MAX 625
#define STATION_COUNT 6
#define HEXAGON_RADIUS 63
#define STATION_RADIUS 126

Matrix regionMap(T_MAX, T_MAX);

int defaultFilled;

void initMap(){

    regionMap.placeHexagon(231, 127, HEXAGON_RADIUS);

    regionMap.placeHexagon(340, 127, HEXAGON_RADIUS);

    regionMap.placeHexagon(448, 127, HEXAGON_RADIUS);

    regionMap.placeHexagon(178, 220, HEXAGON_RADIUS);

    regionMap.placeHexagon(286, 220, HEXAGON_RADIUS);

    regionMap.placeHexagon(394, 220, HEXAGON_RADIUS);

    regionMap.placeHexagon(124, 312, HEXAGON_RADIUS);

    regionMap.placeHexagon(231, 312, HEXAGON_RADIUS);

    regionMap.placeHexagon(178, 406, HEXAGON_RADIUS);

    regionMap.placeHexagon(286, 406, HEXAGON_RADIUS);

    regionMap.placeHexagon(394, 406, HEXAGON_RADIUS);

    regionMap.placeHexagon(231, 499, HEXAGON_RADIUS);

    regionMap.placeHexagon(340, 499, HEXAGON_RADIUS);

    regionMap.placeHexagon(448, 499, HEXAGON_RADIUS);

    /*regionMap.placeHexagon(23, 13, HEXAGON_RADIUS);

    regionMap.placeHexagon(34, 13, HEXAGON_RADIUS);

    regionMap.placeHexagon(45, 13, HEXAGON_RADIUS);

    regionMap.placeHexagon(18, 22, HEXAGON_RADIUS);

    regionMap.placeHexagon(29, 22, HEXAGON_RADIUS);

    regionMap.placeHexagon(39, 22, HEXAGON_RADIUS);

    regionMap.placeHexagon(12, 31, HEXAGON_RADIUS);

    regionMap.placeHexagon(23, 31, HEXAGON_RADIUS);

    regionMap.placeHexagon(18, 41, HEXAGON_RADIUS);

    regionMap.placeHexagon(29, 41, HEXAGON_RADIUS);

    regionMap.placeHexagon(39, 41, HEXAGON_RADIUS);

    regionMap.placeHexagon(23, 50, HEXAGON_RADIUS);

    regionMap.placeHexagon(34, 50, HEXAGON_RADIUS);

    regionMap.placeHexagon(45, 50, HEXAGON_RADIUS);*/
}

double fitness(vector<double> pos){
    Matrix m = regionMap;
    for(int i = 0; i < pos.size()-1; i+=2){
        m.placeCircle(pos.at(i), pos.at(i+1), STATION_RADIUS);
    }
    int result = 0;
    for(int i = 0; i < m.getNumRows(); ++i){
        for(int j = 0; j < m.getNumRows(); ++j){
            result += m.getValue(i, j);
        }
    }
    return (double) result/defaultFilled;
}

void genGraph(vector<double> pos, int number){
    Matrix m = regionMap;
    for(int i = 0; i < pos.size()-1; i+=2){
        m.placeCircle(pos.at(i), pos.at(i+1), STATION_RADIUS);
    }

    std::stringstream ss;
    ss << "./plots/plot"<< number <<".txt";
    string filepath = ss.str();

	ofstream file(filepath);
    file << m;
    file.close();
}

//Compile with: g++ -std=c++11 src/main.cpp src/matrix.cpp src/random_engine.cpp src/bat_swarm.cpp src/bat.cpp -o main
int main(int argc, char **argv){

    initMap();
    
    ofstream file("./plots/example.txt");
    file << regionMap;
    file.close();

    defaultFilled = 0;
    for(int i = 0; i < regionMap.getNumRows(); ++i){
        for(int j = 0; j < regionMap.getNumRows(); ++j){
            defaultFilled += regionMap.getValue(i, j);
        }
    }

    int dimensions = STATION_COUNT*2;

    vector<double> lb(dimensions, 0);
    vector<double> ub(dimensions, T_MAX);

    BatSwarm swarm(dimensions, 20, lb, ub, fitness);
    Bat best = swarm.getBest();
    cout << "Iterations: " << swarm.getIterationCount() << "; " << swarm.getBest() << endl;
    genGraph(swarm.getBest().getPosition(), swarm.getIterationCount());

    while(0.01 < best.getFitness() && swarm.getIterationCount() < 200){
        swarm.update();
        if(swarm.getBest() <= best){
            cout << "Iterations: " << swarm.getIterationCount() << "; " << swarm.getBest();
            
            if(swarm.getBest() < best){
                genGraph(swarm.getBest().getPosition(), swarm.getIterationCount());
                cout << endl;
            } else{
                cout << "\r";
            }
            
            best = swarm.getBest();
        }
    }

    cout << "Iterations: " << swarm.getIterationCount() << "; " << best << endl;
}