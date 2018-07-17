//first try at scramble
function scramble(str) {
	if (isVowel(str.charAt(0)) && !isVowel(str.charAt(str.length-1))) {
		let lastLetter = str.charAt(str.length-1);
		str = str.charAt(str.length-1) + str.substring(1,str.length-1) + str.charAt(0);
	}
    if (!isVowel(str.charAt(0)) && !isVowel(str.charAt(str.length-1))) {
		let lastLetter = str.charAt(str.length-1);
		str = str.charAt(str.length-1) + str.substring(1,str.length-1) + str.charAt(0);
	}
	return str;
}
function isVowel(letter) {
	return (letter === 'a' || letter === 'e'|| letter === 'i' ||
	letter === 'o' || letter === 'u' || letter === 'y')
}

module.exports = scramble;
