//
// an Assembler for the SSEM "baby" computer
//
// M Billaud, April 2012
// michel.billaud@u-bordeaux1.fr
//
function toHex(word,width) 
{
    var s = "";
    while (width-- > 0) {
	s = "0123456789abcdef"[word & 0xf] + s
	word = word >> 4
    }
    return s;
}

function isSpace(c)
{
    return /\s/.test(c)
}
