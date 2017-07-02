#!/bin/bash

memory=0
n_wielkosc_planszy=10
k_max_liczba_tur=100
s_czas=1
x1=0
y1=0
x2=0
y2=0
ai1=""
ai2=""

function generate_random_value
{
	rand=$RANDOM
	memory=$rand
	rand=$RANDOM
	memory=$(( memory + rand * 10000 ))
	rand=$RANDOM
	memory=$(( memory + rand * 100000000 ))
	memory=$(( memory % 2147483647 + 1 ))
}

function set_positions_1
{
	generate_random_value
	x1=$(( memory % (n_wielkosc_planszy - 3) + 1 ))
	generate_random_value
	y1=$(( memory % (n_wielkosc_planszy) + 1 ))
}

function set_positions_2
{
	generate_random_value
	x2=$(( memory % (n_wielkosc_planszy - 3) + 1 ))
	generate_random_value
	y2=$(( memory % (n_wielkosc_planszy) + 1 ))
}

function set_positions
{
	set_positions_1
	set_positions_2
}

while [[ $# > 0 ]]
do
	if [[ $1 == "-n" || $1 == "-k" || $1 == "-s" ]]
	then
		if ! [ "$2" -eq "$2" ]
		then
			exit 1
		fi
		if [ $2 -gt 2147483647 ]
		then
			exit 1
		fi
	fi
	if [[ $1 == "-p1" || $1 == "-p2" ]]
	then
		if ! [ "${2%,*}" -eq "${2%,*}" ]
		then
			exit 1
		fi
		if ! [ "${2#*,}" -eq "${2#*,}" ]
		then
			exit 1
		fi
	fi
	if [[ $1 == "-p1" ]]
	then
		w_lewo=${2%,*}
		w_lewo=$((w_lewo - n_wielkosc_planszy))
		do_gory=${2#*,}
		do_gory=$((do_gory - n_wielkosc_planszy))
		if (( (($w_lewo < 8)) && (($w_lewo > -8)) && (($do_gory < 8)) && (($do_gory > -8)) ))
		then
			exit 1
		fi
	fi
	
	
	case $1 in
	"-n")
		n_wielkosc_planszy=$2;;
	"-k")
		k_max_liczba_tur=$2;;
	"-s")
		s_czas=$2;;
	"-p1")
		x1=${2%,*}
		y1=${2#*,};;
	"-p2")
		x2=${2%,*}
		y2=${2#*,};;
	"-ai1")
		ai1=$2;;
	"-ai2")
		ai2=$2;;
	*)
		exit 1;;
	esac
	shift 2
done
if (( $n_wielkosc_planszy < 9 )); then
	exit 1
fi

if [[ $x1 = 0 && $y1 = 0 ]]
then
	if [[ $x2 = 0 && $y2 = 0 ]]; then
		set_positions
		x=$((x1 - x2))
		y=$((y1 - y2))
		while (( (($x < 8)) && (($x > -8)) && (($y < 8)) && (($y > -8)) ))
		do
			set_positions
			x=$((x1 - x2))
			y=$((y1 - y2))
		done
	else
		set_positions_1
		x=$((x1 - x2))
		y=$((y1 - y2))
		while (( (($x < 8)) && (($x > -8)) && (($y < 8)) && (($y > -8)) ))
		do
			set_positions_1
			x=$((x1 - x2))
			y=$((y1 - y2))
		done
	fi
else
	if [[ $x2 = 0 && $y2 = 0 ]]
	then
		set_positions_2
		x=$((x1 - x2))
		y=$((y1 - y2))
		while (( (($x < 8)) && (($x > -8)) && (($y < 8)) && (($y > -8)) ))
		do
			set_positions_2
			x=$((x1 - x2))
			y=$((y1 - y2))
		done
	fi
fi

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 3<>$PIPE
rm $PIPE

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 4<>$PIPE
rm $PIPE

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 5<>$PIPE
rm $PIPE

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 6<>$PIPE
rm $PIPE

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 7<>$PIPE
rm $PIPE

PIPE=$(mktemp -u)
mkfifo $PIPE
exec 8<>$PIPE
rm $PIPE


if [[ $ai1 = "" && $ai2 = "" ]]
then
	./sredniowiecze_gui_with_libs.sh -human1 -human2 <&3 >&4 &
	PID1=$!
	echo "INIT $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2" >&3
	echo "INIT $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2" >&3
	wait
