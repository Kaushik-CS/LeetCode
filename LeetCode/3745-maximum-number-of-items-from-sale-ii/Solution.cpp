class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        long long minPrice = LLONG_MAX;

        for (auto& x : items) {
            freq[x[0]]++;
            minPrice = min(minPrice, (long long)x[1]);
        }

        vector<int> gain(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                gain[i] += freq[j];
            }
            gain[i]--;
        }

        vector<pair<long long, int>> deals;

        for (auto& x : items) {
            int factor = x[0];
            long long price = x[1];

            if (gain[factor] > 0 && price < 2 * minPrice) {
                deals.push_back({price, gain[factor]});
            }
        }

        sort(deals.begin(), deals.end());

        long long ans = 0;
        long long remaining = budget;

        for (auto& d : deals) {
            long long price = d.first;
            long long count = d.second;

            long long buy = min(count, remaining / price);

            ans += buy * 2;
            remaining -= buy * price;
        }

        ans += remaining / minPrice;

        return (int)ans;
    }
};