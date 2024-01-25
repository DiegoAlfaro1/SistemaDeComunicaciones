// =========================================================
// File: bill.h
// Author: Diego Alfaro
// Date: 5/27/2023
// Description:
// =========================================================

#ifndef BILL_H
#define BILL_H

#include<iostream>

using namespace std;

class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

//constructores
Bill::Bill(){
    limitAmount = 0;
    currentDebt = 0;
    totalMoneySpent = 0;
}

Bill::Bill(double n){
    if(n > 0){
        limitAmount = n;
    }else{
        limitAmount = 0;
    }
    currentDebt = 0;
    totalMoneySpent = 0;
}

Bill::Bill(const Bill& obj1){
    limitAmount = obj1.limitAmount;
    currentDebt = obj1.currentDebt;
    totalMoneySpent = obj1.totalMoneySpent;
}

//getters
double Bill::getLimitAmount() const{
    return limitAmount;
}

double Bill::getCurrentDebt() const{
    return currentDebt;
}

double Bill::getTotalMoneySpent() const{
    return totalMoneySpent;
}

//metodos

void Bill::add(double n){
    if(n > 0){
        currentDebt = currentDebt + n;
    }
}

void Bill::pay(double n){
    if(n > 0){
        if(n < currentDebt){
            currentDebt = currentDebt - n;
            totalMoneySpent = totalMoneySpent + n;
        }
        else{
            double aux = n - currentDebt;
            aux = n - aux;
            currentDebt = 0;
            totalMoneySpent = totalMoneySpent + aux;
        }
    }
}

void Bill::changeTheLimit(double n){
    if(n > 0){
        if(n > currentDebt){
            limitAmount = n;
        }
    }
}

bool Bill::check(double n) const{
    if((n + currentDebt) < limitAmount){
        return true;
    }else{
        return false;
    }
}
#endif