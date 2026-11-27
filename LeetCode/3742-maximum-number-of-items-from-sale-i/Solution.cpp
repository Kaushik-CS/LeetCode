class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = 1501;
        int cheapIndex = 0;

        for (int i = 0; i < n; i++) {
            if (items[i][1] < minPrice) {
                minPrice = items[i][1];
                cheapIndex = i;
            }
        }

        vector<int> freeItems(n, 0);

        // Step 1: Calculate free items
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    freeItems[i]++;
                }
            }
        }

        // Step 2: Knapsack DP
        vector<vector<int>> dp(budget + 1, vector<int>(2, -1));

        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int value = 1 + freeItems[i];
            int cheap = (i == cheapIndex);

            for (int j = budget; j >= price; j--) {
                for (int k = 0; k <= 1; k++) {
                    if (dp[j - price][k] != -1) {
                        int nk = k | cheap;

                        dp[j][nk] = max(
                            dp[j][nk],
                            dp[j - price][k] + value
                        );
                    }
                }
            }
        }

        // Step 3: Calculate maximum answer
        int ans = 0;

        for (int i = 0; i <= budget; i++) {
            int remaining = budget - i;

            // Cheapest item already activated
            if (dp[i][1] != -1) {
                int extra = remaining / minPrice;

                ans = max(ans, dp[i][1] + extra);
            }

            // Cheapest item not yet activated
            if (dp[i][0] != -1) {
                int extra = remaining / minPrice;

                if (remaining >= minPrice) {
                    extra += freeItems[cheapIndex];
                }

                ans = max(ans, dp[i][0] + extra);
            }
        }

        return ans;
    }
};