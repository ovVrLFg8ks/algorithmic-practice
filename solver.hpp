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
	{'#', INT_MIN}
};

string conversion(string str) {
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
		else if (str[i] >= '0' && str[i] <= '9') {
			num += str[i];
		}
		else
			return "ERR";
	}

	return out;
}

/*
std::string magic1(std::string str) {
	std::stack<string> nums;
	std::stack<char> ops;
	std::string num;
	std::string out;

	for (int i = 0; i < str.length(); i++) {
		if (pr.count(str[i])) {
			if (!num.empty()) {
				nums.push(num);
				num.clear();
			}
			if (!ops.empty() && pr[str[i]] <= pr[ops.top()]) {
				out = nums.top() + out + ops.top();
				nums.pop(); ops.pop();
				if (!nums.empty()) {
					out = nums.top() + out;
					nums.pop();
				}
			}

			ops.push(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9') {
			num += str[i];
		}
		else
			return "ERR unnown char";
	}
	
	if (!num.empty())
		nums.push(num);

	while (!nums.empty()) {
		num = nums.top() + num;
		nums.pop();
	}
	while (!ops.empty()) {
		num = num + ops.top();
		ops.pop();
	}
	out += num;

	return out;
}
*/

bool checkParentheses(std::string str) {
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
	return (s == 0) ? true : false;
}

std::string parser(std::string str) {
	if (!checkParentheses(str))
		return "ERR";
	// remove spaces
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

	std::string out;


	return out;
}

std::string solver(std::string str) {
	std::stack<double> s;
	int start = 0;
	str = str + ' ';

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			std::string t = str.substr(start, i - start);
			start = i + 1;
			if (t == "")
				continue;
			/*
			if (s.size() < 2)
			goto addnum;
			*/
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
					return "WHAT";
				}
			}
		}
	}

	return std::to_string(s.top());
}
#undef ll