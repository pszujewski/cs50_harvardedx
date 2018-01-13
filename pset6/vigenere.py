import sys
import cs50

def ensureAlphaNumChars(string):
    length = len(string)
    for i in range(length):
        if not string[i].isalpha():
            return False
    return True

def isInAsciiRange(isUpper, num):
    if isUpper:
        return num >= 65 and num <= 90
    return num >= 97 and num <= 122

def getOffSet(isUpper):
    if isUpper:
        # the first ascii for upper case letters ('A')
        return 65
        # the first ascii for lower case letters ('a')
    return 97

def applyOffset(isUpper, cipheredVal):
    # get the ascii offset based on whether this is a capital letter or not.
    # ascii ranges differ based on whether or not capital.
    offset = getOffSet(isUpper)
    # apply the mod operation below to find how many spots passed the range
    # the ciphered_val is located. There are 26 spots in the both upper case and
    # lower case ranges (total letters). How many more than 26 is the ciphered_val after offset
    # is applied?
    backToBeginning = (cipheredVal - offset) % 26
    # re-apply the offset so the ascii value is back within the correct range
    # depending on whether its upper or lower case.
    return backToBeginning + offset

def convertCipherCharKeyToInt(cipherKeyChar):
    # With the cipher key (alphabetical letter)
    # We only care about its number in the range 1 - 26
    # (position in alphabet) That's the essence of the cipher.
    isCapital = cipherKeyChar.isupper()
    offset = getOffSet(isCapital)
    return ord(cipherKeyChar) - offset

def cipherCharbyKey(originalChar, cipherKeyChar):
    isCapital = originalChar.isupper()
    # cast the char as an ascii int
    originalAscii = ord(originalChar)
    # get the int position of the cipher char in the alphabet (ie a is 1, b is 2...)
    cipherKeyPositionInt = convertCipherCharKeyToInt(cipherKeyChar)
    # apply the cipher key to the integer
    cipheredValInt = originalAscii + cipherKeyPositionInt
    # Need to be sure the ciphered_val has not exceeded
    # the bounds of either upper or lower case ranges
    isInRange = isInAsciiRange(isCapital, cipheredValInt)
    if not isInRange:
        # We need to apply an offset that will wrap
        # the ciphered_val back to the start of the range
        return applyOffset(isCapital, cipheredValInt)
    # otherwise, cipheredVal is still in ascii range and therefore
    # corresponds to a valid char, so just return it as is
    return cipheredValInt

def main():
    if len(sys.argv) != 2 or not ensureAlphaNumChars(sys.argv[1]):
        print("alphabetical command line argument must be provided")
        exit(1)

    print("plaintext: ", end="")
    plaintext = cs50.get_string()

    print("ciphertext: ", end="")

    plainTxtCharIdx = 0
    cipherKey = sys.argv[1];
    cipherKeyLen = len(sys.argv[1])

    for i in range(len(plaintext)):
        j = plainTxtCharIdx % cipherKeyLen
        cipherKeyChar = cipherKey[j]
        cipheredValInt = cipherCharbyKey(plaintext[i], cipherKeyChar)
        # convert the integer to ascii char
        print("{}".format(chr(cipheredValInt)), end="")
        plainTxtCharIdx += 1

    # print a newline and exit with success
    print("")
    exit(0)

if __name__ == "__main__":
    main()
