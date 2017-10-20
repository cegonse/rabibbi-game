// Node.JS tool to convert JSON Tiled maps to C headers
var fs = require("fs");

if (process.argv.length != 3) {
	console.log("Usage: tiled2c [in.json]");
	process.exit(1);
}

// File names and data
var inName = process.argv[2];
var inMap = JSON.parse(fs.readFileSync(inName));
var outName = inName.substring(0, inName.indexOf(".json")) + ".h";

// Fetch the map properties
var mapName = inMap.properties.map_name;
var mapTileset = inMap.properties.tileset_name;
var mapPalette = inMap.properties.tileset_palette;

// Create the output C header
var outFile = "// Created with tiled2c.js\n";
outFile += "#ifndef _" + mapName + "_\n";
outFile += "#define _" + mapName + "_\n\n";
outFile += "#include \"room.h\"\n\n";

// Write the data for the plane A layer
var planTiles = null;
var planData = null;

for (var i = 0; i < inMap.layers.length; ++i) {
	if (inMap.layers[i].name == "PlaneA") {
		planData = inMap.layers[i];
		planTiles = planData.data;
		break;
	}
}

if (planData && planTiles) {
	outFile += "#define " + mapName + "_" + planData.name + "_HEIGHT\t" + planData.height + "\n";
	outFile += "#define " + mapName + "_" + planData.name + "_WIDTH\t" + planData.width + "\n\n";

	outFile += "static const u16 " + mapName + "_" + planData.name + "["+ planTiles.length +"] = {\n";
	var k = 0;

	for (var j = 0; j < planTiles.length; j++) {
		if (k == 0) {
			outFile += "\t";
		}

		outFile += planTiles[j].toString() + ", ";
		k++;

		if (k == 16) {
			outFile += "\n";
			k = 0;
		}
	}

	outFile += "};\n\n";
}

// Write the collision data
var collisionEdges = null;

for (var i = 0; i < inMap.layers.length; ++i) {
	if (inMap.layers[i].name == "Collision") {
		collisionEdges = inMap.layers[i].objects;
		break;
	}
}

if (collisionEdges) {
	outFile += "#define " + mapName + "_COLLISION_EDGE_COUNT\t" + collisionEdges.length + "\n\n";
	outFile += "static const s16 " + mapName + "_collision_data[" + collisionEdges.length + "][4] = {\n";

	for (var i = 0; i < collisionEdges.length; ++i) {
		var ed = collisionEdges[i];

		outFile += "\t{ " + Math.floor(ed.x).toString() + ", " + Math.floor(ed.y).toString() + ", " + 
			(Math.floor(ed.x) + Math.floor(ed.polyline[1].x)).toString() + ", " + 
			(Math.floor(ed.y) + Math.floor(ed.polyline[1].y)).toString() + " },\n";
	}

	outFile += "};\n\n";
}

// Write the room struct
outFile += "static const room_t " + mapName + " {\n";
outFile += "\t.tilesetData = &" + mapTileset + ",\n";
outFile += "\t.paletteData = &" + mapPalette + ",\n";

if (planData) {
	outFile += "\t.planeWidth = " + planData.width + ",\n";
	outFile += "\t.planeHeight = " + planData.height + ",\n";
	outFile += "\t.planeData = &" + mapName + "_" + planData.name + ",\n";
}

if (collisionEdges) {
	outFile += "\t.collisionEdges = " + collisionEdges.length + ",\n";
	outFile += "\t.collisionData = &" + mapName + "_collision_data" + "\n";
}

outFile += "};\n\n";

outFile += "#endif // _" + mapName + "_\n";

fs.writeFileSync(outName, outFile);

