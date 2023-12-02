const fs = require("fs");

const file = fs.readFileSync("./input.txt", "utf-8");

const lines = file.split("\n");

const allNums = "1234567890".split("");

const pairs = lines.map(l => {
    const nums = l.split("").filter(c => allNums.includes(c));

    return parseInt(nums[0] + "" + nums.at(-1), 10);
});

console.log(pairs.length, pairs[0], pairs[999])

const sum = pairs.reduce((agg, i) => agg + i, 0);

console.log(sum);
