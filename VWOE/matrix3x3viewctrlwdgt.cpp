#include "matrix3x3viewctrlwdgt.h"
#include "ui_matrix3x3viewctrlwdgt.h"

Matrix3x3ViewCtrlWdgt::Matrix3x3ViewCtrlWdgt( QWidget *parent ) :
QWidget( parent ),
ui( new Ui::Matrix3x3ViewCtrlWdgt ) {

	ui->setupUi( this );
}

Matrix3x3ViewCtrlWdgt::~Matrix3x3ViewCtrlWdgt( ) {

	delete ui;
}

void
Matrix3x3ViewCtrlWdgt::setModel( Matrix3x3Model * p_matrix3x3Model ) {

	matrix3x3model = p_matrix3x3Model;

//	connect( ui->doubleSpinBox11, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox12, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox13, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );

//	connect( ui->doubleSpinBox21, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox22, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox23, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );

//	connect( ui->doubleSpinBox21, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox22, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
//	connect( ui->doubleSpinBox23, SIGNAL(  editingFinished( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );

	connect( ui->doubleSpinBox11, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell11( double ) ) );
	connect( ui->doubleSpinBox12, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell12( double ) ) );
	connect( ui->doubleSpinBox13, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell13( double ) ) );

	connect( ui->doubleSpinBox21, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell21( double ) ) );
	connect( ui->doubleSpinBox22, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell22( double ) ) );
	connect( ui->doubleSpinBox23, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell23( double ) ) );

	connect( ui->doubleSpinBox31, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell31( double ) ) );
	connect( ui->doubleSpinBox32, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell32( double ) ) );
	connect( ui->doubleSpinBox33, SIGNAL( valueChanged( double ) ), matrix3x3model, SLOT( slotSetCell33( double ) ) );

	connect( matrix3x3model,	SIGNAL( signalMatrixChanged( ) ), this, SLOT( slotUpdateDisplay( ) ) );
	connect( matrix3x3model,	SIGNAL( signalMatrixWritten( ) ), this, SLOT( slotUpdateDisplay( ) ) );
	connect( matrix3x3model,	SIGNAL( signalMatrixChanged( QMatrix3x3 ) ), this, SLOT( slotPipeSignalContentChanged( QMatrix3x3 ) ) );
	connect( matrix3x3model,	SIGNAL( signalMatrixChanged( ) ), this, SLOT( slotPipeSignalContentChanged( ) ) );
}

void
Matrix3x3ViewCtrlWdgt::slotUpdateDisplay( ) {

	this->blockSignals( true );

	ui->doubleSpinBox11->setValue(	matrix3x3model->getCell( 0, 0 ) );
	ui->doubleSpinBox12->setValue(	matrix3x3model->getCell( 0, 1 ) );
	ui->doubleSpinBox13->setValue(	matrix3x3model->getCell( 0, 2 ) );

	ui->doubleSpinBox21->setValue(	matrix3x3model->getCell( 1, 0 ) );
	ui->doubleSpinBox22->setValue(	matrix3x3model->getCell( 1, 1 ) );
	ui->doubleSpinBox23->setValue(	matrix3x3model->getCell( 1, 2 ) );

	ui->doubleSpinBox31->setValue(	matrix3x3model->getCell( 2, 0 ) );
	ui->doubleSpinBox32->setValue(	matrix3x3model->getCell( 2, 1 ) );
	ui->doubleSpinBox33->setValue(	matrix3x3model->getCell( 2, 2 ) );

	this->blockSignals( false );

	emit signalDisplayUpdated( );
}

void
Matrix3x3ViewCtrlWdgt::slotWriteMatrix3x3( QMatrix3x3 p_matrix3x3 ) {

	matrix3x3model->slotWriteMatrix( p_matrix3x3 );

	emit signalContentWritten( );
	emit signalContentWritten( p_matrix3x3 );
}

//void
//Matrix3x3ViewCtrlWdgt::slotSetMatrix3x3( QMatrix3x3 p_matrix3x3 ) {

//	matrix3x3model->slotSetMatrix( p_matrix3x3 );

//	emit signalContentChanged( );
//	emit signalContentChanged( p_matrix3x3 );
//}

void
Matrix3x3ViewCtrlWdgt::slotPipeSignalContentChanged( ) {

	emit signalContentChanged( );
	emit signalContentChanged( matrix3x3model->getMatrix( ) );
}

void
Matrix3x3ViewCtrlWdgt::slotPipeSignalContentChanged( QMatrix3x3 p_matrix3x3 ) {

	emit signalContentChanged( );
	emit signalContentChanged( p_matrix3x3 );
}
