echo "--- TESTS EXIT ---"

echo test | exit
exit | echo test
exit 165411651651615132132 | echo test
exit asdas | echo test
exit 1 2 3 | echo test

echo test| exit
echo test| exit 165411651651615132132
echo test | exit asdas
echo test | exit 1 2 3
echo test | exit 1 a 2 3

exit | exit 10 | exit 11 | exit 9223372036854775808
echo $?
exit | exit 10 | exit 11 | exit 9223372036854775807
echo $?
exit | exit 10 | exit 11 | exit 4294967296
echo $?
exit | exit 10 | exit 11 | exit 4294967295
echo $?
exit | exit 10 | exit 11 | exit 268
echo $?