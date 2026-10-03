class Solution {
    // The tricky point in this problem is that i was forbidden to use 
    // size64_t (unable to hold an 64 bit integer).
    // Through the flow, no 8byte value is employed.
    const size_t MAX_NUM_DIGITS = 10;
private:
    void next_reversed_digit(uint32_t x, std::deque<uint8_t>& digits) {
        if (x < 10 && x >= 0) {
            digits.push_back(x);
            return;
        }
        digits.push_back(x % 10);
        next_reversed_digit(x/10, digits);
    }

    bool compare(std::deque<uint8_t> digits, std::deque<uint8_t> max_digits) {
        if (digits.front() > max_digits.front()) {
            return false;
        } else if (digits.front() < max_digits.front()) {
            return true;
        } else {
            digits.pop_front();
            max_digits.pop_front();
            return compare(digits, max_digits);
        }
    }

    uint32_t absolute(int32_t x) {
        if (x >= 0) {
            return x;
        }
        return ((~(uint32_t)x)  + 1);
    }

public:
    int reverse(int x) {
        // max: 0111 1111 1111 1111 1111 1111 1111 1111
        int32_t max = 0x7FFFFFFF;
        // min: 1000 0000 0000 0000 0000 0000 0000 0000
        int32_t min = 0x80000000;

        // approach: take the abs and perform transformations
        // with absolute value.
        // the cross with -1 if the initial value is minus
        const bool is_minus = x > 0 ? false : true;

        // push all the digits of abs(max) value for futrher
        // check if the result remains in our range
        std::deque<uint8_t> max_digits;
        int32_t temp = max;
        for (int y = MAX_NUM_DIGITS; y > 0; y--) {
            uint8_t division = temp / std::pow(10, y-1);
            max_digits.push_back(division);
            temp = temp - (division * std::pow(10, y-1));
        }

        // reverse the digits and compare digit by digit
        // if our value is in teh range
        std::deque<uint8_t> x_reversed_digits;
        next_reversed_digit(absolute(x), x_reversed_digits);
        while (x_reversed_digits.size() < max_digits.size()) {
            x_reversed_digits.push_front(0);
        }

        // compare, return 0 if not in the region
        bool is_valid = compare(x_reversed_digits, max_digits);
        if (!is_valid) {
            return 0;
        }

        // calculate the final value if the reversed integer is valid.
        int32_t ret = 0;
        for (int i=x_reversed_digits.size()-1; i>=0; i--) {
            ret += std::pow(10, i) * x_reversed_digits.front();
            x_reversed_digits.pop_front();
        }
        return is_minus ? ret*-1 : ret;
    }
};
