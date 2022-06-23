//
// Created by stach on 06.06.22.
//
#ifndef GUROBI_TEMPLATE_PURESTRATEGY_H
#define GUROBI_TEMPLATE_PURESTRATEGY_H
#include<vector>
#include "chopstick/chopstick.h"
#include "utils.h"

class PureStrategy {
protected:
    std::vector<int> division;
public:
    bool operator != (const PureStrategy &Ref) const {
        return(this->division != Ref.division);
    }

    bool operator == (const PureStrategy &Ref) const {
        return(this->division == Ref.division);
    }

    PureStrategy(std::vector<int> div) {
        this->division = div;
    }

    vector<int> get_division(){
        return this->division;
    }

    PureStrategy next_strategy(){
        return PureStrategy(next_division(this->division));
    }

    double payoff(PureStrategy strategy){
        return symmetrized_payoff_chopstick(this->division, strategy.division);
    }
};


#endif //GUROBI_TEMPLATE_PURESTRATEGY_H
