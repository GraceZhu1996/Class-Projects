This testcase verifys:

1) Default file name is used if no argument is passed to rolodex.
2) Removing a card that doesn't exist.
3) Looking up a card that doesn't exist.
4) Lower-case letters for commands are accepted.

Run your program:

$ rm myRolodex
$ ./rolodex
Command: P
Command: d
Enter name of card to remove
Klefstad
No contact to remove
Command: L
Enter name of card to look up
Klefstad
No contact found
Command: I
Enter card: last-name first-name phone
Klefstad Ray (949)111-0000
Command: L
Enter name of card to look up
Dang
No contact found
Command: q
$ ./rolodex
Command: I
Enter card: last-name first-name phone
Obama Barack (929)121-4343
Command: I
Enter card: last-name first-name phone
Zimmer Hans (769)121-4523
Command: S
Command: Q

"myRolodex2.out" is the correct output that your program should generate at the end. Compare your output with the golden (correct) output using:

$ diff myRolodex myRolodex2.out > diff2

Then see the differences with:

$ cat diff2

or 

$ vim diff2

if "diff2" is empty, your program has passed this testcase successfully. 

