make:
	g++ -fPIC -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets main.cpp -o bin/lnsky.bin -L/usr/lib/x86_64-linux-gnu/qt5/lib -lQt5Core -lQt5Gui -lQt5Widgets

mr:
	g++ -fPIC -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets main.cpp -o bin/lnsky.bin -L/usr/lib/x86_64-linux-gnu/qt5/lib -lQt5Core -lQt5Gui -lQt5Widgets
	./bin/lnsky.bin

run:
	./bin/lnsky.bin
	
clean:
	rm bin/lnsky.bin
