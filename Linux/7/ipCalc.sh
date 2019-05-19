#!/bin/bash


function decToBin {
	echo "obase=2;$1" | bc | awk '{printf "%08d\n", $0}'
}

function binToDec {
	echo "ibase=2;obase=A;$1" | bc
}

function busyBitCount {
	echo "obase=2;$1" | bc | tr -cd '1' | wc -c
}

function binaryOperation {
	echo "ibase=2;obase=2; $1$2$3" | bc -l | awk '{printf "%032s\n", $0}' | tr ' ' '0'
}

function valToAddr {
	echo "$1" | sed -e "s/.\{8\}/&./" -e "s/.\{17\}/&./" -e "s/.\{26\}/&./"
}

IFS='. '

read ip_d[0] ip_d[1] ip_d[2] ip_d[3] <<< "$1"
read m_d[0] m_d[1] m_d[2] m_d[3] <<< "$2"

for ((i=0; i!=4; ++i)); do
	ip_b[i]=$(decToBin ${ip_d[i]})
	m_b[i]=$(decToBin ${m_d[i]})
    network_d[i]=$((${ip_d[i]} & ${m_d[i]}))
    network_b[i]=$(decToBin ${network_d[i]})
    hmin_d[i]=${network_d[i]}
done
hmin_d[3]=$((${network_d[3]} + 1))

for ((i=0; i!=4; ++i)); do
    bitmask=$((bitmask + $(busyBitCount ${m_d[i]})))
done

broadcast_val="${network_b[0]}${network_b[1]}${network_b[2]}${network_b[3]}"

if (($bitmask != 32)); then
	net_val=$broadcast_val
	hostmax_val=$(printf '1%.0s' $(eval "echo {1.."$((32 - $bitmask))"}"))
	broadcast_val=$(binaryOperation $net_val + $hostmax_val)
fi

broadcast=$(valToAddr $broadcast_val)
hostmax=$(valToAddr $(binaryOperation $broadcast_val - 1))

read b_b[0] b_b[1] b_b[2] b_b[3] <<< "$broadcast"
read hmax_b[0] hmax_b[1] hmax_b[2] hmax_b[3] <<< "$hostmax"

for ((i=0; i!=4; ++i)); do
	hmin_b[i]=$(decToBin ${hmin_d[i]})
	hmax_d[i]=$(binToDec ${hmax_b[i]})
	b_d[i]=$(binToDec ${b_b[i]})
done

echo -e "IP address:\t${ip_d[0]} ${ip_d[1]} ${ip_d[2]} ${ip_d[3]}\c" | sed 's/ /./g'
echo -e "\t${ip_b[0]} ${ip_b[1]} ${ip_b[2]} ${ip_b[3]}" | sed 's/ /./g'

echo -e "Netmask:\t${m_d[0]} ${m_d[1]} ${m_d[2]} ${m_d[3]}\c" | sed 's/ /./g'
echo -e "\t${m_b[0]} ${m_b[1]} ${m_b[2]} ${m_b[3]}" | sed 's/ /./g'

echo -e "Bitmask:\t$bitmask"

echo -e "Network:\t${network_d[0]} ${network_d[1]} ${network_d[2]} ${network_d[3]}\c" | sed 's/ /./g'
echo -e "\t${network_b[0]} ${network_b[1]} ${network_b[2]} ${network_b[3]}" | sed 's/ /./g'

echo -e "Hostmin:\t${hmin_d[0]} ${hmin_d[1]} ${hmin_d[2]} ${hmin_d[3]}\c" | sed 's/ /./g'
echo -e "\t${hmin_b[0]} ${hmin_b[1]} ${hmin_b[2]} ${hmin_b[3]}" | sed 's/ /./g'

echo -e "Hostmax:\t${hmax_d[0]} ${hmax_d[1]} ${hmax_d[2]} ${hmax_d[3]}\c" | sed 's/ /./g'
echo -e "\t${hmax_b[0]} ${hmax_b[1]} ${hmax_b[2]} ${hmax_b[3]}" | sed 's/ /./g'

echo -e "Broadcast:\t${b_d[0]} ${b_d[1]} ${b_d[2]} ${b_d[3]}\c" | sed 's/ /./g'
echo -e "\t${b_b[0]} ${b_b[1]} ${b_b[2]} ${b_b[3]}" | sed 's/ /./g'