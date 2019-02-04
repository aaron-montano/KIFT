const path = require('path');
const fs = require('fs');
const { EventEmitter } = require('events');
const { exec, spawn, kill } = require('child_process');
// var cio = require('socket.io')(9001);
// var redis = require('socket.io-redis');
// cio.adapter(redis({ host: '127.0.0.1', port: 9001 }));
// const appio = require('socket.io-emitter')({host: '127.0.0.1', port: 4242 });
let process;


module.exports = function (socket, app, socketid){
    socket.on('enter', () => {
        process = spawn('rec', ['-q', '-c1', '-b16', '-r16k', 'server/command.wav',
        'silence', '1', '0.1', '3%', '1', '1.0', '3%']);
        process.on('close', function(code) {
            console.log('SRV: Rec Return: ' + code);
            pocket(socket, app, socketid);
        });
    });
    socket.on('getData', () => {
        var log = exec(path.join(__dirname, '../log_line -g database/' + socketid));
        log.stdout.on('data', function(data){
            socket.emit('NewLog', data);
        });
    });
    socket.on('disconnect', () => {
        var clean = exec(path.join(__dirname, '../log_line -c database/' + socketid));
        console.log('Socket has disconnected from ' + socketid);
    });
}

function pocket(socket, app, socketid) {
    var psphinx = spawn('./server/pocketsphinx_continuous', ['-argfile', 'server/serv_args']);
    psphinx.stdout.on('data' , function(data) {
        socket.emit('incoming', data);
        console.log('SRV: psphinx: ' + data)
        app.write(data);
        exec(path.join(__dirname, '../log_line -s database/' + socketid + ' "' + data + '"'));
    });
    psphinx.on('close', function(code) {
        console.log('Psphinx return: ' + code);
        socket.emit('ready');
    });
}