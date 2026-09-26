class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> sum(2);
        // hold the indexes of the seen numbers to check
        // if we already traverse it further.
        std::unordered_map<int, int> seen;
        for (int i=0; i < nums.size(); i++) {
            int left = target - nums[i];
            if (seen.find(left) != seen.end()) {
                sum[0] = seen[left];
                sum[1] = i;
                break;
            }
            // add num, index pair to the seen map.
            seen[nums[i]] = i;
        }
        return sum;
    }
};
