randomstring.c
Chris Brackett
bracketc@oregonstate.edu
CS362 - Random Testing Quiz 2
1/30/2017

In order to have the error message in the testme() function show up, a few things need to happen. First, the state integer must be increased from 0 to 9. Each increase in state is tied to a specific character being stored in c. For example, only the character '[' will change state from 0 to 1 and only the character '(' will change state from 1 to 2. This happens with varying characters until state equals 9.

Once state is at 9, the string (s) is checked. If the string is "reset" (followed by its terminating null), then the error message is printed and the program exits. If the string is anything else besides "reset", then the loop in testme() starts over. This will cause a new random string to be generated and compared to "reset" again. At this point, the value of c does not matter since state is already at 9.

The value for c is generated by the function inputChar(). As we can see in the testme() function, c cannot simply be a-z; it must also be able to be space, brackets, parentheses, or braces. To do this, the inputChar() function simply generates a single random number in the range 32-126. When this number is assigned to a variable of type char, the char takes on the corresponding ASCII value. The number 32 represents a space, and 126 representing a tilde (~). Between these values are various symbols, the numbers 0-9, lowercase letters a-z, and uppercase letters A-Z. This means that the character returned from inputChar() can be any of these. The characters required to change the state variable from 0 to 9 are included in this range, therefore the inputChar() function can successfully change state to 9 in testme().

The value for s is generated by the function inputString(). As we can see in the testme() function, we are only comparing the string s to the string "reset". Because of this, I chose to have the inputString() function return only strings of length 5 (6 if you count the terminating null). Using similar logic, I restricted the characters that can be in the string to lowercase letters a-z using the same method as in inputChar(). In order for the program to have access to the generated string after the inputString() function returns, I made the string static. Now, testme() has access to the returned string which is 5 random lowercase letters plus the terminating null.

The odds of the random string being the string "reset" are (1/26)^5. These are pretty low odds, however, computers can run iterations very quickly. For example, I ran the program and it took 5.5 million iterations to reach the error message while another time it took 12.5 million iterations. The string generated from inputString() could theoretically be of any length and made up of the full range of characters. However, this would dramatically reduce the odds of activating the error message and would almost certainly lead to an extremely large number of iterations each time the program was run (unless you get very, very lucky).