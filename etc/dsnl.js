/*
 * DSN Live HTML application layer
 * Copyright 2014 John Pritchard, Syntelos.
 * 
 * This work is licensed under a Creative Commons Attribution 3.0
 * Unported License (CC-BY).
 * http://creativecommons.org/licenses/by/3.0/
 *
 * Requires 'spin.js', 'nacl.js'.
 */
var dsnl = {
    running: false,
    spinner_conf: {
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
    },
    init: function(){
        /*
         * Requires 'nacl.js'
         */
        if (!nacl.supported){

            this.unsupported();
        }
        else if (!this.running){

            this.spinner = (new Spinner(this.spinner_conf).spin());

            var el_loading = document.getElementById("loading");
            if (el_loading){

                el_loading.appendChild(this.spinner.el);
            }
            else {
                console.log("HTML: Failed to append 'dsnl.spinner' to 'loading'.");
            }

            setTimeout(this.validate,60000);
        }
    },
    unavailable: function(){
        this.running = false;
        try {
            var el = document.getElementById("nacl");
            el.style.display = "none";
        }
        catch (x){
            console.log("HTML: dsnl.unavailable(): Failed 'nacl' hide.");
        }
        try {
            var el = document.getElementById("loading");
            el.style.display = "none";
        }
        catch (x){
            console.log("HTML: dsnl.unavailable(): Failed loading hide.");
        }
        try {
            if (this.spinner){

                this.spinner.stop();
            }
        }
        catch (x){
            console.log("HTML: dsnl.unavailable(): Failed dsnl.Spinner stop.");
        }
        try {
            var el = document.getElementById("unavailable");
            el.style.display = "block";
        }
        catch (x){
            console.log("HTML: dsnl.unavailable(): Failed failure show.");
        }
    },
    unsupported: function(){
        this.running = false;
        try {
            var el = document.getElementById("nacl");
            el.style.display = "none";
        }
        catch (x){
            console.log("HTML: dsnl.unsupported(): Failed nacl hide.");
        }
        try {
            var el = document.getElementById("loading");
            el.style.display = "none";
        }
        catch (x){
            console.log("HTML: dsnl.unsupported(): Failed loading hide.");
        }
        try {
            if (this.spinner){

                this.spinner.stop();
            }
        }
        catch (x){
            console.log("HTML: dsnl.unsupported(): Failed dsnl.Spinner stop.");
        }
        try {
            var el = document.getElementById("unsupported");
            el.style.display = "block";
        }
        catch (x){
            console.log("HTML: dsnl.unsupported(): Failed failure show.");
        }
    },
    show: function(){
        if (!this.running){
            this.running = true;
            try {
                if (this.spinner){

                    this.spinner.stop();
                }
            }
            catch (x){
                console.log("HTML: dsnl.show(): Failed dsnl.Spinner stop.");
            }
            try {
                var el = document.getElementById("loading");
                el.style.display = "none";
            }
            catch (x){
                console.log("HTML: dsnl.show(): Failed loading hide.");
            }
        }
    },
    /*
     * Event handlers will not see reference 'this' as 'dsnl' when
     * called.
     */
    validate: function(){

        if (dsnl.running){
            console.log("HTML dsnl.validate(): OK");
        }
        else {
            console.log("HTML dsnl.validate(): NG");

            dsnl.unavailable();
        }
    },
    load: function(evt){
        console.log("HTML: dsnl.load(): "+evt);

        dsnl.show();
    },
    message: function(nacl_msg){

        dsnl.show();
        try {
            var js_data = JSON.parse(nacl_msg.data);

            if (js_data.log){

                if (js_data.message){
                    console.log(js_data.message);
                }
                else {
                    alert("HTML: dsnl.message(): 'log' missing 'message'.");
                }
            }
            else if (js_data.alert){

                if (js_data.message){
                    alert(js_data.message);
                }
                else {
                    alert("HTML: dsnl.message(): 'alert' missing 'message'.");
                }
            }
            else if (js_data.body){

                if (js_data.content){
                    document.body.innerHTML = js_data.content;
                }
                else {
                    alert("HTML: dsnl.message(): 'body' missing 'content'.");
                }
            }
            else if (js_data.failure){

                if (js_data.content){

                    dsnl.unavailable();

                    try {
                        var el_p3 = document.getElementById("unp3");

                        el_p3.innerHTML = js_data.content;
                    }
                    catch (x){
                        alert("HTML: dsnl.message(): error processing 'failure' / 'content': " + x);
                    }
                }
                else {
                    alert("HTML: dsnl.message(): 'failure' missing 'content'.");
                }
            }
            else {
                console.log(nacl_msg.data);
            }
        }
        catch (x){
            console.log(nacl_msg.data);
        }
    },
    crash: function(evt){
        console.log("HTML: dsnl.Crash(): "+evt);

        dsnl.unavailable();
    },
    error: function(evt){
        console.log("HTML: dsnl.Error(): "+evt);
    }
};
