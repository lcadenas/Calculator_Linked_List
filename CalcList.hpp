#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

class SNode {
    private:
        double element;             //variable to store the final total
        std ::string funcOpt;       //variable to store the operation symbol
        double operand;             //variable to store the operand
        double stepTotal;           //variable to store the total before performing operation
        SNode* next;                //next item in the list
    friend class CalcList;          //give CalcList access
};

class CalcList : public CalcListInterface
{
    friend class SNode;
    private:
        SNode* head;                //pointer to the head of the list
        double totalopt = 0;        //store data after calculations
    public:
        CalcList(){head = nullptr;}         //constructor
        bool empty() const {return head == nullptr;}        //for empty list
        virtual double total() const;                       //function that returns the total of the list
        virtual void newOperation(const FUNCTIONS func, const double operand);      //function that performs calculations and adds elemts to the front of the list
        virtual void removeLastOperation();                 //function that remove the last operation by deleting the first node of the list
        virtual std::string toString(unsigned short precision) const;       //function that returns a list of the performed operations
        ~CalcList();                    //destructor
};                                              

#endif