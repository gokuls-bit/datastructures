class Solution {
public:
    int digitProduct(int x) {

        int product = 1;

        while (x > 0) {

            product *= (x % 10);

            x /= 10;
        }

        return product;
    }

    int smallestNumber(int n, int t) {

        while (true) {

            if (digitProduct(n) % t == 0) {

                return n;
            }

            n++;
        }
    }
};
