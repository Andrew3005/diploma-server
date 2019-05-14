const express = require("express");
const cors = require('cors');
const performance = require('perf_hooks').performance;
const app = express();
const math = require('mathjs');
const LU = require('./lu');
const port = process.env.PORT || 3000;
const { LUdecomposition } = require('./build/Release/result');

app.use(cors());
app.use(express.json());
app.post("/calculate", (req, res) => {

    const { array } = req.body;
    // console.log(array);

    var t1 = performance.now();
    const cppResult = LUdecomposition(array);
    const cppTime = performance.now() - t1;

    t1 = performance.now();
    const jsResult = LU(array);
    const jsTime = performance.now() - t1;

    res.send({ code: 200, results: { js: { time: jsTime, result: jsResult }, cpp: { time: cppTime, result: cppResult } } });

});

app.listen(port, (req, res) => {
    console.log(`server has started at ${port} port`)
});
