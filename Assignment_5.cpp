#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// function to print lcs
string findLCS(string s1, string s2) {
    int str1_l = s1.size();
    int str2_l = s2.size();
    vector<vector<int>> lkup_tabl(str1_l+1, vector<int>(str2_l+1, 0)); //
    int max_len = 0;
    int end_pos = 0;

    // fill the look_up table
    for (int i = 1; i <= str1_l; i++) {
        for (int j = 1; j <= str2_l; j++) {
            if (s1[i-1] == s2[j-1]) {
                lkup_tabl[i][j] = lkup_tabl[i-1][j-1] + 1;
                if (lkup_tabl[i][j] > max_len) {
                    max_len = lkup_tabl[i][j];
                    end_pos = i - 1;
                }
            }
        }
    }

    // look up table
    std::cout << "--------------------------------------------" << endl;
    std::cout << "Lookup Table: " << endl;
    std::cout << "    ";
    for (int j = 0; j < str2_l; j++) {
        std::cout << s2[j] << " ";
    }
    std::cout << endl;
    for (int i = 0; i <= str1_l; i++) {
        if (i > 0) {
            std::cout << s1[i-1] << " ";
        } else {
            std::cout << "  ";
        }
        for (int j = 0; j <= str2_l; j++) {
            std::cout << lkup_tabl[i][j] << " ";
        }
        std::cout << endl;
    }

    
    cout << "Length of the largest common substring: " << max_len << endl;

    return s1.substr(end_pos - max_len + 1, max_len); // return the longest common substring
}

//main function
int main() {
    string s1, s2;
    std::cout << "Enter first string: ";
    std::cin >> s1;
    std::cout << "Enter second string: ";
    std::cin >> s2;
    string lngst_cmn_substring = findLCS(s1, s2); // Calling the findLCS function
    std::cout << "Longest Common Substring: " << lngst_cmn_substring << endl;
    return 0;
}
