class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        vector<int> answer = {-1, -1};

        if (head == nullptr || head->next == nullptr ||
            head->next->next == nullptr) {
            return answer;
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next = curr->next;

        int position = 1;

        int firstCritical = -1;
        int previousCritical = -1;

        int minimumDistance = INT_MAX;
        int maximumDistance = 0;

        while (next != nullptr) {

            bool isLocalMaximum =
                (curr->val > prev->val &&
                 curr->val > next->val);

            bool isLocalMinimum =
                (curr->val < prev->val &&
                 curr->val < next->val);

            if (isLocalMaximum || isLocalMinimum) {

                if (firstCritical == -1) {

                    // First critical point.
                    firstCritical = position;

                } else {

                    // Distance from previous critical point.
                    int distance =
                        position - previousCritical;

                    minimumDistance =
                        min(minimumDistance, distance);

                    // Distance from first to current.
                    maximumDistance =
                        position - firstCritical;
                }

                previousCritical = position;
            }

            prev = curr;
            curr = next;
            next = next->next;

            position++;
        }

        // Fewer than two critical points.
        if (firstCritical == -1 ||
            firstCritical == previousCritical) {

            return {-1, -1};
        }

        return {
            minimumDistance,
            maximumDistance
        };
    }
};
