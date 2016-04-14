# CS303_Project3

I think 3B will be easier than 3A.

Because we already have the binary search tree code, all we have to do is...

1) While reading from a file... (easy)
2) Tie each letter to an integer value for insertion (medium)
OR
2) Manually branch left or right depending on character (easy)
3) Decode a message using the tree. (easy)
  a) Go to left node at dot (.)
  b) Go to right node at dash (-)
  c) At space ( ), use value of current node.
  d) Repeat until message is decoded.
4) Encode a message using the tree. (hardish)
  a) Create a temp string.
  b) Search the tree recursively for the desired character.
    i) When you go left, append a dot to the temp string.
    ii) When you go right, append a dash to the temp string.
    iii) When you go back up, pop the last character from the temp string.
  c) Once the character is found, append a space. Repeat until message is done.
  
  
ORR We can use a map.

1) While reading from a file... (easy)
2) Use the letter as the key and a string of dots/dashes as the value. (easy)
3) Decode a message using the map. (mediumish)
  a) Parse the message, separting groups of dashes/dots by spaces.
  b) Search the map iteratively (ew) for the value. Write it's key.
  c) Repeat until message is decoded.
4) Encode a message using the map. (easy)
  a) Iterate through the message, using each character as key and then write it's value.
  b) Repeat until message is encoded.
  
  
It seems that binary trees are better for decoding while maps are better for encoding.
