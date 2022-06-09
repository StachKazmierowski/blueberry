//
// Created by stach on 06.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_ORACLE_H
#define DOUBLEORACLEALGORITHM_ORACLE_H
#include "mixedStrategy.h"
#include "pureStrategy.h"
#include "utils.h"

class Oracle {
public:
    static PureStrategy find_best_response(MixedStrategy opponentMixedStrategy, PureStrategy firstStrategy){
        PureStrategy bestResponse = firstStrategy;
        double bestPayoff = opponentMixedStrategy.opponents_payoff(firstStrategy);
        PureStrategy currentStrategy = PureStrategy(firstStrategy);
        while(currentStrategy != currentStrategy.next_strategy()){
            if(opponentMixedStrategy.opponents_payoff(currentStrategy) > bestPayoff){
                bestResponse = PureStrategy(currentStrategy);
                bestPayoff = opponentMixedStrategy.opponents_payoff(bestResponse);
            }
            currentStrategy = currentStrategy.next_strategy();
        }
        return bestResponse;
    }
};


#endif //DOUBLEORACLEALGORITHM_ORACLE_H
