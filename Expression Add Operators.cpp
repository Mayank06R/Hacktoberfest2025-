#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> result;

    void backtrack(string &s, int target, int pos, long currVal, long prevVal, string expr) {
        // base case: if we reached the end of the string
        if (pos == s.size()) {
            if (currVal == target) {
                result.push_back(expr);
            }
            return;
        }

        for (int i = pos; i < s.size(); i++) {
            // avoid numbers with leading zeros
            if (i > pos && s[pos] == '0') break;

            string currStr = s.substr(pos, i - pos + 1);
            long currNum = stol(currStr);

            if (pos == 0) {
                // first number, start expression
                backtrack(s, target, i + 1, currNum, currNum, currStr);
            } else {
                // try '+'
                backtrack(s, target, i + 1, currVal + currNum, currNum, expr + "+" + currStr);

                // try '-'
                backtrack(s, target, i + 1, currVal - currNum, -currNum, expr + "-" + currStr);

                // try '*'
                backtrack(s, target, i + 1, currVal - prevVal + prevVal * currNum, prevVal * currNum, expr + "*" + currStr);
            }
        }
    }

    vector<string> findExpr(string &s, int target) {
        result.clear();
        backtrack(s, target, 0, 0, 0, "");
        sort(result.begin(), result.end()); // required in lexicographically smallest order
        return result;
    }
};
