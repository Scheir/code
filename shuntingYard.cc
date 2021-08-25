/*
  Implementation of the Shunting Yard algorithm which solves the codewars task:
  https://www.codewars.com/kata/52a78825cdfc2cfc87000005/
  The unary '-' complicated things and made the code a bit ugly.
  To be refactored.
*/
#include <string>
#include <stack>
#include <regex>
using namespace std;

vector<string> parseInput(string expression){
  vector<string> vec;
  bool prevOper = false;
  for(int i = 0; i < expression.size(); i++){
    char c = expression[i];
    if(c == '-'){
      string temp("-");
      if(isdigit(expression[i+1])){
        if(prevOper || i == 0)
          temp = "#";
        vec.push_back(temp);
      }
      else if(expression[i+1] == '('){
        string temp = "-";
        if(prevOper || i == 0){
          temp = "#";
        }
        vec.push_back(temp);
      }
      else
        vec.push_back(temp);
      prevOper = true;
    }
    else if(isdigit(c)){
      prevOper = false;
      string temp;
      temp.push_back(c);
      c = expression[i+1];
      while(isdigit(c) || c == '.'){
        temp.push_back(c);
        i++;
        c = expression[i+1];
      }
      vec.push_back(temp);
    }
    else if(c != ' '){
      string temp; temp.push_back(c);
      vec.push_back(temp);
      prevOper = true;
    }
  }
  for(auto x : vec)
    cout << x << endl;
  return vec;
}

double calc(std::string expression) {
  auto vec = parseInput(expression);
  
  //Shunting yard algorithm
  stack<double> number;
  stack<char> oper;
  for(auto x : vec){
    regex re(".*[0-9].*");
    smatch m;
    cout << "Current:" << x << endl;
    if(regex_match(x, m, re)){
      number.push(stod(x));
    }
    else if(x == "("){
      oper.push(x[0]);
    }
    else if(x == ")"){
      while(oper.size() && oper.top() != '('){
        if(oper.top() == '#'){
          double a = number.top();
          number.pop();
          number.push(-a);
        }
        else{
          double a = number.top();
          number.pop();
          double b = number.top();
          number.pop();
          switch(oper.top()){
              case '+': number.push(a+b);
                break;
              case '-': number.push(b-a);
                break;
              case '*': number.push(a*b);
                break;
              case '/': number.push(b/a);
              break;
          }
        }
        oper.pop();
      }
      oper.pop();
    }
    else if(x == "#"){
      oper.push(x[0]);
    }
    else{
      if(x == "*" || x == "/"){
        while(oper.size() && oper.top() != '(' && oper.top() != '+' && oper.top() != '-'){
          if(oper.top() == '#'){
            double a = number.top();
            number.pop();
            number.push(-a);
          }
          else{
            double a = number.top();
            number.pop();
            double b = number.top();
            number.pop();
            switch(oper.top()){
              case '*': number.push(a*b);
                break;
              case '/': number.push(b/a);
            }
          }
          oper.pop();
        }
      }
      else{
        while(oper.size() && oper.top() != '('){
          if(oper.top() == '#'){
            double a = number.top();
            number.pop();
            number.push(-a);
          }
          else{
            double a = number.top();
            number.pop();
            double b = number.top();
            number.pop();
            switch(oper.top()){
              case '*': number.push(a*b);
                break;
              case '/': number.push(b/a);
                break;
              case '+': number.push(a+b);
                break;
              case '-': number.push(b-a);
            }
          }
          oper.pop();
        }
      }
      oper.push(x[0]);
    }
  }
  while(oper.size())
	{
    if(oper.top() == '#'){
      double a = number.top();
      number.pop();
      number.push(-a);
    }
    else{
      double a = number.top();
      number.pop();
      double b = number.top(); 
      number.pop();
      switch(oper.top()){
        case '*': number.push(a*b);
          break;
        case '/': number.push(b/a);
          break;
        case '+': number.push(a+b);
          break;
        case '-': number.push(b-a);
      }
    }
		oper.pop();
	}
  return number.top();
}
