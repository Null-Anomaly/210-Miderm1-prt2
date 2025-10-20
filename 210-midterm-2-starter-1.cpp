/*COMSC 210 | Midterm 1 Part 2| Lawrence Bryant
IDE used: Visual Studio Code*/
#include <iostream>
#include <stdio.h>      
#include <stdlib.h> 
#include <time.h>
#include <fstream>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() 
{
    srand(time(NULL));

    ifstream fin("names.txt");

    if(fin.good())//Just checks if the file input is good
    {
        fin.close();//This immediately closes the file so I can begin the most scuffed
                    //File input of all time.

        //First set of customers variable.
        DoublyLinkedList customers;
        string tempn;
        int storeIn;
        vector<string> totalLine;

        cout << "Store opens:\n";
        for(int i = 0; i < 5; i++)//Creates the first five customers based on the line their name is in
        {
            storeIn = rand() % 100 + 1;
            customers.push_back(storeIn);
            fin.open("names.txt"); //Opens the file back up from the start each time
            for(int j = 0; j < storeIn; j++)
            {
                getline(fin, tempn);
            }
            cout << "   " << tempn << " joins the line\n";
            totalLine.resize(totalLine.size()+1);
            totalLine[i] = tempn; //Keeps track of the line of names.
            fin.close(); //Hard resets the file.
        }
        cout << "   Resulting line:\n";
        for(int i = 0; i < totalLine.size(); i++)
        {
            cout << "   " << totalLine[i] << "\n";
        }

        //Now the big main loop
        
        //Variables needed to keep track of things
        int vip;
        int newCustomer;
        int served;
        int bored;
        int boredInLine;
        

        for(int i = 2; i < 21; i++)
        {
            cout << "Time step #" << i << "\n";


            //Joined the line
            newCustomer = rand() % 100 + 1;
            if(newCustomer <= 60)
            {
                fin.open("names.txt");
                storeIn = rand() % 100 + 1;
                customers.push_back(storeIn);
                for(int j = 0; j < storeIn; j++)
                {
                    getline(fin,tempn);
                }
                totalLine.resize(totalLine.size()+1);
                totalLine[totalLine.size() - 1] = tempn;
                fin.close();
                cout <<"    "<< tempn << " joined the line\n";
            }

            //Leaves the line before being served
            boredInLine = rand() % 100 + 1;
            if(boredInLine <= 10)
            {
                storeIn = rand() % totalLine.size();
                customers.delete_pos(storeIn);
                cout << "    "<<totalLine[storeIn-1] << " left the line\n";
                totalLine.erase(totalLine.begin() + storeIn);
                
            }

            //VIP customer joins the line
            vip = rand() % 100 + 1;
            if(vip <= 10)
            {
                fin.open("names.txt");
                storeIn = rand() % 100 + 1;
                customers.push_front(storeIn);
                for(int j = 0; j < storeIn; j++)
                {
                    getline(fin,tempn);
                }
                totalLine.resize(totalLine.size()+1);
                for(int j = 0; j < totalLine.size()-1; j++)
                {
                    totalLine[j+1] = totalLine[j];
                }
                totalLine[0] = tempn;
                fin.close();
                cout <<"    "<< tempn << " (VIP) joins the front of the line\n";
            }

            //Served customer
            served = rand() % 100 + 1;
            if(served <= 40)
            {
                cout << totalLine[0] << " is served\n";
                customers.pop_front();
                for(int j = 0; j < totalLine.size() - 1; j++)
                {
                    totalLine[j] = totalLine[j+1];
                }
                totalLine.resize(totalLine.size()-1);
            }

            //Rear of the line leaves
            bored = rand() % 100 + 1;
            if(bored <= 20)
            {
                cout <<"    " <<totalLine[totalLine.size()-1] << " (the rear) left the line";
                customers.pop_back();
                totalLine.pop_back();
            }

            //Final Line output
            cout << "   Resulting line:\n";
            for(int j = 0; j < totalLine.size(); j++)
            {
                cout <<"    " << totalLine[j] << "\n";
            }

        }
    }
    
    return 0;
}
//Whoops! Couldn't get all the errors. Works on some runs, fails on others, no time to check
//Also this wound up using Vectors more than the actual DDL since the DDL had no way
//Of pulling any of the needed data out of it.