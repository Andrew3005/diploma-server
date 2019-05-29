const express = require("express");
const app = express();
var ffi = require('ffi')
var ref = require('ref')
var ArrayType = require('ref-array')
const cors = require('cors');

const performance = require('perf_hooks').performance;
const LU = require('./lu');

const port = process.env.PORT || 3000;

app.use(express.static(__dirname + '/dist/client'));

app.get('/*', function (req, res) {
    res.sendFile(path.join(__dirname + '/dist/client/index.html'));
});

app.use(cors());
app.use(express.json());

app.post("/calculate", (req, res) => {
    console.log('request');
    const { array } = req.body;

    var float = ref.types.float;
    var floatArrayType = ArrayType(float);
    var floatArr = new floatArrayType(array.length);
    var int = ref.types.int;

    var library = ffi.Library('./build/Release/result', {
        "LUdecomposition": [int, [floatArrayType, floatArrayType, floatArrayType, int, int]]
    })

    const readyToUseArray = new floatArrayType(prepareArrsay(array));
    let l = new floatArrayType(readyToUseArray.length);
    let u = new floatArrayType(readyToUseArray.length);


    var t1 = performance.now();
    library.LUdecomposition(readyToUseArray, l, u, array.length, array[0].length);
    const cppTime = performance.now() - t1;

    t1 = performance.now();
    const jsResult = LU(array);
    const jsTime = performance.now() - t1;

    res.send({ code: 200, results: { js: { time: jsTime, result: jsResult }, cpp: { time: cppTime, result: {lower: l, upper: u} } } });

});

app.listen(port, (req, res) => {
    console.log(`server has started at ${port} port`)
});


function prepareArray(array) {
    const resArray = [];

    for (let i = 0; i < array.length; i++) {
        for (let j = 0; j < array[0].length; j++) {
            resArray.push(array[i][j]);
        }
    }
    return resArray;
}