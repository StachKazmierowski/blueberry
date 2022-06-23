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
        assert_probabilities(probs);
        this->strategies = pureStrategies;
        this->probabilities = probs;
    }

    vector<PureStrategy> get_strategies(){
        return this->strategies;
    }

    vector<double> get_probabilities(){
        return this->probabilities;
    }

    int get_size(){
        return this->strategies.size();
    }

    void append_strategy(PureStrategy p){
        this->strategies.push_back(p);
    }

    void set_probabilities(vector<double> probs){
        assert_probabilities(probs);
        assert(probs.size() == this->strategies.size());
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

    int support_size(){
        int size = 0;
        for(double probability : probabilities){
            if(probability > 0.0){
                size++;
            }
        }
        return size;
    }

    int get_max_value(){
        int max_value = 0;
        for (int i = 0 ; i < this->get_size(); i++){
            if(this->probabilities.at(i) > 0 and max_value < this->strategies.at(i).get_division().at(0)){
                max_value = this->strategies.at(i).get_division().at(0);
            }
        }
        return max_value;
    }

};



#endif //DOUBLEORACLEALGORITHM_MIXEDSTRATEGY_H
