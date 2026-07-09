function calculateScore(s) {
    let pos = {};
    let score = 0;

    for (let i = 0; i < s.length; i++) {
        let ch = s[i];

        // Find the mirror character
        let twin = String.fromCharCode(
            'a'.charCodeAt(0) + 'z'.charCodeAt(0) - ch.charCodeAt(0)
        );

        if (pos[twin] && pos[twin].length > 0) {
            let j = pos[twin].pop();
            score += i - j;
        } else {
            if (!pos[ch]) {
                pos[ch] = [];
            }
            pos[ch].push(i);
        }
    }

    return score;
}
