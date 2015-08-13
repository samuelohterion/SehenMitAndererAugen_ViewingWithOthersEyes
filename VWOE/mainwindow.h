#ifndef	MAINWINDOW_H
#define	MAINWINDOW_H

#include <QMainWindow>
#include "glview.h"
#include "matrix3x3model.h"
#include "parameterkonverter.h"
#include "parameterverhalten.h"
#include <QDesktopServices>

namespace	Ui{

	class	MainWindow;
}

class	MainWindow:
public	QMainWindow{

		Q_OBJECT

	public:

		explicit
		MainWindow(	GLView  *p_glView, QWidget	*p_parent = 0 );

		~MainWindow();

	private:

		Ui::MainWindow
		*ui;

	public:

		GLView *
		glView;

		ParameterKonverter *
		parameterKonverter;

		ParameterFehlsichtigkeit
		parameterFehlsichtigkeit;

	protected:

		void
		closeEvent( QCloseEvent *p_closeEvent );

	public slots:

	private slots:

		void
		on_radioButtonFarbfehlsichtigkeitTypKeine_clicked( );

		void
		on_radioButtonFarbfehlsichtigkeitTypProtanopie_clicked( );

		void
		on_radioButtonFarbfehlsichtigkeitTypDeuteranopie_clicked( );

		void
		on_radioButtonFarbfehlsichtigkeitTypTritanopie_clicked( );

		void
		on_radioButtonFarbfehlsichtigkeitTypAchromatopsie_clicked( );

		void
		on_radioButtonFarbfehlsichtigkeitTypNutzerdefiniert_clicked( );

		void
		on_commandLinkButton_released( );
		void on_commandLinkButton_2_released();
};

#endif // MAINWINDOW_H
