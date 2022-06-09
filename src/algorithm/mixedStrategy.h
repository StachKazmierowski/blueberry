//
// Created by stach on 06.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_MIXEDSTRATEGY_H
#define DOUBLEORACLEALGORITHM_MIXEDSTRATEGY_H
#include <vector>
#include <cassert>
#include "pureStrategy.h"
#include <cassert>

class MixedStrategy {
protected:
    std::vector<PureStrategy> strategies;
    std::vector<double> probabilities;
public:
    MixedStrategy(std::vector<PureStrategy> pureStrategies, std::vector<double> probs){
        assert(pureStrategies.size() == probs.size());
        this->strategies = pureStrategies;
        this->probabilities = probs;
    }

    vector<PureStrategy> get_strategies(){
        return this->strategies;
    }

    void append_strategy(PureStrategy p){
        this->strategies.push_back(p);
    }

    void set_probabilities(vector<double> probs){
        this->probabilities = probs;
    }

    double payoff(PureStrategy opponentStrategy){
        double result = 0.0;
        for(int i = 0 ; i < this->strategies.size(); i++){
            result += this->probabilities.at(i) * this->strategies.at(i).payoff(opponentStrategy);
        }
        return result;
    }

    double opponents_payoff(PureStrategy opponentStrategy){
        return -payoff(opponentStrategy);
    }

    bool contains(PureStrategy pureStrategy){
        for(PureStrategy p : this->strategies){
            if(p == pureStrategy)
                return true;
        }
        return false;
    }
};



#endif //DOUBLEORACLEALGORITHM_MIXEDSTRATEGY_H
