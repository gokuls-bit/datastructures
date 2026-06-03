
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        int k = 0;

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] != val) {
                nums[k++] = nums[i];
            }
        }

        return k;
    }
};


# 12. Find First Occurrence in a String (strStr)

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {

        int n = haystack.size();
        int m = needle.size();

        for (int i = 0; i <= n - m; i++) {

            int j = 0;

            while (j < m && haystack[i + j] == needle[j])
                j++;

            if (j == m)
                return i;
        }

        return -1;
    }
};
```

---

# 13. Divide Two Integers

```cpp
class Solution {
public:
    int divide(int dividend, int divisor) {

        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long dvd = llabs((long long)dividend);
        long long dvs = llabs((long long)divisor);

        long long ans = 0;

        for (int i = 31; i >= 0; i--) {

            if ((dvd >> i) >= dvs) {

                ans += (1LL << i);
                dvd -= (dvs << i);
            }
        }

        if ((dividend < 0) ^ (divisor < 0))
            ans = -ans;

        return (int)ans;
    }
};
```

---

# 14. Asteroids Destroyed

```cpp
class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {

        sort(asteroids.begin(), asteroids.end());

        long long currMass = mass;

        for (int asteroid : asteroids) {

            if (currMass < asteroid)
                return false;

            currMass += asteroid;
        }

        return true;
    }
};
```

---

# 15. Minimum Cost of Buying Candies With Discount

```cpp
class Solution {
public:
    int minimumCost(vector<int>& cost) {

        sort(cost.begin(), cost.end(), greater<int>());

        int total = 0;

        for (int i = 0; i < cost.size(); i++) {

            if ((i + 1) % 3 != 0)
                total += cost[i];
        }

        return total;
    }
};
```

---

# 16. Number of Ways to Paint N × 3 Grid

```cpp
class Solution {
public:
    int numOfWays(int n) {

        const long long MOD = 1e9 + 7;

        long long aba = 6;
        long long abc = 6;

        for (int i = 2; i <= n; i++) {

            long long newAba =
                (aba * 3 + abc * 2) % MOD;

            long long newAbc =
                (aba * 2 + abc * 2) % MOD;

            aba = newAba;
            abc = newAbc;
        }

        return (aba + abc) % MOD;
    }
};
```

---

# 17. Minimum Element After Replacement With Digit Sum

```cpp
class Solution {
public:

    int digitSum(int n) {

        int sum = 0;

        while (n) {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }

    int minElement(vector<int>& nums) {

        int ans = INT_MAX;

        for (int num : nums) {
            ans = min(ans, digitSum(num));
        }

        return ans;
    }
};
```

---

# 18. Count Special Characters II

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {

        vector<int> lastLower(26, -1);
        vector<int> firstUpper(26, -1);

        for (int i = 0; i < word.size(); i++) {

            char c = word[i];

            if (islower(c)) {

                lastLower[c - 'a'] = i;
            }
            else {

                int idx = c - 'A';

                if (firstUpper[idx] == -1)
                    firstUpper[idx] = i;
            }
        }

        int count = 0;

        for (int i = 0; i < 26; i++) {

            if (lastLower[i] != -1 &&
                firstUpper[i] != -1 &&
                lastLower[i] < firstUpper[i]) {

                count++;
            }
        }

        return count;
    }
};
```

---

# 19. Password Strength

```cpp
class Solution {
public:
    int passwordStrength(string password) {

        unordered_set<char> seen;

        int strength = 0;

        for (char c : password) {

            if (seen.count(c))
                continue;

            seen.insert(c);

            if (islower(c))
                strength += 1;
            else if (isupper(c))
                strength += 2;
            else if (isdigit(c))
                strength += 3;
            else
                strength += 5;
        }

        return strength;
    }
};
```

---

# 20. Limit Occurrences

```cpp
class Solution {
public:
    vector<int> limitOccurrences(vector<int>& nums, int k) {

        unordered_map<int, int> freq;

        vector<int> ans;

        for (int num : nums) {

            if (freq[num] < k) {

                ans.push_back(num);
                freq[num]++;
            }
        }

        return ans;
    }
};
```

---

# 21. Earliest Finish Time for Land and Water Rides I

```cpp
class Solution {
public:

    int calc(vector<int>& start1,
             vector<int>& dur1,
             vector<int>& start2,
             vector<int>& dur2) {

        int earliestEnd = INT_MAX;

        for (int i = 0; i < start1.size(); i++) {
            earliestEnd =
                min(earliestEnd,
                    start1[i] + dur1[i]);
        }

        int ans = INT_MAX;

        for (int i = 0; i < start2.size(); i++) {

            ans = min(ans,
                max(earliestEnd,
                    start2[i]) + dur2[i]);
        }

        return ans;
    }

    int earliestFinishTime(
        vector<int>& landStartTime,
        vector<int>& landDuration,
        vector<int>& waterStartTime,
        vector<int>& waterDuration) {

        int landFirst =
            calc(landStartTime,
                 landDuration,
                 waterStartTime,
                 waterDuration);

        int waterFirst =
            calc(waterStartTime,
                 waterDuration,
                 landStartTime,
                 landDuration);

        return min(landFirst, waterFirst);
    }
};
```

---

# 22. Check Reachability in Binary String (Jump Game VII)

```cpp
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {

        int n = s.size();

        vector<bool> visited(n, false);

        queue<int> q;

        q.push(0);
        visited[0] = true;

        int farthest = 0;

        while (!q.empty()) {

            int i = q.front();
            q.pop();

            if (i == n - 1)
                return true;

            int start =
                max(i + minJump,
                    farthest + 1);

            int end =
                min(i + maxJump,
                    n - 1);

            for (int j = start;
                 j <= end;
                 j++) {

                if (s[j] == '0') {

                    visited[j] = true;
                    q.push(j);
                }
            }

            farthest = end;
        }

        return false;
    }
};
```

---

### Remaining Major Problems Not Yet Included

* Minimum Effort Tasks (Greedy)
* String Indices (Trie)
* Prime Teleportation (BFS + SPF)
* Substring with Concatenation of All Words
* Minimum Moves to Make Array Complementary
* Block Placement Queries
* Any others you asked that need longer implementations

Those are larger solutions and fit well into a **Batch 3 (Advanced Problems)**.

