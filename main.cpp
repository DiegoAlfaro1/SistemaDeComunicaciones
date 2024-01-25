#include <string>
#include <iostream>
#include<sstream>
#include <iomanip>
#include<fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"


using namespace std;

int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;
  vector <Customer*> customers;
  vector <Operator*> operators;
  int idCustomer, idOperator, C, O, N;

  if (argc != 3) {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  int oper,x,y,z,ap;
  //Operator* ap;
  double xd,yd,zd;
  std::string name;
  inputFile >> C >> O >> N;

	cout << "Entering..\n";
	
	idCustomer = idOperator = 0;
	customers.resize(C);
	operators.resize(O);
  for(int i = 0; i < N; i++){
    inputFile >> oper;
    cout << "operation = " << oper << "\n";
    switch (oper){
      case 1:
        inputFile >> name >> x >> ap >> xd;
        customers[idCustomer] = new Customer(idCustomer,name,x,operators[ap],xd);
        idCustomer++;
        break;
      case 2:
        inputFile >> x >> xd >> yd >> zd >> y;
        switch(x){
          case 1:
            operators[idOperator] = new VoxOperator(idOperator,xd,yd,zd,y,INTERNET);
            idOperator++;
            break;
          case 2:
            operators[idOperator] = new InternetOperator(idOperator,xd,yd,zd,y,INTERNET);
            idOperator++;
            break;
        }
        break;
      case 3:
        inputFile >> x >> y >> z;
        customers[x] -> talk(z, *customers[y]);
        break;
      case 4:
        inputFile >> x >> y >> z;
        customers[x] -> message(z,*customers[y]);
        break;
      case 5:
        inputFile >> x >> xd;
        customers[x] -> connection(xd);
        break;
      case 6:
        inputFile >> x >> xd;

        customers[x] -> getBill() -> pay(xd);

        break;
      case 7:
        inputFile >> x >> y;

        customers[x] -> setOperator(operators[y]);
        break;
      case 8:
        inputFile >> x >> xd;

        customers[x] -> getBill() -> changeTheLimit(xd);
        break;
    }
  }
  cout << "printing\n";
  for (int i = 0; i < idOperator;i++){
    outputFile<<operators[i]->toString()<<endl;

  }

  for (int i = 0; i < idCustomer; i++){

    outputFile<<customers[i]->toString()<<endl;
  }

  int tiempo = 0;
  int id_m= 0;

  for (int i = 0; i < customers.size(); i++){

    int comparation=customers[i]->getTotalSpentTalkingTime();

    if (comparation > tiempo){
      tiempo = comparation;
      id_m=i;

    }else if (comparation == tiempo){

      if (i < id_m){
        id_m=i;
      }

    }

    

  }
  
  outputFile<<customers[id_m]->getName()<<": "<< customers[id_m]->getTotalSpentTalkingTime()<<endl;;

  tiempo = 0;
  id_m= 0;

  for (int i = 0; i < customers.size(); i++){

    int comparacion=customers[i]->getTotalMessageSent();

    if (comparacion > tiempo){
      tiempo = comparacion;
      id_m=i;

    }else if (comparacion == tiempo){

      if (i < id_m){
        id_m=i;
      }

    }

  }

  outputFile<<customers[id_m]->getName()<<": "<< customers[id_m]->getTotalMessageSent()<<endl;
  
  double tiempo_2;

  for (int i = 0; i < customers.size(); i++){

    double comparacion_2=customers[i]->getTotalInternetUsage();

    if (comparacion_2 > tiempo_2){
      tiempo_2 = comparacion_2;
      id_m=i;

    }else if (comparacion_2 == tiempo_2){

      if (i < id_m){
        id_m=i;
      }

    }

    

  }

  outputFile<<customers[id_m]->getName()<<": "<< customers[id_m]->getTotalInternetUsage()<<endl;

  inputFile.close();
  outputFile.close();
  return 0;
}
