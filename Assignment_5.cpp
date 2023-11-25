#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to print the vector
string longestSubstring(string s1, string s2) {
    int string1_length = s1.size();
    int string2_length = s2.size();
    vector<vector<int>> lookup_table(string1_length+1, vector<int>(string2_length+1, 0)); //
    int maximum_length = 0;
    int end_position = 0;

    // Filling the lookup table
    for (int i = 1; i <= string1_length; i++) {
        for (int j = 1; j <= string2_length; j++) {
            if (s1[i-1] == s2[j-1]) {
                lookup_table[i][j] = lookup_table[i-1][j-1] + 1;
                if (lookup_table[i][j] > maximum_length) {
                    maximum_length = lookup_table[i][j];
                    end_position = i - 1;
                }
            }
        }
    }

    // Print the lookup table
    cout << "Lookup Table: " << endl;
    cout << "    ";
    for (int j = 0; j < string2_length; j++) {
        cout << s2[j] << " ";
    }
    cout << endl;
    for (int i = 0; i <= string1_length; i++) {
        if (i > 0) {
            cout << s1[i-1] << " ";
        } else {
            cout << "  ";
        }
        for (int j = 0; j <= string2_length; j++) {
            cout << lookup_table[i][j] << " ";
        }
        cout << endl;
    }

    // Print the length of the longest common substring
    cout << "Length of the largest common substring: " << maximum_length << endl;

    return s1.substr(end_position - maximum_length + 1, maximum_length); // return the longest common substring
}

// Defining the main function
int main() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;
    string longest_common_substring = longestSubstring(s1, s2); // Calling the longestSubstring function
    cout << "Longest Common Substring: " << longest_common_substring << endl;
    return 0;
}
