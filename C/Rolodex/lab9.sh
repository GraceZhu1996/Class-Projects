#!/bin/bash

#USAGE
#	sh lab9.sh [0 for student 1 for grader/TA] [path to c file] [location of testcase root] [runtime directory] [detailed_results directory] [if grader mode, absolute path to .csv for grading]
#
# ex. sh lab9.sh 0 ./rolodex.c ./testcases . ./results
# ex. sh lab9.sh 1 ./cpmcgrat_rolodex.c ./testcases . ./results ./final_results.csv
#	Note: the desing is set up to return a csv file listing the UCNetID of each student followed by the number
#	      of tests they passed/failed (if compile failed, large note saying "COMPILE FAILURE")

#Colors
BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
LIME_YELLOW=$(tput setaf 190)
POWDER_BLUE=$(tput setaf 153)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
BLINK=$(tput blink)
REVERSE=$(tput smso)
UNDERLINE=$(tput smul)

now="$(date)"

printf "\n\n=================================================================================\n"
printf "||             ${YELLOW}ICS51-LAB9-TEST      $now${NORMAL}               ||\n"
printf "=================================================================================\n\n"

#Passed in info
MODE=${1}
C_FILE=${2}
TEST_DIR=${3}
RUN_DIR=${4}
RESULTS_DIR=${5}
CSV_LOC=${6}
UCNETID=

if [ $MODE -eq 1 ]; then
	UCNETID=($(echo $C_FILE | tr "_" "\n")[0])
fi

echo "Switch =$SWITCH"
echo "C file = $C_FILE"
echo "Test directory = $TEST_DIR"
echo "Runtime directory = $RUN_DIR"
echo "Results directory = $RESULTS_DIR"

#Success/fail bools
TEST1=0
TEST2=0
TEST3=0
TEST4=0
TEST5=0
TEST6=0

#Check test directory exists
if [ ! -d "$TEST_DIR" ]; then
    printf "\nERROR, testcases missing!\nPlease move the testcases directory into your current working directory\n"
    exit 1
fi

if [ ! -f "$C_FILE" ]; then
    printf "\nERROR, file $C_FILE does not exist\n"
fi

if [ ! -d "$RUN_DIR" ]; then
    printf "\nERROR, Runtime directory $RUN_DIR does not exist\n"
fi

if [ ! -d "$RESULTS_DIR" ]; then
   printf "\nERROR, Results directory $RESULTS_DIR does not exist\n"
fi

#Attempt to compile and write out failure if failed
printf "${CYAN}\nCompiling...\n\n${NORMAL}"
if gcc -std=c99 $C_FILE -o $RUN_DIR/rolodex; then
	printf "${GREEN}\nSUCCESS\n${NORMAL}"
	printf "\nContinuing with tests...\n"
else
	printf "${RED}\nFAIL\n${NORMAL}"
	printf "\nExiting...\n"
	if [ $MODE -eq 1 ]; then
		printf "$UCNETID, COMPILE FAIL\n" >> $CSV_LOC
	fi
	exit 1
fi

#Remove diff files
rm $RESULTS_DIR/test1/diff1
rm $RESULTS_DIR/test2/diff2
rm $RESULTS_DIR/test3/diff3
rm $RESULTS_DIR/test4/diff4
rm $RESULTS_DIR/test5/diff5
rm $RESULTS_DIR/test6/diff6

#Remove result files from previous test
rm $RESULTS_DIR/test1/results1
rm $RESULTS_DIR/test2/results2
rm $RESULTS_DIR/test3/results3
rm $RESULTS_DIR/test4/results4
rm $RESULTS_DIR/test5/results5
rm $RESULTS_DIR/test6/results6

#Reset contactList(s) to the initial values needed
cp $TEST_DIR/test1/contactList1.in $TEST_DIR/test1/contactList1
rm $TEST_DIR/test2/myRolodex 
cp $TEST_DIR/test3/contactList3.in $TEST_DIR/test3/contactList3
cp $TEST_DIR/test4/contactList4.in $TEST_DIR/test4/contactList4
cp $TEST_DIR/test5/contactList5.in $TEST_DIR/test5/contactList5
cp $TEST_DIR/test6/contactList6.in $TEST_DIR/test6/contactList6

wait

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-1${NORMAL}            ||\n"
printf "|| * Invalid command ignore     ||\n"
printf "|| * Sorting                    ||\n"
printf "==================================\n"
$RUN_DIR/rolodex $TEST_DIR/test1/contactList1 < $TEST_DIR/test1/in1
diff $TEST_DIR/test1/contactList1 $TEST_DIR/test1/contactList1.out > $RESULTS_DIR/test1/diff1

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-2${NORMAL}            ||\n"
printf "|| * Default filename usage     ||\n"
printf "|| * Non-existant card removal  ||\n"
printf "|| * Non-existant card lookup   ||\n"
printf "|| * Lower case commands        ||\n"
printf "==================================\n"
rm -r -f myRolodex
$RUN_DIR/rolodex < $TEST_DIR/test2/in2-1
./rolodex < $TEST_DIR/test2/in2-2
mv myRolodex $TEST_DIR/test2
diff $TEST_DIR/test2/myRolodex $TEST_DIR/test2/myRolodex2.out > $RESULTS_DIR/test2/diff2

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-3${NORMAL}            ||\n"
printf "|| * Remove multiple cards      ||\n"
printf "||   sharing last name          ||\n"
printf "==================================\n"
$RUN_DIR/rolodex $TEST_DIR/test3/contactList3 < $TEST_DIR/test3/in3
diff $TEST_DIR/test3/contactList3 $TEST_DIR/test3/contactList3.out > $RESULTS_DIR/test3/diff3

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-4${NORMAL}            ||\n"
printf "|| * Case sensitive sorting     ||\n"
printf "==================================\n"
$RUN_DIR/rolodex $TEST_DIR/test4/contactList4 < $TEST_DIR/test4/in4
diff $TEST_DIR/test4/contactList4 $TEST_DIR/test4/contactList4.out > $RESULTS_DIR/test4/diff4

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-5${NORMAL}            ||\n"
printf "|| * Add cards to rolodex       ||\n"
printf "==================================\n"
$RUN_DIR/rolodex $TEST_DIR/test5/contactList5 < $TEST_DIR/test5/in5
diff $TEST_DIR/test5/contactList5 $TEST_DIR/test5/contactList5.out > $RESULTS_DIR/test5/diff5

