module.exports = function LU(arr) {
    const n = arr.length;
    let l = [];
    let u = [];
    for (let i = 0; i < n; i++) {
        l.push([]);
        u.push([]);
    }
    let i = 0, j = 0, k = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j < i)
                l[j][i] = 0;
            else {
                l[j][i] = arr[j][i];
                for (k = 0; k < i; k++) {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (j = 0; j < n; j++) {
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else {
                u[i][j] = arr[i][j] / l[i][i];
                for (k = 0; k < i; k++) {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            }
        }
    }
    return { lower: l, upper: u };
}
