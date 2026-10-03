class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        // Easy peasy:
        // Convert integer to string and check if any mirror letters
        // break the rule.
        std::string xstr = std::to_string(x);
        const int xstr_len = xstr.length();
        for (int i=0; i<(xstr_len/2); i++) {
            if (xstr[i] !=  xstr[xstr_len - i - 1]) {
                return false;
            }
        }
        return true;
    }
};
