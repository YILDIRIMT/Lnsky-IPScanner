#!/bin/bash

current_ip=$1
timeout 0.1 ping -c 1 $current_ip | sed -n '2p' | awk '{print $1}'
