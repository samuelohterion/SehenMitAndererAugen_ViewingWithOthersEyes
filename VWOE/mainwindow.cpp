#include	"mainwindow.h"
#include	"ui_mainwindow.h"

MainWindow::MainWindow(	GLView  *p_glView, QWidget	*p_parent ):
QMainWindow(	p_parent ),
ui(	new	Ui::MainWindow ),
glView( p_glView ){

	ui->setupUi(	this );

	parameterKonverter = new ParameterKonverter( &glView->parameterVerhalten, &parameterFehlsichtigkeit, &glView->parameterSimulation, this );

	ui->matrix3x3ViewCtrlWdgt->setModel( &parameterKonverter->matrix3x3Model );

	connect( ui->radioButtonKeinSplitscreen, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeVerhaltenTypAufAUS( ) ) );
	connect( ui->radioButtonHorizontalerSplitScreen, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeVerhaltenTypAufHORIZONTAL( ) ) );
	connect( ui->radioButtonVertikalerSplitScreen, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeVerhaltenTypAufVERTIKAL( ) ) );

	connect( ui->radioButtonKeinSplitscreen, SIGNAL( clicked( ) ), glView, SLOT( slotErneuereFensterGeometrie( ) ) );
	connect( ui->radioButtonHorizontalerSplitScreen, SIGNAL( clicked( ) ), glView, SLOT( slotErneuereFensterGeometrie( ) ) );
	connect( ui->radioButtonVertikalerSplitScreen, SIGNAL( clicked( ) ), glView, SLOT( slotErneuereFensterGeometrie( ) ) );

	connect( ui->radioButtonVerzerrungTypGauss, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeVerzerrungModellTypAufGAUSS( ) ) );
	connect( ui->radioButtonVerzerrungTypGlaskugel, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeVerzerrungModellTypAufKUGEL( ) ) );


	connect( ui->horizontalSliderGesichtsfeldausfaelleStufe,	SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeGesichtsfeldausfaelleStufeAuf(int ) ) );
	connect( ui->horizontalSliderGesichtsfeldausfaelleGroesse, SIGNAL(valueChanged( int ) ), parameterKonverter, SLOT(slotSetzeGesichtsfeldausfaelleGroesseAuf( int ) ) );
	connect( ui->horizontalSliderKontrastempfindlichkeit, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeKontrastempfindlichkeitAuf( int ) ) );
	connect( ui->horizontalSliderLinseneintruebung, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeLinseneintruebungAuf( int ) ) );
	connect( ui->horizontalSliderSehschaerfe, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeSehschaerfeAuf( int ) ) );
	connect( ui->horizontalSliderVerzerrungenAmplitude, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeVerzerrungAmplitudeAuf( int ) ) );
	connect( ui->horizontalSliderVerzerrungenRadius, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeVerzerrungRadiusAuf( int ) ) );

	connect( ui->horizontalSliderGesichtsfeldausfaelleStufe,	SIGNAL( valueChanged( int ) ), ui->labelGesichtsfeldausfaelleStufeWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderGesichtsfeldausfaelleGroesse,	SIGNAL( valueChanged( int ) ), ui->labelGesichtsfeldausfaelleGroesseWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderKontrastempfindlichkeit, SIGNAL( valueChanged( int ) ), ui->labelKontrastempfindlichkeitWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderLinseneintruebung, SIGNAL( valueChanged( int ) ), ui->labelLinseneintruebungWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderSehschaerfe, SIGNAL( valueChanged( int ) ), ui->labelSehschaerfeWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderVerzerrungenAmplitude, SIGNAL( valueChanged( int ) ), ui->labelVerzerrungenAmplitudeWert, SLOT( setNum( int ) ) );
	connect( ui->horizontalSliderVerzerrungenRadius, SIGNAL( valueChanged( int ) ), ui->labelVerzerrungenRadiusWert, SLOT( setNum( int ) ) );

	connect( ui->radioButtonFarbfehlsichtigkeitTypKeine, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufKeine( ) ) );
	connect( ui->radioButtonFarbfehlsichtigkeitTypProtanopie, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufProtanopie( ) ) );
	connect( ui->radioButtonFarbfehlsichtigkeitTypDeuteranopie, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufDeuteranopie( ) ) );
	connect( ui->radioButtonFarbfehlsichtigkeitTypTritanopie, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufTritanopie( ) ) );
	connect( ui->radioButtonFarbfehlsichtigkeitTypAchromatopsie, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufAchromatopsie( ) ) );
	connect( ui->radioButtonFarbfehlsichtigkeitTypNutzerdefiniert, SIGNAL( clicked( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufNutzerdefiniert( ) ) );

	connect( ui->verticalSliderFarbfehlsichtigkeitAmplitude, SIGNAL( valueChanged( int ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitAmplitudeAuf( int ) ) );
	connect( ui->verticalSliderFarbfehlsichtigkeitAmplitude, SIGNAL( valueChanged( int ) ), ui->labelFarbfehlsichtigkeitWert, SLOT( setNum( int ) ) );

	connect( ui->matrix3x3ViewCtrlWdgt, SIGNAL( signalContentChanged( ) ), parameterKonverter, SLOT( slotSetzeFarbfehlsichtigkeitTypAufNutzerdefiniert( ) ) );
	connect( ui->matrix3x3ViewCtrlWdgt, SIGNAL( signalContentChanged( ) ), ui->radioButtonFarbfehlsichtigkeitTypNutzerdefiniert, SLOT( click( ) ) );

	parameterKonverter->slotInit( );
}

MainWindow::~MainWindow( ){

	delete	ui;
}

void
MainWindow::closeEvent( QCloseEvent *p_closeEvent ){

	glView->close( );

	p_closeEvent->accept( );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypKeine_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( false );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( false );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( false );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypProtanopie_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( true );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( true );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( true );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypDeuteranopie_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( true );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( true );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( true );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypTritanopie_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( true );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( true );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( true );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypAchromatopsie_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( true );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( true );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( true );
}

void
MainWindow::on_radioButtonFarbfehlsichtigkeitTypNutzerdefiniert_clicked( ) {

	ui->verticalSliderFarbfehlsichtigkeitAmplitude->setEnabled( false );
	ui->labelFarbfehlsichtigkeitWert->setEnabled( false );
	ui->labelFarbfehlsichtigkeitProzentZeichen->setEnabled( false );
}

void
MainWindow::on_commandLinkButton_released( ) {

	QDesktopServices::openUrl( QString( "https://samuelohterion.wordpress.com/smam/" ) );
}

void
MainWindow::on_commandLinkButton_2_released( ) {

	QDesktopServices::openUrl( QString( "http://genumedia.htwk-leipzig.de/de/projekte/interaktionsdesign-zur-barrierefreien-bereitstellung-von-informationen/" ) );
}