printf "\n\n==================================\n"
printf "||            ${CYAN}TEST-6${NORMAL}            ||\n"
printf "|| * Find all cards with same   ||\n"
printf "||   lastname                   ||\n"
printf "==================================\n"
$RUN_DIR/rolodex $TEST_DIR/test6/contactList6 < $TEST_DIR/test6/in6
diff $TEST_DIR/test6/contactList6 $TEST_DIR/test6/contactList6.out > $RESULTS_DIR/test6/diff6

wait

#Check if pass/fail for testcases and log to bools
if [ ! -s "$RESULTS_DIR/test1/diff1" ]; then
	(( TEST1++ ))
fi

if [ ! -s "$RESULTS_DIR/test2/diff2" ]; then
	(( TEST2++ ))
fi

if [ ! -s "$RESULTS_DIR/test3/diff3" ]; then
	(( TEST3++ ))
fi

if [ ! -s "$RESULTS_DIR/test4/diff4" ]; then
	(( TEST4++ ))
fi

if [ ! -s "$RESULTS_DIR/test5/diff5" ]; then
	(( TEST5++ ))
fi

if [ ! -s "$RESULTS_DIR/test6/diff6" ]; then
	(( TEST6++ ))
fi

wait

printf "\n\n==================================\n"
printf "||           ${CYAN}RESULTS${NORMAL}            ||\n"
printf "==================================\n"

printf "\ntest1: "
stat --printf="Your Output Size: %s" $TEST_DIR/test1/contactList1 >> ${RESULTS_DIR}/test1/results1
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test1/contactList1.out >> ${RESULTS_DIR}/test1/results1
cat ${RESULTS_DIR}/test1/diff1 >> ${RESULTS_DIR}/test1/results1
if [ $TEST1 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test1/results1\n"

printf "\ntest2: "
stat --printf="Your Output Size: %s" $TEST_DIR/test2/myRolodex >> ${RESULTS_DIR}/test2/results2
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test2/myRolodex2.out >> ${RESULTS_DIR}/test2/results2
cat $RESULTS_DIR/test2/diff2 >> $RESULTS_DIR/test2/results2
if [ $TEST2 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test2/results2\n"

printf "\ntest3: "
stat --printf="Your Output Size: %s" $TEST_DIR/test3/contactList3 >> $RESULTS_DIR/test3/results3
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test3/contactList3.out >> $RESULTS_DIR/test3/results3
cat $RESULTS_DIR/test3/diff3 >> $RESULTS_DIR/test3/results3
if [ $TEST3 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test3/results3\n"

printf "\ntest4: "
stat --printf="Your Output Size: %s" $TEST_DIR/test4/contactList4 >> $RESULTS_DIR/test4/results4
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test4/contactList4.out >> $RESULTS_DIR/test4/results4
cat $RESULTS_DIR/test4/diff4 >> $RESULTS_DIR/test4/results4
if [ $TEST4 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test4/results4\n"

printf "\ntest5: "
stat --printf="Your Output Size: %s" $TEST_DIR/test5/contactList5 >> $RESULTS_DIR/test5/results5
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test5/contactList5.out >> $RESULTS_DIR/test5/results5
cat $RESULTS_DIR/test5/diff5 >> $RESULTS_DIR/test5/results5
if [ $TEST5 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test5/results5\n"

printf "\ntest6: "
stat --printf="Your Output Size: %s" $TEST_DIR/test6/contactList6 >> $RESULTS_DIR/test6/results6
stat --printf="   Correct Output Size: %s\n\nDiff:\n" $TEST_DIR/test6/contactList6.out >> $RESULTS_DIR/test6/results6
cat $RESULTS_DIR/test6/diff6 >> $RESULTS_DIR/test6/results6
if [ $TEST6 -eq 1 ]
then
	printf "${GREEN}PASS${NORMAL}\n"
else
	printf "${RED}FAIL${NORMAL}\n"
fi
printf "For more info:\n"
printf "   vim $RESULTS_DIR/test6/results6\n"

if [ $MODE -eq 1 ]; then
	printf "$UCNETID, $TEST1, $TEST2, $TEST3, $TEST4, $TEST5, $TEST6\n" >> $CSV_LOC
fi

printf "\n\nTESTING COMPLETE\n\n"
