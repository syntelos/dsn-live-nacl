/*
 * Browser feature test for native client.
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
