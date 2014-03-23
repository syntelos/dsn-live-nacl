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

        var m_data = nacl_msg.data;

        if (m_data.log && m_data.message){

            console.log(m_data.message);
        }
        else if (m_data.alert && m_data.message){

            alert(m_data.message);
        }
        else if (m_data.body && m_data.content){

            document.body.innerHTML = m_data.content;
        }
        else if (m_data.failure && m_data.content){

            dsnl.unavailable();

            try {
                var el_p3 = document.getElementById("unp3");

                el_p3.innerHTML = m_data.content;
            }
            catch (x){
                alert("HTML: dsnl.message(): error processing 'failure' / 'content': " + x);
            }
        }
        else {
            console.log(m_data);
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
