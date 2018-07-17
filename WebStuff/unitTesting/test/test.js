var scramble = require("../scramble");
var chai = require("chai");
var expect = chai.expect;

describe("scramble",function() {
	it("scrambles the first and last letters", function() {
		expect(scramble("ask")).to.equal("ksa");
	});
	it("scrambles the 2 letters in the middle", function() {
		expect(scramble("milk")).to.equal("mlik");
	});
});

