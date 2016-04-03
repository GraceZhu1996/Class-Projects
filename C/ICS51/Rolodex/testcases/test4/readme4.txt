This testcase verifys:

1) Your program implements case-insensitive sorting

"contactList4" is the initial contact list that you should pass as a parameter to your program. 

$ ./rolodex contactList4
Command: s
Command: q

"contactList4.out" is the correct output that your program should generate. Compare your output with the golden (correct) output using:

$ diff contactList4 contactList4.out > diff4

Then see the differences with:

$ cat diff4

or 

$ vim diff4

if "diff4" is empty, your program has passed this testcase successfully. 

