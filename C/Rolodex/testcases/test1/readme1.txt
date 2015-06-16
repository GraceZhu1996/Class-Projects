This testcase verifys:

1) Your program ignores invalid commands
2) The sorting command works (doesn't check case-insensitive implementation) 

"contactList1" is the initial contact list that you should pass as a parameter to your program. 

$ ./rolodex contactList1
Command: X
Invalid command!
Command: S
Command: Q

"contactList1.out" is the correct output that your program should generate after sorting the initial list. Compare your output with the golden (correct) output using:

$ diff contactList1 contactList1.out > diff1

Then see the differences with:

$ cat diff1

or 

$ vim diff1

if "diff1" is empty, your program has passed this testcase successfully. 

