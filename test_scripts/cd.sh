echo "--- TESTS CD & PWD ---"

pwd
mkdir ftest
cd ./ftest
pwd
cd ..
"cd .."
rm -rf ./ftest
cd ./ftest
cd .
pwd

cd ~/Documents/minishell
cd $HOME/Documents/minishell

unset PWD
unset OLDPWD
pwd
cd ..
pwd

cd ./NOFILE
echo $?