function moveZeroesToEnd(arr) {
    let result = [];
    let count = 0;

    for (let num of arr) {
        if (num !== 0) {
            result.push(num);
        } else {
            count++;
        }
    }

    while (count > 0) {
        result.push(0);
        count--;
    }

    return result;
}

// Do Not Edit This Part
const n = Number(prompt());
let arr = [];

for (let i = 0; i < n; i++) {
    arr.push(Number(prompt()));
}

const result = moveZeroesToEnd(arr);
console.log(result.join(" "));
