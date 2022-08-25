echo "--- TESTS ECHO ---"

export coucou=salut ;
env | grep coucou
unset coucou
echo

echo 0 : 	
export cou=ec
export bon=ho
$cou$bon salut
echo 'expected : 	salut'
echo

echo 1 : 	
export cou=ec
export bon=ho
"$cou$bon" salut
echo 'expected : 	salut'
echo

echo 1 : 	
export cou=ec
export bon=ho
'$cou$bon' salut
echo 'expected : 	 $cou$bon : command not found'
echo

echo 0 : 	
export cou=ec
export bon=ho
$cou $bon salut
echo 'expected : 	 ec : command not found'
echo

echo 0 : 	
export cou=ec
export bon=ho
"$cou $bon" salut
echo 'expected : 	 ec ho: command not found'
echo

echo 1 : 	
export what="echo coucou"
$what
echo 'expected : 	coucou'
echo

echo
export test="   a   "
echo $test
echo $test$test$test$test$test$test$test$test$test$test$test
echo "$test$test$test$test$test$test$test$test$test"
unset test

echo
export TEST=coucou
export TEST+=bonjour
export | grep TEST
unset TEST
echo

echo
export A=B=C
echo $A
echo

echo
export L="s -la"
l$L
l"$L"
l$L | l$L | l$L
l$L | l$L | l"$L"
echo

echo
export A=p
export B=w
$A$Bd
$A"$B"d
echo

echo
export TEST=LOL | export TEST+=LOL | echo $TEST > 0test.log | env | sort >> 0test.log | export | grep -v SHLVL >> 1test.log | env | grep -v 4 > 3test.log | export | grep TEST >> 4test.log | unset TEST
export TEST="ls       -l     - a" | echo $TEST | $LS |  env | sort | grep -v SHLVL | grep -v _= | grep TEST | unset TEST
export test=hello | export test | env | grep test | grep -v alien | unset test