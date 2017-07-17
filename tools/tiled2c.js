// Node.JS tool to convert JSON Tiled maps to C headers
var fs = require("fs");

if (process.argv.length != 4) {
	console.log("Usage: tiled2c [in.json] [out]");
	process.exit(1);
}

var inMap = JSON.parse(fs.readFileSync(process.argv[2]));
var outName = process.argv[3];

var outFile = "// Created with tiled2c.js\n";
outFile += "// Cesar Gonzalez, 2017\n\n";
outFile += "#ifndef _" + outName + "_\n";
outFile += "#define _" + outName + "_\n\n";

// Write the data for all the layers
for (var i = 0; i < inMap.layers.length; ++i) {
	var layerData = inMap.layers[i].data;

	outFile += "#define " + outName + "_" + inMap.layers[i].name + "_HEIGHT\t" + inMap.layers[i].height + "\n";
	outFile += "#define " + outName + "_" + inMap.layers[i].name + "_WIDTH\t" + inMap.layers[i].width + "\n";

	outFile += "static const u16 " + outName + "_" + inMap.layers[i].name + "["+ layerData.length +"] = {\n";
	var k = 0;

	for (var j = 0; j < layerData.length; j++) {
		if (k == 0) {
			outFile += "\t";
		}

		outFile += layerData[j].toString() + ", ";
		k++;

		if (k == 16) {
			outFile += "\n";
			k = 0;
		}
	}

	outFile += "};\n\n";
}

outFile += "#endif // _" + outName + "_\n";

fs.writeFileSync(outName + ".h", outFile);
