#ifndef MATRIX3X3MODEL_H
#define MATRIX3X3MODEL_H

#include <QObject>
#include <QMatrix3x3>

class
Matrix3x3Model :
public QObject {

		Q_OBJECT

	public:

		explicit
		Matrix3x3Model( QMatrix3x3 * const p_matrixPtr = 0, QObject * parent = 0 );

	public:

		QMatrix3x3 * const
		matrixPtr;

		QMatrix3x3 &
		matrix;

	public:

		float
		getCell( int p_row, int p_col ) const;

		QMatrix3x3
		getMatrix( ) const;

	signals:

		void
		signalMatrixChanged( );

		void
		signalMatrixChanged( QMatrix3x3 constp_mat );

		void
		signalMatrixWritten( );

		void
		signalMatrixWritten( QMatrix3x3 constp_mat );

	private slots:

		void
		slotSetCell( int p_row, int p_col, float p_val );

		void
		slotSetCell11( double p_val );

		void
		slotSetCell12( double p_val );

		void
		slotSetCell13( double p_val );

		void
		slotSetCell21( double p_val );

		void
		slotSetCell22( double p_val );

		void
		slotSetCell23( double p_val );

		void
		slotSetCell31( double p_val );

		void
		slotSetCell32( double p_val );

		void
		slotSetCell33( double p_val );

		void
		slotSetMatrix( QMatrix3x3 p_matrix3x3 );

	public slots:

		void
		slotWriteMatrix( QMatrix3x3 p_matrix3x3 );
};

#endif // MATRIX3X3MODEL_H
