echo "--- TEST REDIR RIGHT ---"

echo
echo 0
echo
echo coucou > test.log
ls
cat test.log
rm test.log

echo
echo 2
echo
echo coucou > 0test.log > 1test.log
ls
cat 0test.log
cat 1test.log
rm 0test.log 1test.log

echo
echo 3
echo
ls > test.log
ls
cat test.log
rm test.log

echo
echo 6
echo
ls > 2test.log > 3test.log
ls
cat 2test.log
cat 3test.log
rm 2test.log 3test.log

export | grep SHELL > 0test.log
cat 0test.log
rm 0test.log

env | SHELL > 0test.log
cat 0test.log
rm 0test.log

pwd > 0test.log
cat 0test.log
rm 0test.log

cd srcs > 0test.log
cd ..
cat 0test.log
rm 0test.log

echo
echo 7
echo
echo coucou> test.log
ls
cat test.log
rm test.log

echo
echo 8
echo
echo coucou >test.log
ls
cat test.log
rm test.log

echo
echo 9
echo
echo coucou>test.log
ls
cat test.log
rm test.log


echo coucou > test.log
ls -l test.log
rm tes.log

echo coucou >> test.log
ls -l test.log
rm tes.log

# expected to redir output
export > 0test.log
cat 0test.log | grep 'USER'
rm 0test.log

# expected : bash: ../alientest_minishell/test.log: No such file or directory
echo coucou > ../alientest_minishell/0test.log ; ls
echo coucou >> ../alientest_minishell/0test.log ; ls
echo coucou > ../../0test.log | ls
echo coucou >> ../../0test.log | ls
cat ../../0test.log
rm ../../0test.log
# expected : is a directory
echo lol > srcs | ls
echo lol > srcs


# cree le 0 et le 3
echo coucou > 0test.log 1test.log 2test.log > 3test.log
# rien
cat 0test.log
# coucou 1test.log 2test.log
cat 3test.log
rm 0test.log 3test.log

2> test.log ls sdfsdf


echo coucou >0test.log | cat 0test.log
rm 0test.log
echo test > ls >> ls | echo test
rm ls
# expexted : test\ntest\n
echo test > ls >> ls >> ls | echo test >> ls | cat ls
rm ls

rm test.log