echo "testing $1"
./ft_nm $1 &> mine
nm $1 &> ref
diff mine ref
if [ "$?" -eq 0 ]
then
	echo Sucess.
else
	echo Fail.
fi