elif [[ $ai1 = "" ]]
then
	./sredniowiecze_gui_with_libs.sh -human1 <&3 >&4 &
	PID1=$!
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2 >&3
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2 >&3
	$ai2 <&5 >&6 &
	PID2=$!
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2 >&5
	for (( i = 0; $i < $k_max_liczba_tur; i++ ));
	do
		read -t 0.2 move <&4
		if (( $? == 142 ))
		then
			kill $PID2
			exit 1
		fi
		echo $move >&5
		
		if [[ $move != "END_TURN" ]]
		then
			if ! ( test -d /proc/$PID2 )
			then
				wait $PID2
				if (( $? < 0 || $? > 2 ))
				then
					kill $PID1
					exit 1
				else
					kill $PID1
					exit 0
				fi
			fi
			while [[ $move != "END_TURN" ]]
			do
				read -t 0.2 move <&4
				if (( $? == 142 ))
				then
					kill $PID2
					exit 1
				fi
				echo $move >&5
				if [[ $move != "END_TURN" ]]  
				then
					if ! ( test -d /proc/$PID2 )
					then
						wait $PID2
						if (( $? < 0 || $? > 2 ))
						then
							kill $PID1
							exit 1
						else
							kill $PID1
							exit 0
						fi
					fi
				fi
			done
		fi
		read -t 0.2 move <&6
		if (( $? == 142 ))
		then
			kill $PID1
			exit 1
		fi
		echo $move >&3 # TEST 7 wczytałem 2 6 3 6 powinien nastąpić koniec
		if ! ( test -d /proc/$PID1 )
		then
			wait $PID1
			if (( $? != 0 ))
			then
				kill $PID2
				exit 1
			else
				kill $PID2
				exit 0
			fi
		fi
		while [[ $move != "END_TURN" ]]
		do
			read -t 0.2 move <&6
			if (( $? == 142 ))
			then
				kill $PID1
				exit 1
			fi
			echo $move >&3
			if ! ( test -d /proc/$PID1 )
			then
				wait $PID1
				if (( $? != 0 ))
				then
					kill $PID2
					exit 1
				else
					kill $PID2
					exit 0
				fi
			fi
		done
	done
	if ( test -d /proc/$PID1 )
	then
		kill $PID1
	fi
	if ( test -d /proc/$PID2 )
	then
		kill $PID2
	fi
elif [[ $ai2 = "" ]]
then
	./sredniowiecze_gui_with_libs.sh -human2 <&3 >&4 &
	PID1=$!
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2 >&3
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2 >&3
	$ai1 <&5 >&6 &
	PID3=$!
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2 >&5
	for (( iterator=1; iterator <= $k_max_liczba_tur; iterator++ ));
	do
		read -t 0.2 move <&6
		if (( $? == 142 ))
		then
			kill $PID1
			exit 1
		fi
		echo $move >&3
		if ! ( test -d /proc/$PID1 )
		then
			wait $PID1
			if (( $? != 0 ))
			then
				kill $PID3
				exit 1
			else
				kill $PID3
				exit 0
			fi
		fi
		while [[ $move != "END_TURN" ]]
		do
			read -t 0.2 move <&6
			if (( $? == 142 ))
			then
				kill $PID1
				exit 1
			fi
			echo $move >&3
			if ! ( test -d /proc/$PID1 )
			then
				wait $PID1
				if (( $? != 0 ))
				then
					kill $PID3
					exit 1
				else
					kill $PID3
					exit 0
				fi
			fi
		done
		read -t 0.2 move <&4
		if (( $? == 142 ))
		then
			kill $PID3
			exit 1
		fi
		echo $move >&5
		if ! ( test -d /proc/$PID3 )
		then
			wait $PID3
			if (( $? < 0 || $? > 2 ))
			then
				kill $PID1
				exit 1
			else
				kill $PID1
				exit 0
			fi
		fi
		while [[ $move != "END_TURN" ]]
		do
			read -t 0.2 move <&4
			if (( $? == 142 ))
			then
				kill $PID3
				exit 1
			fi
			echo $move >&5
			if ! ( test -d /proc/$PID3 )
			then
				wait $PID3
				if (( $? < 0 || $? > 2 ))
				then
					kill $PID1
					exit 1
				else
					kill $PID1
					exit 0
				fi
			fi
		done
	done
	if ( test -d /proc/$PID1 )
	then
		kill $PID1
	fi
	if ( test -d /proc/$PID3 )
	then
		kill $PID3
	fi
