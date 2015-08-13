#include	"matrix3x3model.h"

Matrix3x3Model::Matrix3x3Model( QMatrix3x3 * const p_matrixPtr, QObject * parent ) :
QObject( parent ),
matrixPtr( p_matrixPtr ),
matrix( *matrixPtr ){

}

float
Matrix3x3Model::getCell( int p_row, int p_col ) const {

	return matrix( p_row, p_col );
}

QMatrix3x3
Matrix3x3Model::getMatrix( ) const {

	return matrix;
}

void
Matrix3x3Model::slotSetCell( int p_row, int p_col, float p_val ) {

	matrix( p_row, p_col ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell11( double p_val ) {

	matrix( 0, 0 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell12( double p_val ) {

	matrix( 0, 1 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell13( double p_val ) {

	matrix( 0, 2 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell21( double p_val ) {

	matrix( 1, 0 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell22( double p_val ) {

	matrix( 1, 1 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell23(  double p_val ) {

	matrix( 1, 2 ) = p_val;
	emit signalMatrixChanged( matrix );
}
void
Matrix3x3Model::slotSetCell31(  double p_val ) {

	matrix( 2, 0 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell32(  double p_val ) {

	matrix( 2, 1 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetCell33(  double p_val ) {

	matrix( 2, 2 ) = p_val;
	emit signalMatrixChanged( matrix );
}

void
Matrix3x3Model::slotSetMatrix( QMatrix3x3 p_matri3x3 ) {

	matrix = p_matri3x3;
	emit signalMatrixChanged( );
	emit signalMatrixChanged( getMatrix( ) );
}

void
Matrix3x3Model::slotWriteMatrix( QMatrix3x3 p_matri3x3 ) {

	matrix = p_matri3x3;
	emit signalMatrixWritten( );
	emit signalMatrixWritten( getMatrix( ) );
}


