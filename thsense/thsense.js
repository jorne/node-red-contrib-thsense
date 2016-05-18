/**
* Copyright 2016 Jorne Roefs
*
**/


module.exports = function(RED) {
  "use strict";

  var fs = require('fs');
  var child_process = require('child_process');

  function ThsenseNode(n) {
    RED.nodes.createNode(this,n);

    var node = this;

    var readth = __dirname + '/../bin/readth.sh';
    fs.access(readth, fs.X_OK, (err) => {
      console.log(err ? 'No execution access to ' + readth : 'ReadTH access OK');
    });

    this.on('input', function (msg) {
      node.log(__dirname);

      child_process.execFile(readth, (err, stdout, stderr) => {
        if (err) {
          node.error(err);
          return null;
        }

        // node.log(stdout);
        msg.payload = JSON.parse(stdout);
        node.send(msg);
      });
    });

    this.on("close", function() {

    });
  }

  RED.nodes.registerType("thsense",ThsenseNode);

}
