// =========================================================
// File: operator.h
// Author: Diego Alfaro
// Date:5/27/2023
// Description:
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

//constructores

Operator::Operator(int id_r, double cost_call, double cost_msg, double cost_gb, int discount, OperatorType type_r){
    id = id_r;
    talkingCharge = cost_call;
    messageCost = cost_msg;
    networkCharge = cost_gb;
    discountRate = discount;
    type = type_r;

    totalInternetUsage = 0;
    totalMessageSent = 0;
    totalSpentTalkingTime = 0;
}

Operator::Operator(const Operator& obj){
    id = obj.id;
    talkingCharge = obj.talkingCharge;
    messageCost = obj.messageCost;
    networkCharge = obj.networkCharge;
    discountRate = obj.discountRate;
    type = obj.type;

    totalInternetUsage = obj.totalInternetUsage;
    totalMessageSent = obj.totalMessageSent;
    totalSpentTalkingTime = obj.totalSpentTalkingTime;
}


//getters

int Operator::getId() const{
    return id;
}

int Operator::getDiscountRate() const{
    return discountRate;
}

double Operator::getTalkingChage() const{
    return talkingCharge;
}

double Operator::getMessageCost() const{
    return messageCost;
}

double Operator::getNetworkCharge() const{
    return networkCharge;
}

int Operator::getTotalSpentTalkingTime() const{
    return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const{
    return totalMessageSent;
}

double Operator::getTotalInternetUsage() const{
    return totalInternetUsage;
}

OperatorType Operator::getType() const{
    return type;
}

//metodos

void Operator::addTalkingTime(int min){
    if(min > 0){
        totalSpentTalkingTime = totalSpentTalkingTime + min;
    }
}

void Operator::addTotalMessageSent(int n){
    if(n > 0){
        totalMessageSent = totalMessageSent + n;
    }
}

void Operator::addTotalInternetUsage(double n){
    if(n > 0){
        totalInternetUsage = totalInternetUsage + n;
    }
}

string Operator:: toString() const{
    ostringstream str;
    str << "Operator id: " << id << " "<< totalSpentTalkingTime << " "<< 
    totalMessageSent << " "<< fixed << setprecision(2)<< totalInternetUsage;

    string str1 = str.str();
    return str1;
}





#endif