// =========================================================
// File: customer.h
// Author: Diego Alfaro 
// Date:6/1/2023
// Description:
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
};

//constructores
Customer::Customer(int id_r, std::string name_r, int age_r, Operator* obj_operator, double cred_limit){
  id = id_r;
  name = name_r;
  age = age_r;
  op = obj_operator;
  bill = new Bill(cred_limit);
  totalInternetUsage = 0;
  totalMessageSent = 0;
  totalSpentTalkingTime = 0;
}

Customer::Customer(const Customer& obj1){
  id = obj1.id;
  name = obj1.name;
  age = obj1.age;
  op = obj1.op;
  totalInternetUsage = obj1.totalInternetUsage;
  totalMessageSent = obj1.totalMessageSent;
  totalSpentTalkingTime = obj1.totalSpentTalkingTime;
}

Customer::~Customer(){
  delete bill;
  op = nullptr;
  bill = nullptr;
}

//getters
int Customer::getId() const{
  return id;
}

int Customer::getAge() const{
  return age;
}

int Customer::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const{
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const{
  return totalInternetUsage;
}

std::string Customer::getName() const{
  return name;
}

Operator* Customer::getOperator() const{
  return op;
}

Bill* Customer::getBill() const{
  return bill;
}

void Customer::setOperator(Operator* obj){
  op = obj;
}

//metodos
string Customer::toString() const{
  ostringstream str;
  str << "Customer id: " << id << " "<< std::fixed << std::setprecision(2) << bill -> getTotalMoneySpent()  << " "<< std::fixed << std::setprecision(2) << bill -> getCurrentDebt();
  string str1 = str.str();
  return str1;
}

void Customer::talk(int min, Customer &other){
  double cost;
  if(min < 0 ){
    return; 
  }
  if(id != other.id){
    cost = op -> calculateTalkingCost(min, age);
    if(bill ->check(cost) == true){
      bill -> add(cost);
      totalSpentTalkingTime += min;
      op -> addTalkingTime(min);
      if(op -> getId() != other.op -> getId()){
        other.op->addTalkingTime(min); 
      }
    }
  }
}

void Customer::message(int quantity, const Customer &other){
  double cost;
  if(quantity <= 0){
    return;
  }
  if(id != other.id){
    cost = op -> calculateMessageCost(quantity,op -> getId(), other.op -> getId());
    if(bill -> check(cost) == true){
      bill -> add(cost);
      op -> addTotalMessageSent(quantity);
      totalMessageSent += quantity;
    }
  }
}

void Customer::connection(double amount){
  double cost;
  if(amount <= 0){
    return;
  }else{
    cost = op -> calculateNetworkCost(amount);
    if(bill -> check(cost)){
      bill -> add(cost);
      op -> addTotalInternetUsage(amount);
      totalInternetUsage += amount;
    }

  }
}


#endif