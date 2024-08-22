#include <iostream>  //for input output
#include <string>    //for strings
using namespace std;

/* STACK CLASS FOR STRING TYPE DATA*/
class StringStack {
private:
    string* array;
    int top;
    int size;
public:
    StringStack() {
        top = -1;
        size = 10;
        array = new string[size];
    }
    StringStack(int _size) {
        top = -1;
        size = _size;
        array = new string[size];
    }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == size - 1; }
    string pop() { return !isEmpty() ? array[top--] : ""; }
    void push(string value) {
        if (!isFull()) {
            array[++top] = value;
            return;
        }
        cout << "\t\tSTACK IS FULL!" << endl;
    }
};

/* STACK CLASS FOR CHARACTER TYPE DATA */
class STACK {
private:
    char* array;
    int top;
    int size;
public:
    STACK() {
        top = -1;
        size = 10;
        array = new char[size];
    }
    STACK(int _size) {
        size = _size;
        top = -1;
        array = new char[size];
    }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == size - 1; }
    char peek() { return (!isEmpty() ? array[top] : '0'); }
    char pop() { return !isEmpty() ? array[top--] : NULL; }

    void push(char value) {
        if (!isFull()) { array[++top] = value; }
        else { cout << "\t\tSTACK IS FULL!" << endl; }
    }
};

/*HELPER FUNCTIONS*/
string expressionConcatenator(string a, string b, string c) { return a + b + c; }
bool isOperand(char ch) {
    return ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122));
}
bool isOperator(char ch) {
    return (ch == '*' || ch == '/' || ch == '-' || ch == '+' || ch == '^');
}
int precendenceChecker(char ch) {
    return ((ch == '^') ? 3 : (ch == '*' || ch == '/') ? 2 : (ch == '+' || ch == '-') ? 1 : -1);
}

/*FUNCTION TO DISPLAY CONVERSION TIMER*/
void converting()
{
    system("CLS");
    int msec = 50;
    cout << "\n\n\n\n\t\t\t\t...............CONVERTING...............\n\n\t\t\t\t";
    for (int i = 0; i < 40; i++)
    {
        // clock function return the time taken by program during execution till now
        long goal = msec + (clock());
        while (goal > (clock()))
            ;
        cout << char(254);
    }
    system("CLS");
}

// FUNCTION TO CHECK EXPRESSION IS BALANCED OR NOT
bool isBalanaced(string exp) {
    int openingCount = 0, closingCount = 0;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            openingCount++;
        }
        if (exp[i] == ')') {
            closingCount++;
        }
    }
    return (openingCount == closingCount);
}

// FUNCTION TO REVERSE AN EXPRESSION
string reverse(string str) {
    string reverse;
    int l = str.length();
    int index = l;
    for (int i = 0; i < l; i++) {
        index--;
        if (str[index] == '(') {
            reverse += ')';
        }
        else if (str[index] == ')') {
            reverse += '(';
        }
        else {
            reverse += str[index];
        }
    }
    return reverse;
}

/*FUNCTION TO CONVERT INFIX EXPRESSION TO POSTFIX AND PREFIX EXPRESSION*/
string infixToPostAndPrefix(string infix) {
    if (!isBalanaced(infix)) {
        cout << "\t\tEXPRESSION ENTERED IS NOT BALANCED. RETURNING SAME EXPRESSION! " << endl;
        return infix;
    }
    STACK s(infix.length());
    string resultingExpression = "";
    char temp = ' ', ch = ' ', topmost = ' ';

    for (int i = 0; i < infix.length(); i++) {
        ch = infix[i];//current index
        // if char is operator pushing it onto stack after comparing precedence with top char of stack
        if (isOperator(ch)) {
            topmost = s.peek();
            do {//comparing precedences to add to stack
                if (precendenceChecker(topmost) >= precendenceChecker(ch) && ch != '^') {
                    resultingExpression += s.pop();//remove from stack, add toresultingExpression expression
                    topmost = s.peek();
                }
            } while (precendenceChecker(topmost) >= precendenceChecker(ch) && ch != '^');
            s.push(ch);
        }
        //if char is '(' adding to stack
        if (ch == '(') {
            s.push(ch);
        }
        //if char is ')' poping all elements from the stack until '('
        if (ch == ')') {
            do {
                temp = s.pop();
                if (temp != '(')
                {
                    resultingExpression += temp;
                }
            } while (temp != '(');
        }
        //checking if char operand
        if (isOperand(ch))
        {
            resultingExpression += ch;
        }
    }
    //at the end emptying the stack and adding all data to resulting Expression 
    while (topmost = s.pop()) {
        resultingExpression += topmost;
    }
    return resultingExpression;
}

