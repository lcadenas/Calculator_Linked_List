#include "CalcList.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

//function that returns the total of the list
double CalcList::total() const               
{
    if (empty()) {                              //check if the list is empty
        return 0;                              
    } 
    return head->element;                      //return the data on the head
}

//function that performs calculations and adds elemts to the front of the list
void CalcList::newOperation(const FUNCTIONS func, const double operand)     
{
    SNode* node = new SNode;                    //creates a new node
    node->stepTotal = total();                  //store the total before performing the operation
    node->operand = operand;                    //store the operand of the operation

    switch(func)                               //create a switch statement to perform the correct operation
    {
        case ADDITION:         
            node->funcOpt = "+";                //store the operation symbol as a string
            totalopt = total() + operand;       //perform calculation and store the new total in the totalopt variable
            break;
        case SUBTRACTION:
            node->funcOpt = "-";                //store the operation symbol as a string
            totalopt = total() - operand;       //perform calculation and store the new total in the totalopt variable
            break;
        case MULTIPLICATION:
            node->funcOpt = "*";                //store the operation symbol as a string
            totalopt = total() * operand;       //perform calculation and store the new total in the totalopt variable
            break;
        case DIVISION:
            node->funcOpt = "/";                //store the operation symbol as a string
            if(operand == 0)
                throw runtime_error("Cannot divide by zero");       //throw a message when trying to divide by zero
            else
                totalopt = total() / operand;           //perform calculation and store the new total in the totalopt variable
            break;
        default:
            break;
    }
    
    node->element = totalopt;                       //store the result in the new node
    node->next = head;                             //place the new node in front of the head
    head = node;                                  //assign head the new node 
}

//function that remove the last operation by deleting the first node of the list       
void CalcList::removeLastOperation()
{
    if(empty()){
        throw runtime_error("Cannot revome from an empty list.");       //throw a message when trying to delete from an empty list
    }
    SNode* undo = head;                         //create a node to store the information in head
    head = undo->next;                         //assign head to the next node
    delete undo;                              //delete the first node
}

//function that returns a list of the performed operations
std::string CalcList::toString(unsigned short precision) const
{
    int count = 0;                               //variable to count the steps
    std::ostringstream ossText;                 //variable to store all the components of the operation
    std::string finalText;                     //variable to return the string
    ossText << std::setprecision(precision) << std::fixed;  //set the precision of the numbers
    
    if(empty())                               //check if the list is empty
        return "";
    
    SNode* temp1 = head;                      //create node pointer to iterate thruogh the list  
    while(temp1 != nullptr)
    {
        count++;                             //increment count every time there is a node
        temp1 = temp1->next;                 //move to the following node
    }

    SNode* temp2 = head;                     //create node pointing to head to iterate thruogh the list
    while(temp2 != nullptr)
    {
        //store the needed information as "(step): (totalAtStep)(Function)(operand) = (newTotal)\n".
        ossText << count << ": " << temp2->stepTotal << temp2->funcOpt << temp2->operand << "=" << temp2->element << "\n"; 

        count--;                            //decrement count every time there is a node
        temp2= temp2->next;                 //move to the following node
    }
    return finalText = ossText.str();
}

CalcList::~CalcList()       // deallocate memory 
{ 
    while(!empty()) 
    {
        removeLastOperation();      //call the function to delete the nodes
    }
}