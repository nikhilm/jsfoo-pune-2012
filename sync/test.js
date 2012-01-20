var inv = new (require('./build/Release/sync')).Inventory()

inv.reshelve(function() {
    console.log("Reshelving done");
})
console.log("After reshelve in source");
