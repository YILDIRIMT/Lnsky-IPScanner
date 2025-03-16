#!/bin/bash

current_ip=$1
paste <(nslookup $current_ip | grep 'name' | awk '{print $4}') <(timeout 0.1 ping -c 1 $current_ip | grep time= | awk -F'time=' '{print $2}')
