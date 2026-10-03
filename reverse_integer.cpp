// The tricky point in this problem is that i was forbidden to use 
// size64_t (unable to hold an 64 bit integer).
// Through the flow, no 8byte value is employed.
class Solution {
    const size_t MAX_NUM_DIGITS = 10;
private:
    void reversed_digits(uint32_t x, std::deque<uint8_t>& digits) const {
        if (x < 10 && x >= 0) {
            digits.push_back(x);
            return;
        }
        digits.push_back(x % 10);
        reversed_digits(x/10, digits);
    }

    inline uint32_t absolute(int32_t x) const {
        if (x >= 0) {
            return x;
        }
        return ((~(uint32_t)x)  + 1);
    }

    uint32_t get_reversed_integer(std::deque<uint8_t>& digits, uint32_t max) const {
        int32_t ret = 0;
        bool in_range = false;
        for (uint8_t index = MAX_NUM_DIGITS; index > 0; index--) {
            uint8_t division = max / std::pow(10, index-1);
            max -= (division * std::pow(10, index-1));

            if (digits.front() < division) in_range = true;
            // check corresponding digits till ensuring that the value
            // is in range, or break when the equality is broken.
            if (in_range || digits.front() == division) {
                ret += std::pow(10, index-1) * digits.front();
                digits.pop_front();
            } else if (digits.front() > division) {
                return 0;
            }
        }
        return ret;
    }

public:
    int reverse(int x) const {
        // max: 0111 1111 1111 1111 1111 1111 1111 1111
        int32_t max = 0x7FFFFFFF;
        // min: 1000 0000 0000 0000 0000 0000 0000 0000
        int32_t min = 0x80000000;

        const bool is_minus = x > 0 ? false : true;


        // reverse the digits
        std::deque<uint8_t> x_digits;
        reversed_digits(absolute(x), x_digits);
        // Inserts n zeros at the end
        x_digits.insert(x_digits.begin(), MAX_NUM_DIGITS-x_digits.size(), 0);

        // if num_digits < MAX_NUM_DIGITS, then this is definitely in our range
        // if num_digits == MAX_NUM_DIGITS,
        //      compare them digit by digit until they are not equal
        //      mark the value is_valid=false if bigger than max value
        uint32_t ret = get_reversed_integer(x_digits, max);
        return is_minus ? ret*-1 : ret;
    }
};
