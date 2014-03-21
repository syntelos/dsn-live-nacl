/*
 * 
 */
var dsnlReady = false;
var spinner = null;
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
  top: '49%',
  left: '49%'
};

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

    if (dsnlReady){
        console.log("HTML dsnlTest(): OK");
    }
    else {
        console.log("HTML dsnlTest(): NG");

        dsnlHide();
    }
}
function dsnlHide(){
    try {
        var el_nacl = document.getElementById("nacl");
        el_nacl.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlHide(): Failed nacl hide.");
    }
    try {
        var el = document.getElementById("loading");
        el.style.display = "none";
    }
    catch (x){
        console.log("HTML: dsnlHide(): Failed loading hide.");
    }
    try {
        spinner.stop();
    }
    catch (x){
        console.log("HTML: dsnlHide(): Failed spinner stop.");
    }
    try {
        var el_fail = document.getElementById("failure");
        el_fail.style.display = "block";
    }
    catch (x){
        console.log("HTML: dsnlHide(): Failed failure show.");
    }
}
function dsnlShow(){
    if (!dsnlReady){
        dsnlReady = true;
        try {
            spinner.stop();
        }
        catch (x){
            console.log("HTML: dsnlShow(): Failed spinner stop.");
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
    if (!dsnlReady){
        spinner = new Spinner(spinner_conf).spin();
        var el_loading = document.getElementById("loading");
        if (el_loading){

            el_loading.appendChild(spinner.el);
        }
        else {
            console.log("HTML: Failed to append 'spinner' to 'loading'.");
        }
    }
}