else
	./sredniowiecze_gui_with_libs.sh <&3 >&4 &
	PID1=$!
	echo "PID = " $PID1
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2 >&3
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2 >&3
	$ai1 <&5 >&6 &
	PID2=$!
	$ai2 <&7 >&8 &
	PID3=$!
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 1 $x1 $y1 $x2 $y2 >&5
	echo "INIT" $n_wielkosc_planszy $k_max_liczba_tur 2 $x1 $y1 $x2 $y2 >&7
	for (( iterator=1; iterator <= $k_max_liczba_tur; iterator++ ));
	do
		read -t 0.2 move <&6
		if (( $? == 142 ))
		then
			kill $PID1
			kill $PID3
			exit 1
		fi
		echo $move >&7
		if ! ( test -d /proc/$PID3 )
		then
			wait $PID3
			if (( $? < 0 || $? > 2 ))
			then
				kill $PID1
				kill $PID2
				exit 1
			else
				kill $PID1
				kill $PID2
				exit 0
			fi
		fi
		echo $move >&3
		if ! ( test -d /proc/$PID1 )
		then
			wait $PID1
			if (( $? != 0 ))
			then
				kill $PID2
				kill $PID3
				exit 1
			else
				kill $PID2
				kill $PID3
				exit 0
			fi
		fi
		while [[ $move != "END_TURN" ]]
		do
			read -t 0.2 move <&6
			if (( $? == 142 ))
			then
				kill $PID1
				kill $PID3
				exit 1
			fi
			echo $move >&7
			if ! ( test -d /proc/$PID3 )
			then
				wait $PID3
				if (( $? < 0 || $? > 2 ))
				then
					kill $PID1
					kill $PID2
					exit 1
				else
					kill $PID1
					kill $PID2
					exit 0
				fi
			fi
			echo $move >&3
			if ! ( test -d /proc/$PID1 )
			then
				wait $PID1
				if (( $? != 0 ))
				then
					kill $PID2
					kill $PID3
					exit 1
				else
					kill $PID2
					kill $PID3
					exit 0
				fi
			fi
		done
		sleep "$s_czas"
		
		read -t 0.2 move <&8
		if (( $? == 142 ))
		then
			kill $PID1
			kill $PID2
			exit 1
		fi
		echo $move >&5
		if ! ( test -d /proc/$PID2 )
		then
			wait $PID2
			if (( $? < 0 || $? > 2 ))
			then
				kill $PID1
				kill $PID3
				exit 1
			else
				kill $PID1
				kill $PID3
				exit 0
			fi
		fi
		echo $move >&3
		if ! ( test -d /proc/$PID1 )
		then
			wait $PID1
			if (( $? != 0 ))
			then
				kill $PID2
				kill $PID3
				exit 1
			else
				kill $PID2
				kill $PID3
				exit 0
			fi
		fi
		while [[ $move != "END_TURN" ]]
		do
			read -t 0.2 move <&8
			if (( $? == 142 ))
			then
				kill $PID1
				kill $PID2
				exit 1
			fi
			echo $move >&5
			if ! ( test -d /proc/$PID2 )
			then
				wait $PID2
				if (( $? < 0 || $? > 2 ))
				then
					kill $PID1
					kill $PID3
					exit 1
				else
					kill $PID1
					kill $PID3
					exit 0
				fi
			fi
			echo $move >&3
			if ! ( test -d /proc/$PID1 )
			then
				wait $PID1
				if (( $? != 0 ))
				then
					kill $PID2
					kill $PID3
					exit 1
				else
					kill $PID2
					kill $PID3
					exit 0
				fi
			fi
		done
		sleep "$s_czas"
	done
fi
if ( kill -0 $PID1 2>/dev/null)
then
	kill $PID1 2>/dev/null
fi
if ( kill -0 $PID2 2>/dev/null)
then
	kill $PID2 2>/dev/null
fi
if ( kill -0 $PID3 2>/dev/null)
then
	kill $PID3 2>/dev/null
fi
exit 0

exec 3>&-
exec 4>&-
exec 5>&-
exec 6>&-
exec 7>&-
exec 8>&-
