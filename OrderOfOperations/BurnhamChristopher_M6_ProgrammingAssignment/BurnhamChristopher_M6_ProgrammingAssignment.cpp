#include <iostream>
#include <string>
#include <stack>

using namespace std;

int order(char sign) 
{
    if (sign == '+' || sign == '-')
    {
        return 1;
    }        
    if (sign == '*' || sign == '/')
    {
        return 2;
    }        
    return 0;
}


int applySign(int a, int b, char op) 
{
    switch (op) 
    {
    case '+': 
        return a + b;
    case '-': 
        return a - b;
    case '*': 
        return a * b;
    case '/': 
        return a / b;
    default:
        return 0;
    }
}

/*evaluate expression*/
int evaluate(string x) {
    
    /*Variable storage stuff*/
    int i;    
    stack<int> values;
    stack<char> operators;

    for (i = 0; i < x.length(); i++) 
    {
        /*skip spaces if they are input*/
        if (x[i] == ' ')
        {
            continue;
        }
        /*if a parenthesis push to the operator stack*/
        else if (x[i] == '(') 
        {
            operators.push(x[i]);
        }
        /*push current digit*/
        else if (isdigit(x[i])) 
        {
            int val = 0;

            /*check for more than one digit in number*/
            while (i < x.length() && isdigit(x[i]))
            {
                val = (val * 10) + (x[i] - '0');
                i++;
            }

            values.push(val);
            i--;
        }               
        else if (x[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applySign(val1, val2, op));
            }

            
            if (!operators.empty())
                operators.pop();
        }
        /*if none of above is true, current is sign*/
        else
        {            
            while (!operators.empty() && order(operators.top()) >= order(x[i]))
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applySign(val1, val2, op));
            }

            operators.push(x[i]);
        }
    }
    /*apply remaining ops to remaining values (if any)*/
    while (!operators.empty())
    {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(applySign(val1, val2, op));
    }

    /*return top answer value*/
    return values.top();
}

int main() 
{
    cout << evaluate("5 + 3 * 9") << endl;
    cout << evaluate("20 * 3 + 2") << endl;
    cout << evaluate("5 * ( 6 + 2 )") << endl;
    cout << evaluate("80 * ( 6 + 1 ) / 13") << endl;
    cout << evaluate("(( 15 + 2 * 3 - 4 ) / 17 + ( 22 / 11 * 3)) * 101") << endl;

    int x = 1;
    string y;
    char z;
    
    while (x == 1)
    {
        cout << "Please enter your own equation to be evaluated." << endl;
        getline(cin, y);
        cout << y << endl;
        cout << evaluate(y) << endl;

        cout << "Continue? y/n" << endl;
        cin >> z;
        
        if (z == 'n' || z == 'N')
        {
            x = 0;
        }
        else
        {
            x = 1;
        }
        
        cin.ignore();
    }

    
}