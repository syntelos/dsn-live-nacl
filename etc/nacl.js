/*
 * Browser feature test for native client
 * Copyright 2014 John Pritchard, Syntelos.
 * 
 * This work is licensed under a Creative Commons Attribution 3.0
 * Unported License (CC-BY).
 * http://creativecommons.org/licenses/by/3.0/
 */
var nacl = {
    supported: false,
    mimetypes: [
        'application/x-nacl',
        'application/x-ppapi-release',
        'application/x-ppapi-debug'
    ]
};
try {
    var cc;
    for (cc = 0; cc < nacl.mimetypes.length; cc++){
        var mimetype = nacl.mimetypes[cc];

        if (undefined !== navigator.mimeTypes[mimetype]){

            console.log("HTML: nacl.js found " + mimetype);

            nacl.supported = true;
        }
    }
}
catch (x){
    console.log("HTML: nacl.js error: " + x);
}
