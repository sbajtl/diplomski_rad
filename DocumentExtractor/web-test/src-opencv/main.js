let wasmWorker = new Worker('wasm-worker.js');

wasmWorker.onmessage = function (e) {
    if (e.data.msg == 'wasm') {
        console.log(e.data.msg)
    }
}