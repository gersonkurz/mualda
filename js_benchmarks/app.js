fs = require('fs');
now = require("performance-now");

// nr. of items in array
var COUNTING_SORT_NR_ELEMENTS = 1000000;

// range of numbers: 0..N-1
var COUNTING_SORT_MAX_ITEM = 10000;

function BuiltinSort(a) {
    return a.sort(function (a, b) { return a - b; });
}

var CreateEmptyArrayOfLength = function (n) {
    var result = [];
    for (var i = 0; i < n; ++i) {
        result.push(0);
    }
    return result;
}

var CreateArrayWithRandomValues = function (n) {
    var result = [];
    for (var i = 0; i < n; ++i) {
        result.push(Math.floor(Math.random() * COUNTING_SORT_MAX_ITEM));
    }
    return result;
}

var CountingSort = function (A) {
    var frequencies = CreateEmptyArrayOfLength(A.length);
    for (var item in A) {
        frequencies[item]++;
    }
    var writepos = 0;
    for (var readpos = 0; readpos < A.length; ++readpos) {
        for (var i = 0; i < frequencies[readpos]; ++i) {
            A[writepos++] = readpos;
        }
    }
    return A;
}


var IsSorted = function (A) {
    var expected = A[0];
    for (var i = 1; i < A.length; ++i) {
        var item = A[i];
        if (item < expected)
            return false;
        
        expected = item;
    }
    return true;
}

var ljust = function (val, n) {
    val = "" + val;
    while (val.length < n)
        val += " ";
    return val;
}

var EvaluateSortingMethod = function (sortingMethod, sortingMethodName) {
    var repeat = 10;
    
    var totalTime = 0;
    var maxTime = 0;
    var minTime = 0;
    for(var r = 0; r < repeat; ++r) {

        var array = CreateArrayWithRandomValues(COUNTING_SORT_NR_ELEMENTS);
        console.assert(!IsSorted(array));
        var startTime = now();
        array = sortingMethod(array);
        var elapsedTime = now() - startTime;
        console.assert(IsSorted(array));

        if (r == 0) {
            totalTime = elapsedTime;
            minTime = elapsedTime;
            maxTime = elapsedTime;
        }
        else {
            totalTime += elapsedTime;
            if (elapsedTime < minTime)
                minTime = elapsedTime;
            if (elapsedTime > maxTime)
                maxTime = elapsedTime;
        }
    }
    var averageTime = totalTime / repeat;
    console.log(ljust(sortingMethodName, 30) + " " + ljust(Math.floor(averageTime), 10) + " " + ljust(Math.floor(maxTime), 10) + " " + ljust(Math.floor(minTime), 10));
}

var TestCountingSort = function () {
    console.log("--- Counting Sort in Javascript ---");
    console.log("- Sample size: " + COUNTING_SORT_NR_ELEMENTS + " integers in the range [0.." + (COUNTING_SORT_MAX_ITEM-1) + "]");
    console.log("")
    console.log("                        Method    Average        Max        Min");
    console.log("----------------------------------------------------------------------------------------------------");

    EvaluateSortingMethod(CountingSort, "CountingSort");
    EvaluateSortingMethod(BuiltinSort, "BuiltinSort");
}

TestCountingSort();
console.log("[PRESS ANY KEY TO CLOSE THIS WINDOW]");
