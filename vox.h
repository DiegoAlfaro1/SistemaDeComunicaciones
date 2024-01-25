// =========================================================
// File: vox.h
// Author: Diego Alfaro
// Date: 6/2/2023
// Description:
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

//constructores

VoxOperator::VoxOperator(int id, double cost_call, double cost_msg, double cost_gb, int discount, OperatorType tipo): Operator (id,cost_call,cost_msg,cost_gb,discount,tipo){}

VoxOperator::VoxOperator(const VoxOperator& obj1): Operator (obj1){}

//metodos

double VoxOperator::calculateTalkingCost(int min, int age){
    if(min <= 0 || age <= 0){
        return 0;
    }else if(age < 18 || age > 65){
        return (talkingCharge * min) - ((talkingCharge * min) * (discountRate / 100.0));
    }else{
        return talkingCharge * min;
    }
}

double VoxOperator::calculateMessageCost(int quantity, int thisId, int otherId){
    if(quantity <= 0){
        return 0;
    }else{
        if(thisId == otherId){
            return (messageCost * quantity) - ((messageCost * quantity) * (discountRate / 100.0));
        }else{
            return messageCost * quantity;
        }
    }
}

double VoxOperator::calculateNetworkCost(double amount){
    if(amount > 0){
        return amount * networkCharge;
    }else{
        return 0;
    }
}
#endif