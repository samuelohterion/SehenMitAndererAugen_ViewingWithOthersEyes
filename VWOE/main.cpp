#include "glview.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <ios>
#include <QMatrix3x3>
#include <QVector3D>

using namespace std;

int
main(	int	p_argc,	char	*p_argv[] ){

	for( int i = 0; i < p_argc; ++i ) {

		std::cout << "arg" << i << " : " << p_argv[ i ] << std::endl;
	}

	QString
	sDir = "../VWOE/shaders/",
	pDir = "../VWOE/pix/";

	if(	1 < p_argc ) {

		sDir = p_argv[ 1 ];
		pDir = p_argv[ 2 ];
	}

	QApplication
	application(	p_argc,	p_argv );

	GLView
	glView( sDir, pDir );

	MainWindow
	mainWindow( &glView );

	mainWindow.show( );

	return
	application.exec( );
}
