# Frank's Caesar Cipher Solver
A small program that cracks caesar-cipher-encrypted messages using custom dictionaries.

# How it Works
The program comes with three dictionary files, *short.dict*, *normal.dict*, and *long.dict*. The user can create
more by calling */p* on a file containing a newline-delineated list of words to add to the dictionary.

The short dictionary is suitable for most applications and contains English's 100 most common words.
The normal dictionary contains English's 1,000 most common words, and is a bit more intensive.
The long dictionary contains 350,000+ words, and is the most comprehensive attack available by default.

The encrypted string is cycled 26 times. For each time, each word in the string is compared against every word
in the dictionary. The cycle with the most matched words should be the decoded string.

# Usage
/p [filename]: Converts a file with a newline-delineated list of words into a dictionary file
/d [dilename]: Selects the dictionary file to use during that session. It is *short.dict* by default
/i [filename]: The encrypted file input to decrypt

# Examples
### Converting a Text File into a Dictionary:
decode /p example.txt

### Decoding an Encrypted File:
decode /i encryptedFile.txt

### Decoding an Encrypted File with a Specific Dictionary:
decode /i encryptedFile.txt /d someDictionary.dict

# Disclaimer
This is, in no way, shape, or form, an elegant way to break these. It works, however, and it does so quickly enough, at ~1.8 seconds to check 62,000,000+ strings (8-word cipher with the long dictionary) on my subpar laptop.

~Enjoy
