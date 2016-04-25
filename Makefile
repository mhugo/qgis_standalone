all: main

QT_DIR=/usr/include/qt4
QGIS_DIR=/usr/local/include/qgis

CFLAGS=-DCORE_EXPORT= -DGUI_EXPORT= -I${QT_DIR} -I${QT_DIR}/QtCore -I${QT_DIR}/QtGui -I${QT_DIR}/QtXml -I${QGIS_DIR} -std=c++11

LIBS=-L/usr/local/lib -lQtCore -lQtGui -lQtXml -lqgis_core -lqgis_gui -lqgis_app

main.o: main.cpp
	clang++ $(CFLAGS) main.cpp -c -o main.o

main: main.o
	clang++ $(LIBS) main.o -o main
