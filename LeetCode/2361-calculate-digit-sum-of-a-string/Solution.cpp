
class Solution {
public:
    string digitSum(string s, int k) {

        while (s.length() > k) {
            string result = "";

            for (int i = 0; i < s.length(); i += k) {

                string group = s.substr(i, k);

                int sum = 0;

                for (char digit : group) {
                    sum += digit - '0';
                }

                result += to_string(sum);
            }

            s = result;
        }

        return s;
    }
};
