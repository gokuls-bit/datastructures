class Solution {
public:

    struct Node {
        int left;
        int right;

        int prefix;
        int suffix;
        int best;

        Node() {
            left = 0;
            right = 0;
            prefix = 0;
            suffix = 0;
            best = 0;
        }

        Node(int l, int r) {
            left = l;
            right = r;
            prefix = 1;
            suffix = 1;
            best = 1;
        }
    };

    vector<Node> tree;
    string str;

    void build(int node, int left, int right) {

        tree[node] = Node(left, right);

        if (left == right) {
            return;
        }

        int mid = left + (right - left) / 2;

        build(node * 2, left, mid);

        build(node * 2 + 1, mid + 1, right);

        mergeNode(node);
    }

    void mergeNode(int node) {

        Node &current = tree[node];

        Node &L = tree[node * 2];

        Node &R = tree[node * 2 + 1];

        current.prefix = L.prefix;

        current.suffix = R.suffix;

        current.best = max(L.best, R.best);

        int leftLength = L.right - L.left + 1;

        int rightLength = R.right - R.left + 1;

        /*
            If the character at the boundary is the same,
            the suffix of the left interval can be joined
            with the prefix of the right interval.
        */
        if (str[L.right] == str[R.left]) {

            current.best = max(
                current.best,
                L.suffix + R.prefix
            );

            /*
                The entire left interval has the same
                character, so its prefix can extend into
                the right interval.
            */
            if (L.prefix == leftLength) {

                current.prefix =
                    leftLength + R.prefix;
            }

            /*
                The entire right interval has the same
                character, so its suffix can extend into
                the left interval.
            */
            if (R.suffix == rightLength) {

                current.suffix =
                    rightLength + L.suffix;
            }
        }
    }

    void update(int node, int position, char value) {

        if (tree[node].left == tree[node].right) {

            str[position] = value;

            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;

            return;
        }

        int mid =
            tree[node].left +
            (tree[node].right - tree[node].left) / 2;

        if (position <= mid) {

            update(node * 2, position, value);

        } else {

            update(node * 2 + 1, position, value);
        }

        mergeNode(node);
    }

    int longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        str = s;

        int n = str.size();

        tree.clear();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> answer;

        answer.reserve(queryIndices.size());

        for (int i = 0;
             i < queryIndices.size();
             i++) {

            int position = queryIndices[i];

            char newCharacter =
                queryCharacters[i];

            update(
                1,
                position,
                newCharacter
            );

            answer.push_back(tree[1].best);
        }

        return answer;
    }
};
