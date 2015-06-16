This testcase verifys:

1) Look-up for multiple card works.

"contactList7" is the initial contact list that you should pass as a parameter to your program. 

$ ./rolodex contactList7
Command: i
Enter card: last-name first-name phone
chavez ronak (322)323-4444
Command: s
Command: l
Enter name of card to look up
chavez
0 Chavez Allegra (662)428-9794
1 Chavez Amos (497)547-8064
2 Chavez Avye (484)780-8115
3 Chavez Branden (387)524-9329
4 Chavez Danielle (143)905-6453
5 Chavez Desirae (525)160-1699
6 CHAVEZ Doris (508)299-9556
7 Chavez Elaine (731)912-4689
8 Chavez Hilda (819)895-1659
9 chavez Holly (480)531-2761
10 CHAVEZ Ivor (985)579-3254
11 ChAVEz Jade (992)305-9652
12 Chavez Jerry (788)779-7540
13 Chavez Lacy (896)323-2125
14 chavez Lewis (647)841-9996
15 Chavez Meredith (261)395-8718
16 Chavez Nicole (702)265-5052
17 chaVEZ Raven (276)132-0587
18 Chavez Raya (189)532-6814
19 Chavez Rhona (495)909-4378
20 chavez ronak (322)323-4444
21 Chavez Tiger (991)210-2406
22 Chavez Wanda (695)640-8226
23 Chavez Xenos (610)608-4069
24 Chavez Yuli (212)506-7390
Command: q


"contactList7.out" is the correct output that your program should generate. Compare your output with the golden (correct) output using:

$ diff contactList0 contactList0.out > diff7

Then see the differences with:

$ cat diff7

or 

$ vim diff7

if "diff7" is empty, your program has passed this testcase successfully. 

