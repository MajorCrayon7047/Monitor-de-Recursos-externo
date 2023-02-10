const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline')
const cpu = require('windows-cpu');
const si = require('systeminformation');

const port = new SerialPort({ path: 'COM3', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }))


async function serialParser(){
    let load = await cpu.totalLoad();
    load[0] = String(load[0]);
    while (load[0].length <= 2) load[0] = '0' + load[0]
    console.log("cpu:", load[0]);
    let CPU = load[0]

    let mem = await cpu.totalMemoryUsage();
    let mem2 = mem.usageInGb;
    mem2 = String(mem2.toFixed(1));
    while (mem2.length <= 3) mem2 = mem2 + '0'
    console.log("meme in Gb: ", mem2);
    mem = (mem.usageInGb / 11.8)*100;
    mem = String(mem.toFixed())
    while (mem.length <= 2) mem = '0' + mem
    console.log("mem:", mem);

    let temp = await si.cpuTemperature();
    temp = temp.main;
    temp = String(temp.toFixed());
    while (temp.length <= 2)temp = '0' + temp

    let a = `${CPU + mem + mem2 + temp}\n`
    console.log(a)
    port.write(a)
}

// Read the port data
port.on("open", () => {
    console.log('serial port open');
});

parser.on('data', data =>{
    console.log('Atte Arduino:', data);
});

setInterval(function() {
    serialParser()
  }, 3000);
