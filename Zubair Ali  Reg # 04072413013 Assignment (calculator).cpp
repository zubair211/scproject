#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;
    int Top;
    int Size;

public:
    Stack(int size = 100) {
        Size = size;
        data = new T[Size];
        Top = -1;
    }
    ~Stack() {
        delete[] data;
    }

    void push(T val) {
        if (Top == Size - 1) {
            cout << "\nStack Overflow\n " << endl;
            return;
        }
        data[++Top] = val;
    }

    void pop() { 
        if (Empty()) {
            cout << "\nStack Underflow\n" << endl;
        }
         data[--Top];
    }

    T top() const {
        if (Empty()) {
            cout << "\nStack is underflow!" << endl;
            exit(1);
        }
        return data[Top];
    }

    bool Empty() const {
        return Top == -1;
    }
};

int operator_precedence(char opr) {
    if (opr == '+' || opr == '-')
      {
      	 return 1;
		} 
    if (opr == '*' || opr == '/')
       {
       	 return 2;
	   }
    if (opr == '^')
       {
       	return 3;
		}
		else{
			 return 0;
		} 
   
}

int evaluation(int value1, int value2, char opr) {
   
   if(opr=='+')
	{
		return value1 + value2;
	 } 
    if(opr=='-')
	{
	 return value1 - value2;	
	 }
   if(opr=='*')
{
		return value1 * value2;
	}
   if(opr=='/') 
      {
      	if (value2 == 0) 
		{
            cout << "Division by zero is not possible !\n";
            return 0;
        }
        return value1 / value2;
		}  
   if(opr=='^') 
       {
       	return pow(value1, value2); 
		} 
  //  }
   else{
   	 return 0;
   }
}

int evaluate(string str) {
    stack<int> values;
    stack<char> ops;

    for (int i = 0; i < str.size(); i++)
	 {
        if (str[i] == ' ')
          {
          	continue;
			} //end of if 
        if (str[i] == '-' && (i == 0 || str[i - 1] == '(' || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/'))
			  {
            i++;
            int val = 0;
            while (i < str.size() && isdigit(str[i]))
			 {
                val = val * 10 + (str[i] - '0');
                i++;
            }//end of while
            values.push(-val);
            i--;
            continue;
        }//end of if condition

        
        if (isdigit(str[i])) {
            int val = 0;
            while (i < str.size() && isdigit(str[i])) 
			{
                val = val * 10 + (str[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }//end of if
        else if (str[i] == '(')
          {
          	 ops.push('(');
			} //end of else if

        else if (str[i] == ')')
		 {
            while (!ops.empty() && ops.top() != '(')
			 {
                int val2 = values.top(); 
				values.pop();
                int val1 = values.top();
				 values.pop();
                char op = ops.top();
				 ops.pop();
                values.push(evaluation(val1, val2, op));
            }//end of while loop
            ops.pop();
        }//end of if else

        
        else {
            while (!ops.empty() && operator_precedence(ops.top()) >= operator_precedence(str[i])) 
			{
                int val2 = values.top();
				 values.pop();
                int val1 = values.top(); 
				values.pop();
                char op = ops.top();
				 ops.pop();
                values.push(evaluation(val1, val2, op));
            }//end of while loop
            ops.push(str[i]); 
        }//end of else
    }//end of for loop

        //if any thing remain in stack 
    while (!ops.empty()) 
	{
        int val2 = values.top();
		 values.pop();
        int val1 = values.top(); 
		values.pop();
        char op = ops.top(); 
		ops.pop();
        values.push(evaluation(val1, val2, op));
    }//end of while

    return values.top();
}

int main(int argc, char* argv[]) {
    string str;

    if (argc > 1) 
	{
        for (int i = 1; i < argc; i++)
		 {
            str += argv[i];
            if (i < argc - 1)
              {
              	 str += " ";
				} 
        }//end of for loop
        cout << "\nExpression =  " << str << endl;
        cout << "\nEvaluated Result = " << evaluate(str) << endl;
        return 0;
    }

    cout << "\nWelcome to Expression Evaluator Calculator\n";
    cout << "\ntype 'quit' to quit\n";
    cout << "\n-------------------------------------------\n";

    while (true) {
        cout << "\nEnter expression for evaluation =  ";
        getline(cin, str);
        if (str == "quit" || str == "Quit" || str == "QUIT")
            {
            break;	
			}
        if (str.empty())
          {
          	continue;
			}  

        cout << "Result = " << evaluate(str) << endl;
    }//end of while loop

    cout << "\nITS END OF CALCULATOR \n";
    cout << "\nThank you \n";
    return 0;
}//end of main
