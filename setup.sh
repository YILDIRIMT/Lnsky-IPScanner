function setup(){
	echo "BUILDING..."
	if [ "$1" = 1 ]; then
		cd src
		make make_apt
		cd ..
	else
		cd src
		make make_pac
		cd ..
	fi
	cp -r src/ /opt/
	mv /opt/src /opt/Lnsky
	cp -r src/bin/sys /bin/
	if [ "$1" = 1 ]; then
		cp -r script_01/ /opt/Lnsky
		mv /opt/Lnsky/script_01 /opt/Lnsky/script
		chmod +x /opt/Lnsky/script
	else
		cp -r script_02/ /opt/Lnsky
		mv /opt/Lnsky/script_02 /opt/Lnsky/script
		chmod +x /opt/Lnsky/script
	fi
	mv /bin/sys /bin/lnskyip
	chmod +x /bin/lnskyip
	echo "INSTALLED Lnsky-IPScanner";
}

remove(){
	rm -rf /opt/Lnsky
	rm /bin/lnskyip
	echo "REMOVED Lnsky-IPScanner"
}

if [ "$EUID" -ne 0 ]; then
    echo "Must be run with sudo"
    exit
fi

echo "1-APT  2-PACMAN 3-REMOVE/Lnsky-IPScanner" 
read -p ">" PACKAGE_MNG

if [ "$PACKAGE_MNG" = 1 ]; then
	sudo apt install qt6ct
	sudo apt install qt6-base-dev
	sudo apt install qt6-base-dev-tools
	sudo apt install fping
	sudo apt install net-tools
	setup $PACKAGE_MNG
	exit
elif [ "$PACKAGE_MNG" = 2 ]; then
	echo "SYSTEM NEED YAY"
	sudo pacman -S qt6
	sudo pacman -S qt6-base	
	sudo pacman -S fping
	sudo pacman -S net-tools
	setup $PACKAGE_MNG
	exit
elif [ "$PACKAGE_MNG" = 3 ]; then
	remove
	exit
else
	echo "WRONG INPUT";
	exit
fi
