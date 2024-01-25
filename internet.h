// =========================================================
// File: internet.h
// Author: Diego Alfaro
// Date:6/1/2023
// Description:
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 1.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int) override;
  double calculateMessageCost(int, int, int) override;
  double calculateNetworkCost(double) override;
};

//constructores
InternetOperator::InternetOperator(int id, double cost_call, double cost_msg,double cost_gb, int discount, OperatorType tipo): Operator (id,cost_call,cost_msg,cost_gb,discount,tipo){}

InternetOperator::InternetOperator(const InternetOperator& obj1): Operator (obj1){}

//metodos

double InternetOperator:: calculateTalkingCost(int min, int age){
  if(min <= 0 || age <= 0){
    return 0;
  }else if(min < 2){
    double ans = (talkingCharge * min) - ((talkingCharge * min) * (discountRate / 100.0));
    return ans;
    }else{
      double ans = talkingCharge * min;
      return ans;
    }
}

double InternetOperator::calculateMessageCost(int quantity, int opId, int otherId){
  if(quantity < 0){
    return 0;
  }else if(quantity < 3){
    double ans = (quantity * messageCost) - ((quantity * talkingCharge) * (discountRate/100.0));
    return ans;
  }else{
      return (quantity * messageCost);
  }
}

double InternetOperator::calculateNetworkCost(double amount){
  if(amount <= 1){
    return 0;
  }else{
    amount = amount - LIMITGB;
    return amount * networkCharge;
  }
}

#endif