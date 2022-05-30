// Helper for opencv.js (see below)
var Module = {
    preRun: [function () {
        console.log("Pre Run...")
        //   Module.FS_createPreloadedFile('/', 'haarcascade_frontalface_default.xml', 'haarcascade_frontalface_default.xml', true, false);
    }],
    postRun: [function () {
        console.log("Post Run...")
    }],
    onRuntimeInitialized: function () {
        postMessage({
            msg: 'wasm'
        });

        console.log("Emscripten runtime is ready.");
        if (cv instanceof Promise) {
            cv.then((target) => {
                cv = target;
                console.log(cv.getBuildInformation());
            })
        } else {
            // for backward compatible
            console.log(cv.getBuildInformation());
        }
    },
    printErr: function (text) {
        console.error(text);
    },
    setStatus: function (text) {
        console.log(text);
    },
    totalDependencies: 0
};

function opencvjs_LoadError() {
    Module.printErr('Failed to load/initialize opencv.js');
}

importScripts('opencv.js');