/*FUNCTION TO CONVERT POSTFIX AND PREFIX EXPRESSION TO INFIX EXPRESSION*/
string inputAndPrefixToInfix(string input) {
    string infix = "";
    StringStack s(input.length());
    string current = "";
    string first = "", second = "";

    //scanning infix expression
    for (int i = 0; i < input.length(); i++) {
        current = input[i];
        //if operand push into stack
        if (isOperand(current[0])) {
            s.push(current);
        }
        //if operator pop two element from stack and make infix by adding operator b/w them
        if (isOperator(current[0])) {
            first = s.pop();
            second = s.pop();
            infix = second + current + first;//operand + operator + operand
            s.push(infix);
        }
    }
    return infix;
}

/*FUNCTION TO CONVERT POSTFIX EXPRESSION TO PREFIX EXPRESSION*/
string postToPre_And_PreToPost(string input, string check) {
    string output = "";
    StringStack s(input.length());
    string current = "";
    string first = "", second = "";
    //scanning infix expression
    for (int i = 0; i < input.length(); i++) {
        current = input[i];
        //if numeric digit ot alphabet push into stack
        if (isOperand(current[0])) {
            s.push(current);
        }
        //if operator pop two element from stack and make infix by adding operator b/w them
        if (isOperator(current[0])) {
            first = s.pop();
            second = s.pop();
            output = (check == "POST") ? expressionConcatenator(current, second, first)
                : expressionConcatenator(first, second, current);
            s.push(output);
        }
    }
    return (output);
}
// DISPLAYING FORMATTED MENU
void menuDisplayer() {
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|=====>   BCS221093   <=====|xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx| EXPRESSION CONVERTER MENU |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   1: INFIX TO POSTFIX     |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   2: INFIX TO PREFIX      |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   3: POSTFIX TO INFIX     |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   4: PREFIX TO INFIX      |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   5: POSTFIX TO PREFIX    |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   6: PREFIX TO POSTFIX    |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxx|   0: EXIT FROM PROGRAM    |xxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;
    cout << " \t\t|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|" << endl;

}

int main() {
    system("Color 3E"); // setting screen and font color 
    int choice = 0;
    string input = "";
    while (1) {
        system("CLS");
        menuDisplayer();
        cout << "\n\t\tENTER YOUR CHOICE ==>   ";
        do {
            cin >> choice;
            if (choice < 0 || choice > 6) {
                cout << "\t\tINVALID CHOICE ! RE-ENTER  ==>  ";
            }
        } while (choice < 0 || choice > 6);

        cout << "\n\n";
        switch (choice) {
        case 1: {
            cout << "\t\tENTER INFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            cout << "\n\n\t\t\t" << input << "   ==>   " << infixToPostAndPrefix(input) << endl;
            break;
        }
        case 2: {
            cout << "\t\tENTER INFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            /*we are passing input after reversing it and when it is converted we again reverse it before printting
            bcz this is requirement of conversion from infix to prefix*/
            cout << "\n\n\t\t\t" << input << "   ==>   " << reverse(infixToPostAndPrefix(reverse(input))) << endl;
            break;
        }
        case 3: {
            cout << "\t\tENTER POSTFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            cout << "\n\n\t\t\t" << input << "   ==>   " << inputAndPrefixToInfix(input) << endl;
            break;
        }
        case 4: {
            cout << "\t\tENTER PREFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            /*we are passing input expression after reversing it and when it is converted we again reverse it before printting
            bcz this is requirement of conversion from prefix to infix*/
            cout << "\n\n\t\t\t" << input << "   ==>   " << reverse(inputAndPrefixToInfix(reverse(input))) << endl;
            break;
        }
        case 5: {
            cout << "\t\tENTER POSTFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            cout << "\t\t\t" << input << "   ==>   " << postToPre_And_PreToPost(input, "POST") << endl;
            break;
        }
        case 6: {
            cout << "\t\tENTER PREFIX EXPRESSION  : ";
            cin.ignore();
            getline(cin, input);
            converting();
            cout << "\n\n\t\t\t" << input << "   ==>   " << postToPre_And_PreToPost(reverse(input), "PRE") << endl;
            break;
        }
        case 0: {
            return 0;
        }
        }
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        system("PAUSE");
    }
    return 0;
}
