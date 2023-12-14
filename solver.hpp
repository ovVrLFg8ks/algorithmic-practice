#pragma once

#include <iostream>
#include <stack>
#include <map>
#include <cmath>
#include <algorithm>
#include <string>

#define ll long long int

using namespace std;

std::map<char, int> pr{
	{'(', 0},
	{')', 0},
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
	//{'~', 3}, 
	{'#', INT_MIN}
};

std::string conversion(std::string str) {
	str += '#';
	stack<string> nums;
	stack<char> ops;
	string out;
	string num;

	for (int i = 0; i < str.length(); i++) {
		if (pr.count(str[i])) {
			if (num.length()) {
				nums.push(num);
				num.clear();
			}
			while (!ops.empty() && pr[str[i]] <= pr[ops.top()]) {
				string temp;
				if ((!out.empty() && pr[out[out.length() - 2]] < pr[ops.top()]) || out.empty()) {
					temp = nums.top() + ' ';
					nums.pop();
				}
				if (!nums.empty()) {
					temp = nums.top() + ' ' + temp;
					nums.pop();
				}
				if (ops.top() == '(')
					out = out + temp;
				else
					out = out + temp + ops.top() + ' ';
				ops.pop();
			}
			if (str[i] != ')')
				ops.push(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9')
			num += str[i];
		else
			return "ERR";
	}
	return out;
}

std::string unary_minus(std::string& str) {
	if (str[0] == '-')
		str[0] = '~';
	for (int i = 1; i < str.length(); i++) {
		if (str[i] == '-' && str[i - 1] != ')' && pr.count(str[i - 1]))
			str[i] = '~';
	}
	return str;
}

bool checkParentheses(std::string& str) {
	int s = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			s++;
		else if (str[i] == ')') {
			s--;
			if (s < 0)
				return false;
		}
	}
	return s == 0;
}

std::string solver(std::string& str) {
	std::stack<double> s;
	int start = 0;
	str = str + ' ';

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			std::string t = str.substr(start, i - start);
			start = i + 1;
			if (t == "")
				continue;

			if (t == "+") {
				double tll = s.top();
				s.pop();
				tll += s.top();
				s.pop();
				s.push(tll);
			}
			else if (t == "-") {
				double tll = s.top();
				s.pop();
				tll = s.top() - tll;
				s.pop();
				s.push(tll);
			}
			else if (t == "*") {
				double tll = s.top();
				s.pop();
				tll *= s.top();
				s.pop();
				s.push(tll);
			}
			else if (t == "/") {
				double tll = s.top();
				s.pop();
				tll = s.top() / tll;
				s.pop();
				s.push(tll);
			}
			else if (t == "^") {
				double tll = s.top();
				s.pop();
				tll = pow(s.top(), tll);
				s.pop();
				s.push(tll);
			}
			else {
				try {
					s.push(stoll(t));
				}
				catch (const std::invalid_argument& e) {
					return "INVALID ARGUMENT";
				}
			}
		}
	}

	return std::to_string(s.top());
}

std::string entry(std::string str) {
	if (!checkParentheses(str))
		return "ERR";

	// remove spaces
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

	unary_minus(str);

	str = conversion(str);
	if (str == "ERR")
		return "ERROR";

	return solver(str);
}

#undef ll