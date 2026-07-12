/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = function(functions) {

    return new Promise((resolve, reject) => {

        const results = new Array(functions.length);

        let completed = 0;

        functions.forEach((fn, index) => {

            fn()
                .then((value) => {

                    // Store result at original index
                    results[index] = value;

                    completed++;

                    // All promises completed successfully
                    if (completed === functions.length) {
                        resolve(results);
                    }
                })
                .catch((error) => {

                    // Immediately reject if any promise fails
                    reject(error);
                });
        });
    });
};

/**
 * const promise = promiseAll([
 *     () => new Promise(res => res(42))
 * ]);
 *
 * promise.then(console.log); // [42]
 */
