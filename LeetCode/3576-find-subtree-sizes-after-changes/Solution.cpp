
class Solution {
public:
    vector<int> answer;
    vector<int> newParent;
    vector<vector<int>> adj;
    vector<int> last;

    void dfs(int node, string &s) {
        int c = s[node] - 'a';

        int oldParent = last[c];

        if (node != 0 && oldParent != -1) {
            newParent[node] = oldParent;
        }

        last[c] = node;

        for (int child : adj[node]) {
            dfs(child, s);
        }

        last[c] = oldParent;
    }

    int getSize(int node) {
        int size = 1;

        for (int child : adj[node]) {
            size += getSize(child);
        }

        answer[node] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        answer.resize(n);
        newParent = parent;
        adj.resize(n);
        last.assign(26, -1);

        // Build the original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Find the closest matching ancestor
        dfs(0, s);

        // Build the modified tree
        adj.assign(n, {});

        for (int i = 1; i < n; i++) {
            adj[newParent[i]].push_back(i);
        }

        // Calculate final subtree sizes
        getSize(0);

        return answer;
    }
};
