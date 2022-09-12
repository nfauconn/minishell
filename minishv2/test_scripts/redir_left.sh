echo "--- TEST REDIR LEFT ---"
#0test.log << cat Makefile -> fait planter le programme
#sort -n << FIN > 0test.log
#cat << dg
#cat << "dg"

ls > 0test.log
echo phase 1 ok
echo
sort < 0test.log
echo
echo phase 2 ok
echo
grep Makefile < 0test.log
echo
echo phase 3 ok
echo
rm 0test.log

echo coucou les zouzous > 0test.log
echo bonjour.sh >> 0test.log
echo salut.sh >> 0test.log
echo hello.sh >> 0test.log

echo phase 1 ok
echo ls /srcs > 0test.log
sort < 0test.log
echo
echo phase 2 ok
echo
grep .c < 0test.log
echo
echo phase 3 ok
echo
rm 0test.log

sort < 0test.log