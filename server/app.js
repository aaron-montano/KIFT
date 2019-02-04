const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const { exec } = require('child_process');
const http = require('http').Server(app);
const io = require('socket.io')(http);
const path = require('path');
const port = 3000;
const net = require('net');
//sockets and routes set up
//data base
//static files

net.createServer( function (app) {
    console.log('TCP: New TCP Connection:');
    app.on('connection', function () {
        app.write('TCP: Welcome new connection!');
    })
    app.on('data', function (data) {
        console.log('TCP: data: ' + app.remoteAddress + ':' + app.remotePort + '\n' + data);
        app.write('TCP: Received message, thank you');
    })    
    app.on('close', function (data) {
        console.log('TCP: Closed: ' + app.remoteAddress + ':' + app.remotePort);
        app.destroy();
    })
    app.on('error', (err) => {
        if (err.code === 'EADDRINUSE') {
            console.log('TCP: Address in use, retrying...');
          setTimeout(() => {
              app.close();
              app.listen(PORT, HOST);
          }, 1000);
        }
    });
    io.on('connection', (socket) => {
        let process;
        require('./controllers/db.js')(socket, app, `${socket.id}`);
        console.log(`SRV: user connected ! socket-id : ${socket.id}`);
        socket.emit('SRV->ALL: socketMessage', 'The server hears you, friend :)');
        //appio.emit('socketMessage', 0x42424242)
    });
}).listen(4242, '127.0.0.1', 3);


http.listen(port, function(){
    console.log(`SRV: kift is listening on ${port}`);
    console.log('Please continue to Frontend startup');
});