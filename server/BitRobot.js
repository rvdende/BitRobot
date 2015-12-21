

// npm install ws
// npm install serialport
// npm install json-scrape
// npm install moment				

// Sources:
// http://momentjs.com
// https://github.com/websockets/ws
// https://blockchain.info/api/api_websocket


var moment = require('moment');
var WebSocket = require('ws');
var ready = 0;

var listenws = function () {
	
	
	console.log(moment().format()+" Connecting to blockchain...")
	var bcsource = 'wss://ws.blockchain.info/inv';
	var ws = new WebSocket(bcsource);

	ws.on('open', function open() {
		console.log(moment().format()+' Blockchain source connected '+bcsource);
	  	ws.send('{"op":"addr_sub", "addr":"17Zu18pDzCneyt5Q7rFC3hjA6ysVoDGX6p"}');
	  	ws.send('{"op":"addr_sub", "addr":"1DNhNdGxZrnjDR6ydxWqm2Qe52NDVuk2QX"}');

	  	//ws.send('{"op":"unconfirmed_sub"}') //all
	  	
	});


	ws.on('message', function(indata, flags) {
		// flags.binary will be set if a binary data is received.
		// flags.masked will be set if the data was masked.
		


		
		var data = JSON.parse(indata);
		
		if (ready == 1) { 
			console.log(data.x);
			for (var i in data.x.out) {
				if (data.x.out[i].addr == "17Zu18pDzCneyt5Q7rFC3hjA6ysVoDGX6p") {
					var apimsg =  { "buy" : "1.0" };
					var apimsgstr = JSON.stringify(apimsg);
					arduino.write(apimsgstr); 
				}

				if (data.x.out[i].addr == "1DNhNdGxZrnjDR6ydxWqm2Qe52NDVuk2QX") {
					var apimsg =  { "buy" : "2.0" };
					var apimsgstr = JSON.stringify(apimsg);
					arduino.write(apimsgstr); 	
				}
			}
		}


	});

	ws.on('close', function close() {
		console.log(moment().format()+' Blockchain connection closed...');
		listenws();
	});
}

listenws();

/* ====================================== */

var SerialPort = require("serialport"); // so we can access the serial port
var scraper = require('json-scrape')(); // cleans messy serial messages.

var arduino;

//LIST DEVICES/AUTODETECT
SerialPort.list( function (err, ports) {
	console.log(moment().format()+" Autodetecting Arduino devices...")
  for (var num in ports) {
    console.log(ports[num]);
    if (ports[num].serialNumber == '754393336353517030D1') {
    	console.log(moment().format()+" Arduino detected on "+ports[num].comName)
    	arduino = new SerialPort.SerialPort(ports[num].comName, {baudrate: 9600}); //you must set the port and baudrate
    	arduConnect(arduino);
    }
  }
});


var arduConnect = function (device) {
	ready = 1;
  	device.on("data", datahandler);
}

var datahandler = function (data) {
  scraper.write(data); 
}

scraper.on('data', function (data) {
  console.log(data)   
  //io.sockets.emit("arduino", data)
});


/*
// TO SEND TO ARDUINO
// ideally this will be called from the browser event with socket io. 
// more in a later class on this.
  var data = { brightness: "0.1" }
  var test = JSON.stringify(data)    // turns into string to send
  console.log(test)
  arduino.write(test)
*/

