#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class Node {
public:
    int value;
    int row;
    int col;
    Node* next;
};

Node* add(Node* head, int row, int col, int valueInput) //Reference: Stepik exercise 1.3
{
    Node* newNode = new Node();
    Node* temp;
    newNode->value = valueInput;
    newNode->col = col;
    newNode->row = row;
    temp = head;

    if(head == NULL){
        return newNode;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        return head;
    }
}

Node* getInput(Node* head){ //Reference: Stepik exercise 2.3
    Node* point;

    string line;
    string token;
    int rowNum=0;
    int colSize=0;
    int rowSize = 0;

    int test;

    getline(cin, line);

    //get col size
    stringstream lineStream(line);
    while(lineStream >> token)
    {
        colSize++;
    }

    //read lines

    for (int k = 0; k<colSize-1; k++)
    {
        stringstream lineStream2(line);
        rowSize = 0;
        while(lineStream2 >> token)
        {
            test = stoi(token);
            if (test != 0){
                head = add(head, rowNum, rowSize, test);
            }
            rowSize++;
        }
        rowNum++;
        getline(cin, line);
        if (line == " "){
            return head;
        }


    }
    //do the last line
    stringstream lineStream2(line);
    rowSize = 0;

    while(lineStream2 >> token)
    {

        test = stoi(token);

        if (test != 0){
            head = add(head, rowNum, rowSize, test);
        }

        rowSize++;
    }

    if (rowSize != colSize){
        cout << "Error! Non-square matrix!" << endl;
        exit(0);
    }

    return head;
}

Node* getElement(Node* head, int row, int col){ //Modified from getInput function
    Node* temp = head;
    while(true){
        if(temp->row == row && temp->col == col){
            return temp;

        }
        else{
            if (temp->next == NULL){
                Node* test = new Node();
                test->value = 0;
                return test;
            }
            temp = temp->next;
        }
    }
}

int getRowAmount(Node* head){ //Modified from getInput function

    Node* temp = head;
    int rowNum = 0;

    if(head == NULL){
        return 0;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        rowNum = temp->row;
        return rowNum;
    }
}

int getColAmount(Node* head){ //Modified from getInput function

    Node* temp = head;
    int colNum = 0;

    if(head == NULL){
        return 0;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        colNum = temp->row;
        return colNum;
    }
}

int getSize(Node* head){ //Modified from getInput function

    Node* temp = head;
    int counter = 0;

    if(head == NULL){
        return 0;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
            counter++;
        }
        return counter + 1;
    }
}

Node* minorFunction(Node* head, int row, int col){
    Node* newHead1 = NULL;
    Node* newHead2 = NULL;
    Node* temp = head;

    while(temp != NULL){

        if (temp->col != col){
            if (temp->col < col)
                newHead1 = add(newHead1, temp->row, temp->col, temp->value);
            else
                newHead1 = add(newHead1, temp->row, temp->col - 1, temp->value);
        }
        temp = temp->next;
    }

    temp = newHead1;

    while(temp != NULL){

        if (temp->row != row){
            if (temp->row < row)
                newHead2 = add(newHead2, temp->row, temp->col, temp->value);
            else
                newHead2 = add(newHead2, temp->row - 1, temp->col, temp->value);
        }
        temp = temp->next;
    }

    if (newHead2 == NULL) {
        Node *test = new Node();
        test->value = 0;
        return test;
    }

    return newHead2;
}

int determinant(Node* head){
    int result = 0;
    int j = 0;

    if(getSize(head) == 0){
        return 0;
    }

    if(getSize(head) == 1){
        return head->value;
    }

    for (int i = 0; i <= getRowAmount(head); i++){
        result += (pow((-1),(i+j)) * getElement(head,i,j)->value * determinant(minorFunction(head,i,j)));
    }

    return result;
}

int main() {

    Node* head = NULL;
    head = getInput(head);

    cout << determinant(head) << endl;


    return 0;
}