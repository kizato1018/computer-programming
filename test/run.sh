TAR="$1"
IN=0
#IN="$2"
if [ $# == 1 ]
then
	./$TAR
elif [ $# == 2 ]
then
	./$TAR<./$TAR.in
else
	echo "wrong command"
fi