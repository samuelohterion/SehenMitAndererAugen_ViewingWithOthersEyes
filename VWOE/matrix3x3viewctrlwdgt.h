#ifndef MATRX3X3VIEWCTL_H
#define MATRX3X3VIEWCTL_H

#include <QWidget>
#include "matrix3x3model.h"

namespace Ui {

	class Matrix3x3ViewCtrlWdgt;
}

class
Matrix3x3ViewCtrlWdgt :
public QWidget {

		Q_OBJECT

	public:

		explicit
		Matrix3x3ViewCtrlWdgt( QWidget * parent = 0 );

		~Matrix3x3ViewCtrlWdgt( );

	private:

		Ui::Matrix3x3ViewCtrlWdgt *
		ui;

		Matrix3x3Model *
		matrix3x3model;

	public:

		void
		setModel( Matrix3x3Model * p_matrix3x3Model );

	signals:

		void
		signalContentChanged( );

		void
		signalContentChanged( QMatrix3x3 );

		void
		signalContentWritten( );

		void
		signalContentWritten( QMatrix3x3 );

		void
		signalDisplayUpdated( );

	private slots:

//		void
//		slotSetMatrix3x3(	QMatrix3x3 p_matrix3x3 );

		void
		slotPipeSignalContentChanged( );

		void
		slotPipeSignalContentChanged( QMatrix3x3 p_matrix3x3 );

	public slots:

		void
		slotUpdateDisplay( );

		void
		slotWriteMatrix3x3(	QMatrix3x3 p_matrix3x3 );
};

#endif // MATRX3X3VIEWCTL_H
