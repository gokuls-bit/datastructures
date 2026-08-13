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
class Solution {
public:

    struct Node {
        int leftChar;
        int rightChar;
        int prefix;
        int suffix;
        int best;

        Node() {
            leftChar = -1;
            rightChar = -1;
            prefix = 0;
            suffix = 0;
            best = 0;
        }
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {

        if (a.best == 0)
            return b;

        if (b.best == 0)
            return a;

        Node result;

        result.leftChar = a.leftChar;
        result.rightChar = b.rightChar;

        result.prefix = a.prefix;
        result.suffix = b.suffix;

        result.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar) {

            result.best = max(
                result.best,
                a.suffix + b.prefix
            );

            if (a.prefix == a.best) {
                result.prefix = a.prefix + b.prefix;
            }

            if (b.suffix == b.best) {
                result.suffix = b.suffix + a.suffix;
            }
        }

        return result;
    }

    void build(int node, int l, int r) {

        if (l == r) {

            tree[node].leftChar = s[l];
            tree[node].rightChar = s[l];

            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;

            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid);

        build(node * 2 + 1, mid + 1, r);

        tree[node] =
            merge(tree[node * 2],
                  tree[node * 2 + 1]);
    }

    void update(
        int node,
        int l,
        int r,
        int index,
        char value
    ) {

        if (l == r) {

            s[index] = value;

            tree[node].leftChar = value;
            tree[node].rightChar = value;

            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;

            return;
        }

        int mid = l + (r - l) / 2;

        if (index <= mid) {

            update(
                node * 2,
                l,
                mid,
                index,
                value
            );

        } else {

            update(
                node * 2 + 1,
                mid + 1,
                r,
                index,
                value
            );
        }

        tree[node] =
            merge(tree[node * 2],
                  tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        this->s = s;

        int n = s.size();

        tree.assign(4 * n + 5, Node());

        build(1, 0, n - 1);

        vector<int> answer;

        for (int i = 0;
             i < queryIndices.size();
             i++) {

            int index = queryIndices[i];

            char character = queryCharacters[i];

            update(
                1,
                0,
                n - 1,
                index,
                character
            );

            answer.push_back(tree[1].best);
        }

        return answer;
    }
};class Solution {
public:
    struct Node {
        int leftChar;
        int rightChar;
        int prefix;
        int suffix;
        int best;
        int size; // Added to track segment length

        Node() {
            leftChar = -1;
            rightChar = -1;
            prefix = 0;
            suffix = 0;
            best = 0;
            size = 0; 
        }
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.best == 0) return b;
        if (b.best == 0) return a;

        Node result;
        result.leftChar = a.leftChar;
        result.rightChar = b.rightChar;
        result.prefix = a.prefix;
        result.suffix = b.suffix;
        result.best = max(a.best, b.best);
        result.size = a.size + b.size; // Maintain size

        if (a.rightChar == b.leftChar) {
            result.best = max(result.best, a.suffix + b.prefix);

            // Corrected: Only extend if the entire left node is the same character
            if (a.prefix == a.size) {
                result.prefix = a.size + b.prefix;
            }

            // Corrected: Only extend if the entire right node is the same character
            if (b.suffix == b.size) {
                result.suffix = b.size + a.suffix;
            }
        }

        return result;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node].leftChar = s[l];
            tree[node].rightChar = s[l];
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            tree[node].size = 1; // Leaf size is 1
            return;
        }

        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int index, char value) {
        if (l == r) {
            s[index] = value;
            tree[node].leftChar = value;
            tree[node].rightChar = value;
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            tree[node].size = 1; // Leaf size is 1
            return;
        }

        int mid = l + (r - l) / 2;

        if (index <= mid) {
            update(node * 2, l, mid, index, value);
        } else {
            update(node * 2 + 1, mid + 1, r, index, value);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        this->s = s;
        int n = s.size();
        
        tree.assign(4 * n + 5, Node());
        build(1, 0, n - 1);

        vector<int> answer;
        for (int i = 0; i < queryIndices.size(); i++) {
            int index = queryIndices[i];
            char character = queryCharacters[i];
            
            update(1, 0, n - 1, index, character);
            answer.push_back(tree[1].best);
        }

        return answer;
    }
};
