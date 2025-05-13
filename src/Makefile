make_pac:
	g++ -fPIC -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtGui -I/usr/include/qt6/QtWidgets main.cpp -o bin/lnsky.bin -L/usr/lib/qt6/lib -lQt6Core -lQt6Gui -lQt6Widgets

make_apt:
	g++ -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets main.cpp -o bin/lnsky.bin -L/usr/lib/qt6/lib -lQt6Core -lQt6Gui -lQt6Widgets

run:
	./bin/lnsky.bin
	
clean:
	rm bin/lnsky.bin
