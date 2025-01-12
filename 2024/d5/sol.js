//Day 5 solution for 2024
// console.log(process.argv.slice(2))
const readlines = require('n-readlines');

var filename = process.argv[2];
// console.log(filename)

var rules = Array();
var updates = Array();

var liner = new readlines(filename);

var reading_rules = true;
var p1_total = 0;
var p2_total = 0;

function checkIfValidUpdate(update)
{
    var is_valid = true;

    for(var i = 0; i < rules.length; i++) {
        if(update.includes(rules[i][0]) && update.includes(rules[i][1])) {
            //console.log("This is a relevant rule.")
            if(update.indexOf(rules[i][0]) > update.indexOf(rules[i][1])) {
                // console.log(update);
                // console.log(rules[i]);
                is_valid = false;
            }
        }
    }

    return is_valid;
}

//It is assumed that by this point the update is bad. We need to correct it and return an array with the right ordering.
function correct_the_incorrect_update(update)
{
    var corrected_update = update.slice();
    for(var i = 0; i < rules.length; i++) {
        if(corrected_update.includes(rules[i][0]) && corrected_update.includes(rules[i][1])) {
            //console.log("This is a relevant rule.")
            if(corrected_update.indexOf(rules[i][0]) > corrected_update.indexOf(rules[i][1])) {
                // console.log("This is a relevant rule that needs to be addressed.")
                // console.log("Index " + corrected_update.indexOf(rules[i][0]) + " needs to come before index " + corrected_update.indexOf(rules[i][1]));
                //Just take the bad higher end and move it just before the one it needs to be before
                var needs_to_be_first_index = corrected_update.indexOf(rules[i][0]);
                var needs_to_be_after_index = corrected_update.indexOf(rules[i][1]);
                var item_to_insert = corrected_update[needs_to_be_first_index];
                //Remove that item from the array now before creating the new one
                corrected_update = corrected_update.slice(0, needs_to_be_first_index).concat(corrected_update.slice(needs_to_be_first_index+1));
                corrected_update = corrected_update.slice(0, needs_to_be_after_index).concat(item_to_insert).concat(corrected_update.slice(needs_to_be_after_index));
                i=0;
            }
        }
    }
    //console.log("Original: " + update);
    //console.log("Corrected update: " + corrected_update);
    //console.log(corrected_update);

    return corrected_update;
}

while(line = liner.next()) {
    line = line.toString('ascii').trim();
    if(line == "") {
        reading_rules = false;
        continue;
    }
    if(reading_rules == true) {
        rules.push(line.split('|'));
    } else {
        var update = line.split(',');
        if(checkIfValidUpdate(update) == true) {
            p1_total += parseInt(update[Math.floor(update.length / 2)], 10);
        } else {
            correct_update = correct_the_incorrect_update(update);
            p2_total += parseInt(parseInt(correct_update[Math.floor(correct_update.length/2)], 10));
        }
    }
}

console.log("Part 1 total: " + p1_total);
console.log("Part 2 total: " + p2_total);
// console.log(rules);
