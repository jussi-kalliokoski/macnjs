#!/usr/bin/env node

try {
	var beautify = require('beautifyjs').js_beautify;
} catch (e) {
	console.error('It is recommended to install beautifyjs for nicer looking output:');
	console.error('`npm install beautifyjs`');
	beautify = function (s) {
		return s;
	};
}

var fs = require('fs');
var chunks = [];

try {
	process.stdin.resume();

	while ((s = fs.readSync(process.stdin.fd, 1000, -1, 'utf8'))[1]) {
		chunks.push(s[0]);
	}

	process.stdin.pause();
} catch (e) {
	console.error(e);
}

process.stdout.write(beautify(chunks.join('')));
