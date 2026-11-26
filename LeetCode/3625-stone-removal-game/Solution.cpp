
class Solution {
public:
    bool canAliceWin(int n) {
        int stones = 10;

        while (n >= stones) {
            n -= stones;
            stones--;

            if (stones == 0) break;
        }

        return stones % 2 == 1;
    }
};
