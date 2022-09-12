echo "--- TESTS PIPE ---"

echo "0 : expected output : coucou"
echo "coucou
bonjour
salut" | grep coucou
echo

echo "1 : expected output : coucou"
echo | echo coucou
echo

echo "2 : expected output : coucou$"
echo | echo coucou | cat -e
echo

echo "3 : expected output : coucou"
ls | echo coucou
echo

echo "4 : expected output : ls output"
echo coucou | ls
echo

echo "5 : expected output : ls output with $"
ls | cat -e
echo

echo "6 : expected output : ls sorted output"
ls | sort
echo

echo "7 : expected output : .sh files"
ls header/ | grep .h
echo

echo "8 : expected output : sorted .sh files"
ls srcs/ | grep .c | sort
echo

echo "9 : expected output : sorted .sh files with $"
ls srcs/ | grep .c | sort | cat -e
echo

echo "10 : expected output : one ls output"
ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls 
echo 

echo
cat a | < b cat | cat > c | cat
ls | grep c
echo

echo
"$HOME" | "$HOME"
"$HOME" | '$HOME'
$HOME | $HOME
echo
