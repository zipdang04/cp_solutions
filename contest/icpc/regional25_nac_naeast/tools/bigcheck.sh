for ((i = 2; i <= 52; i++))
do
	for ((j = 0; j <= i && j <= 10; j++))
	do
		echo "$i $j" | cat > input.txt
		echo "checking" $i $j
		./check.sh
		if [ $? -ne 0 ]
		then
			echo "FUCKED!!!!"
		fi
	done
done
