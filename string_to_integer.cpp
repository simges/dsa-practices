class Solution {
    static constexpr std::string WHITESPACE{" "};
private:
    int from_char_to_int(const char& c) {
        int res = 0;
        switch(c) {
        case '1': res = 1;
            break;
        case '2': res = 2;
            break;
        case '3': res = 3;
            break;
        case '4': res = 4;
            break;
        case '5': res = 5;
            break;
        case '6': res = 6;
            break;
        case '7': res = 7;
            break;
        case '8': res = 8;
            break;
        case '9': res = 9;
            break;
        case '0':
        default: res = 0;
            break;
        }
        return res;
    }
public:
    int myAtoi(string s) {
        // operate on read-only view of our original string
        std::string::size_type pos = s.find_first_not_of(WHITESPACE);
        if (pos == std::string::npos) {
            return 0;
        }
        if (pos != 0) {
            s = s.substr(pos, std::string::npos);
        }
        
        bool is_minus = false;
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
            if (s[0] == '-') {
                is_minus = true;
            }
            // skip the signing character
            s = s.substr(1, std::string::npos);
        }

        std::string::iterator it = std::find_if(s.begin(), s.end(),
                [](const char& c) { return (int)c > (int)'9' || (int)c < (int)'0'; } );

        if (it != s.end()) {
            s = s.substr(0, std::distance(s.begin(), it));
        }

        // 1 skip leading 0s
        // emplace each char into the vector after canting to uint8_t
        int index=0;
        for (; index<s.size(); index++) {
            if (s[index] != '0') {
                break;
            }
        }
        s = s.substr(index, std::string::npos);
        if (s.size() > 10) {
            if (is_minus) {
                return std::numeric_limits<int>::min();
            } else {
                return std::numeric_limits<int>::max();
            }
        }

        signed long long ret = 0;
        for (int index=0; index<s.size(); index++) {
            ret += from_char_to_int(s[index]) * std::pow(10, s.size()-index-1);
        }
        ret = is_minus ? ret*(-1) : ret;

        if (ret < std::numeric_limits<int>::min()) {
            ret = std::numeric_limits<int>::min();
        } else if (ret > std::numeric_limits<int>::max()) {
            ret = std::numeric_limits<int>::max();
        }
        return static_cast<int32_t>(ret);
    }
};
