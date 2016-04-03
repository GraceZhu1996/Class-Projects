This testcase verifys:

1) Your program removes multiple cards with the same last name, ignoring letter case

"contactList3" is the initial contact list that you should pass as a parameter to your program. 

$ ./rolodex contactList3
Command: d
Enter name of card to remove
Holloway
Command: l
Enter name of card to look up
HOLLOWAY
No contact to show
Command: S
Command: Q

"contactList3.out" is the correct output that your program should generate. Compare your output with the golden (correct) output using:

$ diff contactList3 contactList3.out > diff3

Then see the differences with:

$ cat diff3

or 

$ vim diff3

if "diff3" is empty, your program has passed this testcase successfully. 

