#!/bin/bash

#porownywanie zmiennych
#	if (( $i == 6 )) ...
#porownywanie napisow
#	if (( $x == "abecadlo" )) ...
#porownywanie wartosci boolowych
#	if (( $x == true )) ... - jest poprawne
#	if ( $x == true ) .. - to też jest poprawne
#	if [ $x == true ] ... - to też
#	if [[ $x == true ]] .. - to też


rm -r gra/test*
for (( i=1; $i <= 5; i++ ))
do
	echo ". . . . ."
done
i=1
while (( $i <= 5 ))
do
	echo "---------"
	i=$[i+1]
done
echo $i
x=true
if ( $x )
then 
	echo "Tak1"
fi
if (( $x ))
then 
	echo "Tak2"
fi
if [ $x ]
then 
	echo "Tak3"
fi
if [[ $x ]]
then 
	echo "Tak4"
fi
#if (( $i == 6 )) echo "Tak2"
#if [ "$i" == 6 ] echo "Tak3"
#if ( $i == 6 ) echo "Tak4"
