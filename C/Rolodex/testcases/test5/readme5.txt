This testcase verifys:

1) Your program adds multiple cards to an empty list.

"contactList5" is the initial "empty" contact list that you should pass as a parameter to your program. 

$ ./rolodex contactList5
Command: i
Enter card: last-name first-name phone
cartman eric (312)324-7463
Command: i
Enter card: last-name first-name phone
broflovski kyle (922)121-4232
Command: i
Enter card: last-name first-name phone
marsh stan (922)134-1297
Command: i
Enter card: last-name first-name phone
mccormick kenny (273)121-4732
Command: i
Enter card: last-name first-name phone
stotch butters (924)124-3732
Command: i
Enter card: last-name first-name phone
valmer jimmy (764)248-7633
Command: i
Enter card: last-name first-name phone
black token (333)174-2223
Command: p
0 cartman eric (312)324-7463
1 broflovski kyle (922)121-4232
2 marsh stan (922)134-1297
3 mccormick kenny (273)121-4732
4 stotch butters (924)124-3732
5 valmer jimmy (764)248-7633
6 black token (333)174-2223
Command: s
Command: p
0 black token (333)174-2223
1 broflovski kyle (922)121-4232
2 cartman eric (312)324-7463
3 marsh stan (922)134-1297
4 mccormick kenny (273)121-4732
5 stotch butters (924)124-3732
6 valmer jimmy (764)248-7633
Command: q

"contactList5.out" is the correct output that your program should generate. Compare your output with the golden (correct) output using:

$ diff contactList5 contactList5.out > diff5

Then see the differences with:

$ cat diff5

or 

$ vim diff5

if "diff5" is empty, your program has passed this testcase successfully. 

