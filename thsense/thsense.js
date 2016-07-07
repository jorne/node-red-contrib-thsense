/**
* Copyright 2016 Jorne Roefs
*
**/


module.exports = function(RED) {
  'use strict';

  var fs = require('fs');
  var child_process = require('child_process');

  function ThsenseNode(n) {
    RED.nodes.createNode(this,n);

    var node = this;
    this.pin_number = n.pin;

    var readth = __dirname + '/../bin/readth.sh';
    fs.access(readth, fs.X_OK, (err) => {
      console.log(err ? 'No execution access to ' + readth : 'ReadTH access OK');
    });

    this.on('input', function (msg) {
      node.log('Executing ' + readth + ' ' + node.pin_number);
      child_process.execFile(readth, [node.pin_number], (err, stdout, stderr) => {
        if (err) {
          node.error(err);
          return null;
        }

        try {
          msg.payload = JSON.parse(stdout);
          node.send(msg);
        }
        catch (e) {
          node.error('Invalid reading from sensor', e);
          node.log('TH Sensor debug: ' + stderr);
        }
        finally {
          node.log('TH Sensor data: ' + stdout);
        }
        // node.log(stdout);
        //msg.payload = JSON.parse(stdout);
      });
    });

    this.on('close', function() {

    });
  }

  RED.nodes.registerType('thsense',ThsenseNode);

}
