var inv = new (require('./build/Release/async')).Inventory()

inv.reshelve(function() {
    console.log("Reshelving done");
})
console.log("After reshelve in source");
for (var i = 1; i < 5; i++)
    setTimeout(function() {
        console.log("Tick");
    }, i*1000);
