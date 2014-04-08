var request = require("request");

// HTTP GET Request
request("http://nodestreams.com/input/people.csv").pipe(process.stdout)
