/*
 * DSN Live HTML application layer
 *
 * Requires 'spin.js', 'nacl.js'.
 */
var dsnlRunning = false;
var dsnlSpinner = null;

function dsnlMessage(nacl_msg){

    dsnlShow();
    try {
        var js_data = JSON.parse(nacl_msg.data);

        if (js_data.log){

            if (js_data.message){
                console.log(js_data.message);
            }
            else {
                alert("HTML: dsnlMessage(): 'log' missing 'message'.");
            }
        }
        else if (js_data.alert){

            if (js_data.message){
                alert(js_data.message);
            }
            else {
                alert("HTML: dsnlMessage(): 'alert' missing 'message'.");
            }
        }
        else if (js_data.body){

            if (js_data.content){
                document.body.innerHTML = js_data.content;
            }
            else {
                alert("HTML: dsnlMessage(): 'body' missing 'content'.");
            }
        }
        else {
            console.log(nacl_msg.data);
        }
    }
    catch (x){
        console.log(nacl_msg.data);
    }
}
function dsnlTest(){

    if (dsnlRunning){
        console.log("HTML dsnlTest(): OK");
    }
    else {
        console.log("HTML dsnlTest(): NG");

        dsnlUnavailable();
    }
}
function dsnlUnavailable(){
    try {
        var el = document.getElementById("nacl");
        el.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlUnavailable(): Failed nacl hide.");
    }
    try {
        var el = document.getElementById("loading");
        el.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlUnavailable(): Failed loading hide.");
    }
    try {
        if (dsnlSpinner){

            dsnlSpinner.stop();
        }
    }
    catch (x){
        console.log("HTML: dsnlUnavailable(): Failed dsnlSpinner stop.");
    }
    try {
        var el = document.getElementById("unavailable");
        el.style.display = "block";
    }
    catch (x){
        console.log("HTML: dsnlUnavailable(): Failed failure show.");
    }
}
function dsnlUnsupported(){
    try {
        var el = document.getElementById("nacl");
        el.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlUnsupported(): Failed nacl hide.");
    }
    try {
        var el = document.getElementById("loading");
        el.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlUnsupported(): Failed loading hide.");
    }
    try {
        if (dsnlSpinner){

            dsnlSpinner.stop();
        }
    }
    catch (x){
        console.log("HTML: dsnlUnsupported(): Failed dsnlSpinner stop.");
    }
    try {
        var el = document.getElementById("unsupported");
        el.style.display = "block";
    }
    catch (x){
        console.log("HTML: dsnlUnsupported(): Failed failure show.");
    }
}
function dsnlShow(){
    if (!dsnlRunning){
        dsnlRunning = true;
        try {
            if (dsnlSpinner){

                dsnlSpinner.stop();
            }
        }
        catch (x){
            console.log("HTML: dsnlShow(): Failed dsnlSpinner stop.");
        }
        try {
            var el = document.getElementById("loading");
            el.style.display = "none";
        }
        catch (x){
            console.log("HTML: dsnlShow(): Failed loading hide.");
        }
    }
}
function dsnlInit(){
    /*
     * Requires 'nacl.js'
     */
    if (!nacl.supported){

        dsnlUnsupported();
    }
    else if (!dsnlRunning){

        var spinner_conf = {
            lines: 12,
            length: 0,
            width: 25,
            radius: 60,
            corners: 1,
            rotate: 0,
            direction: 1,
            color: '#efefef',
            speed: 1,
            trail: 60,
            shadow: false,
            hwaccel: false,
            className: 'spinner',
            zIndex: 2e9,
            top: '50%',
            left: '50%'
        };
        dsnlSpinner = new Spinner(spinner_conf).spin();

        var el_loading = document.getElementById("loading");
        if (el_loading){

            el_loading.appendChild(dsnlSpinner.el);
        }
        else {
            console.log("HTML: Failed to append 'dsnlSpinner' to 'loading'.");
        }

        setTimeout(dsnlTest,60000);
    }
}
function dsnlLoad(evt){
    console.log("HTML: dsnlLoad(): "+evt);
}
function dsnlCrash(evt){
    console.log("HTML: dsnlCrash(): "+evt);
    dsnlUnavailable();
}
function dsnlError(evt){
    console.log("HTML: dsnlError(): "+evt);
}
