
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // Step 1: Precompute substring costs
        vector<vector<int>> cost(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;
                int best = INF;

                // Try all proper divisors
                for (int d = 1; d < len; d++) {
                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Check palindrome groups
                    for (int offset = 0; offset < d; offset++) {

                        int left = offset;
                        int right = offset +
                                    ((len - 1 - offset) / d) * d;

                        while (left < right) {
                            if (s[i + left] != s[i + right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    best = min(best, changes);
                }

                cost[i][j] = best;
            }
        }

        // Step 2: DP
        vector<vector<int>> dp(
            k + 1, vector<int>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {
            for (int end = 2 * parts; end <= n; end++) {

                for (int start = 2 * (parts - 1);
                     start < end - 1; start++) {

                    dp[parts][end] = min(
                        dp[parts][end],
                        dp[parts - 1][start] +
                        cost[start][end - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
