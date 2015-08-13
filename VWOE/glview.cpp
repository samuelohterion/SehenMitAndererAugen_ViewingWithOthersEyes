#include	"glview.h"
#include	"ui_glview.h"
#include	<math.h>

GLView::GLView( QString const & p_shadersPath, QString const & p_picturesPath, QWidget	*p_parent ):
QGLWidget(	p_parent ),
ui(	new	Ui::GLView ),
shadersPath( p_shadersPath ),
picturesPath( p_picturesPath ) {

	ui->setupUi(	this );
	this->setWindowFlags(	Qt::ToolTip | Qt::WindowStaysOnTopHint );

	slotErneuereFensterGeometrie( );

	shaderProgram1 = 0;
	shaderProgram2 = 0;
	fboRender = 0;
	aktuellesGlaukom = 0;
	textureGesichtsfeld = 0;

	connect(	&timer,	SIGNAL(	timeout( ) ),
				this,	SLOT(	slotTimerEvent( ) ) );

	screenOnLowerSide   =   false;

	timer.setInterval(	1000. / 60. );

	timer.start();
}

GLView::~GLView( ){

	makeCurrent( );

	delete shaderProgram1;
	delete shaderProgram2;

	delete	ui;
}

void
GLView::initializeGL( ) {

	if(	shaderProgram1 ) {

		shaderProgram1->removeAllShaders( );
		delete shaderProgram1;
		shaderProgram1 = 0;
	}

	shaderProgram1 = erstelleShaderProgramAusDateien( "First.vert", "First.frag" );

	if(	shaderProgram2 ) {

		shaderProgram2->removeAllShaders( );
		delete shaderProgram2;
		shaderProgram2 = 0;
	}

	shaderProgram2 = erstelleShaderProgramAusDateien( "Second.vert", "Second.frag" );

//	createShaders( );

	if( textureGesichtsfeld ) {

		textureGesichtsfeld->release( );
		delete textureGesichtsfeld;
		textureGesichtsfeld = 0;
	}

	textureGesichtsfeld = new QOpenGLTexture( QImage( QString( picturesPath + "glaukom%1.png" ).arg( parameterSimulation.gesichtsfeldausfaelleInStufen ) ).mirrored( false, false ) );
//	textureGesichtsfeld = new QOpenGLTexture( QImage( QString( picturesPath + "glaukom%1.png" ).arg( aktuellesGlaukom ) ).mirrored( false, false ) );

	glClearColor(	0.0f,	0.0f,	0.0f,	1.0f );
	glDisable(	GL_LIGHTING );
}

void
GLView::paintGL( ){

	QImage &
	img = screenShotImage;

	uint
	sR = 0,
	sG = 0,
	sB = 0,
	sA = 0;

	uchar
	* run = img.scanLine( 0 );

	for( int y = 0; y < img.height( ); ++y ) {

		for( int x = 0; x < img.width( ); ++x ) {

			sR += *run++;
			sG += *run++;
			sB += *run++;
			sA += *run++;
		}
	}

//	std::cout << "< R > = " << double( sB ) / double( height( ) * width( ) ) << std::endl;
//	std::cout << "< G > = " << double( sG ) / double( height( ) * width( ) ) << std::endl;
//	std::cout << "< B > = " << double( sR ) / double( height( ) * width( ) ) << std::endl;
//	std::cout << "< A > = " << double( sA ) / double( height( ) * width( ) ) << std::endl;

	float
	factor = 1. / ( 255. * height( ) * width( ) );

	QVector3D
	helligkeit( factor * sR ,factor * sG, factor * sB );
//	helligkeit( factor * ( sB + sG + sB ) / 3., factor * ( sB + sG + sB ) / 3., factor * ( sB + sG + sB ) / 3.);


//	std::cout << "< R + G + B > / 3 = " << helligkeit << std::endl;


	glEnable(	GL_TEXTURE_2D );

	fboRender->bind( );

	glActiveTexture( GL_TEXTURE0 );

	QOpenGLTexture
	texScnGrb( screenShotImage );

	texScnGrb.setMinificationFilter( QOpenGLTexture::Linear );
	texScnGrb.setMagnificationFilter( QOpenGLTexture::Linear );
	texScnGrb.bind( );

	glActiveTexture( GL_TEXTURE1 );

	if( aktuellesGlaukom != parameterSimulation.gesichtsfeldausfaelleInStufen ) {


		if( textureGesichtsfeld ) {

			textureGesichtsfeld->release( );
			delete textureGesichtsfeld;
			textureGesichtsfeld = 0;
		}

		textureGesichtsfeld = new QOpenGLTexture( QImage( QString( picturesPath + "/glaukom%1.png" ).arg( parameterSimulation.gesichtsfeldausfaelleInStufen ) ).mirrored( false, false ) );

		aktuellesGlaukom = parameterSimulation.gesichtsfeldausfaelleInStufen;
	}

	textureGesichtsfeld->setMinificationFilter( QOpenGLTexture::Linear );
	textureGesichtsfeld->setMagnificationFilter( QOpenGLTexture::Linear );
	textureGesichtsfeld->setWrapMode( QOpenGLTexture::ClampToEdge );
	textureGesichtsfeld->bind( );



	shaderProgram1->bind( );
	shaderProgram1->setUniformValue( "texture_", 0 );
	shaderProgram1->setUniformValue( "texture_glaucom_", 1 );
	shaderProgram1->setUniformValue( "mouseX", parameterSimulation.mausX );
	shaderProgram1->setUniformValue( "mouseY", parameterSimulation.mausY );
	shaderProgram1->setUniformValue( "width", parameterSimulation.fensterbreite );
	shaderProgram1->setUniformValue( "height", parameterSimulation.fensterhoehe );
	shaderProgram1->setUniformValue( "invWidth", parameterSimulation.inverseFensterbreite );
	shaderProgram1->setUniformValue( "invHeight", parameterSimulation.inverseFensterhoehe );
	shaderProgram1->setUniformValue( "radiusInX", parameterSimulation.radiusInX );
	shaderProgram1->setUniformValue( "verzerrungRadius", parameterSimulation.verzerrungRadius );
	shaderProgram1->setUniformValue( "verzerrungAmplitude", parameterSimulation.verzerrungAmplitude);
	shaderProgram1->setUniformValue( "verzerrungModell", parameterSimulation.verzerrungModellTyp );
	shaderProgram1->setUniformValue( "farbfehlsichtigkeitsMatrix", parameterSimulation.matrixRGB );
	shaderProgram1->setUniformValue( "kontrast", parameterSimulation.kontrast );
	shaderProgram1->setUniformValue( "helligkeit", helligkeit );
	shaderProgram1->setUniformValueArray( "gaussGewicht", parameterSimulation.gauss, 10, 1 );
	shaderProgram1->setUniformValue( "gesichtsfeldausfaelleGroesse", 1.f - parameterSimulation.gesichtsfeldausfaelleGroesse );

	glBegin(	GL_QUADS );

		glTexCoord2d(	0.0,	1.0 );
		glVertex2d(		-1.0,	-1.0 );

		glTexCoord2d(	1.0,	1.0 );
		glVertex2d(		+1.0,	-1.0 );

		glTexCoord2d(	1.0,	0.0 );
		glVertex2d(		+1.0,	+1.0 );

		glTexCoord2d(	0.0,	0.0 );
		glVertex2d(		-1.0,	+1.0 );

	glEnd( );

	textureGesichtsfeld->release( );
	texScnGrb.release( );
	fboRender->release( );
	shaderProgram1->release( );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, fboRender->texture( ) );
	glTexParameteri(	GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,	GL_NEAREST );
	glTexParameteri(	GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,	GL_NEAREST );


	shaderProgram2->bind( );
	shaderProgram2->setUniformValue( "invWidth", parameterSimulation.inverseFensterbreite );
	shaderProgram2->setUniformValue( "invHeight", parameterSimulation.inverseFensterhoehe );
	shaderProgram2->setUniformValueArray( "gaussGewicht", parameterSimulation.gauss, 10, 1 );

	glBegin( GL_QUADS );

		glTexCoord2d(	0.0,	1.0 );
		glVertex2d(		-1.0,	-1.0 );

		glTexCoord2d(	1.0,	1.0 );
		glVertex2d(		+1.0,	-1.0 );

		glTexCoord2d(	1.0,	0.0 );
		glVertex2d(		+1.0,	+1.0 );

		glTexCoord2d(	0.0,	0.0 );
		glVertex2d(		-1.0,	+1.0 );
	glEnd();

	fboRender->release( );
	shaderProgram2->release( );

	glDisable(	GL_TEXTURE_2D );
}

void
GLView::controlWindowsBehaviour( ) {

	desktopGeometry = QGuiApplication::primaryScreen( )->availableGeometry( );

	mousePos = QCursor::pos( );

	mousePos.setY( mousePos.y( ) - desktopGeometry.y( ) );

	switch( parameterVerhalten.zustand ) {

		case ParameterVerhalten::AUS : {

			if( this->isVisible( ) ) {

				this->setVisible( false );
			}

			if( !this->timer.isActive( ) ) {

				this->timer.stop( );
			}

			return;
		}

		case ParameterVerhalten::HORIZONTAL : {

			if( mousePos.x( ) < desktopGeometry.width( ) / 2 && screenOnLowerSide ){

				this->setGeometry( desktopGeometry.width( ) / 2, desktopGeometry.y( ), desktopGeometry.width( ) / 2, desktopGeometry.height( ) );
				screenOnLowerSide = false;
			}
			else{

				if( mousePos.x( ) >= desktopGeometry.width( ) / 2 && !screenOnLowerSide ){

					this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ), desktopGeometry.width( ) / 2, desktopGeometry.height( ) );
					screenOnLowerSide   =	true;
				}
			}
			break;
		}

		case ParameterVerhalten::VERTIKAL : {

			if( mousePos.y( ) < desktopGeometry.height( ) / 2 && screenOnLowerSide ){

				this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ) + desktopGeometry.height( ) / 2, desktopGeometry.width( ), desktopGeometry.height( ) / 2 );
				screenOnLowerSide = false;
			}
			else{

				if( mousePos.y( ) >= desktopGeometry.height( ) / 2 && !screenOnLowerSide ){

					this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ), desktopGeometry.width( ), desktopGeometry.height( ) / 2 );
					screenOnLowerSide = true;
				}
			}
			break;
		}

		default :
			break;
	}

	parameterSimulation.fensterbreite = desktopGeometry.width( );
	parameterSimulation.fensterhoehe = desktopGeometry.height( );
	parameterSimulation.radiusInX = 0.25 * parameterSimulation.fensterhoehe;

	if( parameterVerhalten.zustand == ParameterVerhalten::VERTIKAL ){

		parameterSimulation.fensterhoehe *= 0.5;
	}
	else{

		parameterSimulation.fensterbreite  *= 0.5;
	}

	parameterSimulation.inverseFensterbreite = 1. / parameterSimulation.fensterbreite;
	parameterSimulation.inverseFensterhoehe = 1. / parameterSimulation.fensterhoehe;

	if( !this->isVisible( ) ) {

		this->show( );
	}

	if( !this->timer.isActive( ) ) {

		this->timer.start( );
	}

}

void
GLView::resizeGL( int p_width, int p_height ) {


	if( fboRender ) {

		delete fboRender;
		fboRender = 0;
	}

	fboRender = new QOpenGLFramebufferObject( p_width, p_height );

	glViewport( 0, 0, p_width, p_height );

	glFrustum( 0, 0, 1, 1, 0, 0 );
}

void
GLView::grabScreen( ){

	if( parameterVerhalten.zustand == ParameterVerhalten::AUS ) {

		return;
	}

//	if(	texture ) {

//		glDeleteTextures( 1,	&texture );
//	}

	QRect
	desktopRect(	QGuiApplication::primaryScreen( )->availableGeometry( ) );

	QPixmap
	pixmap_;

	QScreen
	*screen = QGuiApplication::primaryScreen( );

	switch( parameterVerhalten.zustand ) {

		case ParameterVerhalten::AUS : {

			return;
		}

		case ParameterVerhalten::HORIZONTAL : {

			pixmap_ = screen->grabWindow( QApplication::desktop( )->winId( ), screenOnLowerSide * width( ),	y( ), width( ), height( ) );

			break;
		}

		case ParameterVerhalten::VERTIKAL : {

			pixmap_ =	screen->grabWindow( QApplication::desktop( )->winId( ), x( ),  desktopRect.y( ) + screenOnLowerSide * height( ), width( ), height( ) );

			break;
		}
	}

	screenShotImage	= pixmap_.toImage( );

	GLView::convertToGLFormat(	screenShotImage );
}

void
GLView::createShaders( ) {

	if( shaderProgram1 ) {

		shaderProgram1->removeAllShaders( );
		delete shaderProgram1;
	}

	shaderProgram1 = new QOpenGLShaderProgram( this );

	shaderProgram1->addShaderFromSourceCode(

		QOpenGLShader::Vertex,
		"#version 120\n"

		"void\n"
		"main( ){\n"

		"	gl_Position	= ftransform( );\n"
		"	gl_TexCoord[ 0 ] = gl_MultiTexCoord0;\n"
		"	gl_TexCoord[ 1 ] = gl_MultiTexCoord1;\n"
		"}\n"
	);

	shaderProgram1->addShaderFromSourceCode(

		QOpenGLShader::Fragment,
		"#version 120\n"

		"uniform sampler2D\n"
		"texture_,\n"
		"texture_glaucom_;\n"

		"uniform float\n"
		"mouseX,\n"
		"mouseY,\n"
		"width,\n"
		"height,\n"
		"invWidth,\n"
		"invHeight,\n"
		"radiusInX,\n"
		"verzerrungRadius,\n"
		"verzerrungAmplitude,\n"
		"kontrast,\n"
		"gesichtsfeldausfaelleGroesse;\n"

		"uniform int\n"
		"verzerrungModell;  // 0= keins 1=gauss 2=ball\n"

		"uniform mat3\n"
		"farbfehlsichtigkeitsMatrix;\n"

		"const int\n"
		"halbeKernelBreite = 9;\n"

		"uniform float\n"
		"gaussGewicht[ halbeKernelBreite + 1 ];		// 0 1 2 ... 8 9     das macht eine Kernelgroesse von 19 x 19\n"

		"void\n"
		"main( ){\n"

		"	float\n"
		"	verzerrungRadiusQuadrat = verzerrungRadius * verzerrungRadius;\n"

		"	vec2\n"
		"	pixelPos_	=	gl_TexCoord[ 0 ].st,\n"
		"	mousePos_	=	vec2( mouseX,	mouseY ),\n"
		"	grad_		=	vec2( width, height ) / radiusInX,\n"
		"	gradInv_	=	vec2( invWidth, invHeight ) * radiusInX,\n"
		"	relPos_		=	( pixelPos_ - mousePos_ ) * grad_;\n"


		"	float\n"
		"	distSqr_	=	dot(	relPos_, relPos_ );\n"

		"	if( verzerrungModell == 1  ) {\n"

		"		relPos_	*=	( 1.0 - verzerrungAmplitude * exp( -distSqr_ / ( .5 * 4.0 * verzerrungRadiusQuadrat ) ) );\n"
		"	}\n"
		"	else {\n"

		"		verzerrungRadiusQuadrat *= 4.;\n"

		"		float\n"
		"		vA_ = ( 0.999 - verzerrungAmplitude ),\n"
		"		vA2_ = vA_ * vA_,\n"
		"		vR2_ = verzerrungRadiusQuadrat / ( 1. - vA2_ ),\n"
		"		vR_ = sqrt( vR2_ );\n"

		"		float\n"
		"		verzerrungRadius_ = sqrt( verzerrungRadiusQuadrat );\n"

		"		if( distSqr_ < verzerrungRadiusQuadrat  ) {\n"

		"			float\n"
		"			s = sqrt( distSqr_ / vR2_ );\n"

		"			relPos_ *= 1 + ( vR_ * vA_ - sqrt( vR2_ - distSqr_ ) ) * tan( asin( s ) - asin( .5 * s ) ) / sqrt( distSqr_ );\n"
		"		}\n"
		"	}\n"

		"	relPos_	*=	gradInv_;\n"

		"	vec3\n"
		"	col = texture2D( texture_, relPos_ + mousePos_ ).rgb * gaussGewicht[ 0 ];\n"

		"	vec2\n"
		"	dv = vec2( 0. );\n"

		"	for( int i = 1; i < halbeKernelBreite; ++i ) {\n"

		"		dv.x += invWidth;\n"

		"		col +=	(\n"

		"			texture2D( texture_, relPos_ + mousePos_ - dv ).rgb +\n"
		"			texture2D( texture_, relPos_ + mousePos_ + dv ).rgb\n"
		"		) * gaussGewicht[ i ];\n"
		"	}\n"

		"	gl_FragColor = vec4( col, 1.f );\n"
		"	gl_FragColor.rgb = ( ( gl_FragColor.rgb - 0.5f ) * kontrast ) + .5f;\n"
		"	gl_FragColor.rgb = farbfehlsichtigkeitsMatrix * gl_FragColor.rgb  * ( 1. - texture2D( texture_glaucom_, gesichtsfeldausfaelleGroesse * 2. * relPos_ * grad_ + vec2( 0.5 ) ).a );\n"
		"//	gl_FragColor.rgb = farbfehlsichtigkeitsMatrix * gl_FragColor.rgb  * ( 1. - texture2D( texture_glaucom_, gesichtsfeldausfaelleGroesse * 2. * ( pixelPos_ - mousePos_ ) * grad_ + vec2( .5 ) ).a );\n"
		"}\n"
	);



	if(	!shaderProgram1->link( ) ){

		qWarning( ) << "1st Shader Program Linker Error" << shaderProgram1->log( );

		return;
	}


	if( shaderProgram2 ) {

		shaderProgram2->removeAllShaders( );
		delete shaderProgram2;
	}

	shaderProgram2 = new QOpenGLShaderProgram( this );

	shaderProgram2->addShaderFromSourceCode(

		QOpenGLShader::Vertex,

		"#version 120\n"

		"void\n"
		"main( ){\n"

		"	gl_Position	= ftransform( );\n"
		"	gl_TexCoord[ 0 ] = gl_MultiTexCoord0;\n"
		"	gl_TexCoord[ 0 ].t = 1. - gl_TexCoord[ 0 ].t;\n"
		"}\n"
	);

	shaderProgram2->addShaderFromSourceCode(

		QOpenGLShader::Fragment,

		"#version 120\n"

		"uniform sampler2D\n"
		"texture_;\n"

		"uniform float\n"
		"invWidth,\n"
		"invHeight;\n"

		"const int\n"
		"halbeKernelBreite = 9;\n"

		"uniform float\n"
		"gaussGewicht[ halbeKernelBreite + 1 ];		// 0 1 2 ... 8 9     das macht eine Kernelgroesse von 19 x 19\n"

		"void main( void ) {\n"

		"	vec3\n"
		"	col = texture2D( texture_, gl_TexCoord[ 0 ].st ).rgb * gaussGewicht[ 0 ];\n"

		"	vec2\n"
		"	dv = vec2( 0. );\n"

		"	for( int i = 1; i < halbeKernelBreite; ++i ) {\n"

		"		dv.y += invHeight;\n"

		"		col +=	(\n"
		"			texture2D( texture_, gl_TexCoord[ 0 ].st - dv ).rgb +\n"
		"			texture2D( texture_, gl_TexCoord[ 0 ].st + dv ).rgb\n"
		"		) * gaussGewicht[ i ];\n"
		"	}\n"

		"	gl_FragColor = vec4( col, 1.f );\n"
		"}\n"
	);

	if(	!shaderProgram2->link( ) ){

		qWarning( ) << "1st Shader Program Linker Error" << shaderProgram2->log( );

		return;
	}
}

QOpenGLShaderProgram *
GLView::erstelleShaderProgramAusDateien( QString const & p_filenameVertexShader, QString const & p_filenameFragmentShader ) {

	QOpenGLShaderProgram
	* shaderProgram = new QOpenGLShaderProgram( this );

	if( !shaderProgram ) {

		qWarning( ) << "Shader Programm konnte nicht erzeugt werden.\n";

		return 0;
	}

	if(	!shaderProgram->addShaderFromSourceFile( QOpenGLShader::Vertex, shadersPath + "/" + p_filenameVertexShader ) ){

		shaderProgram->removeAllShaders( );
		delete shaderProgram;
		shaderProgram = 0;
		qWarning( ) << "Vertex Shader konnte nicht geladen oder kompiliert werden.\n";

		return 0;
	}

	if(	!shaderProgram->addShaderFromSourceFile( QOpenGLShader::Fragment, shadersPath + "/" + p_filenameFragmentShader ) ){

		shaderProgram->removeAllShaders( );
		delete shaderProgram;
		shaderProgram = 0;
		qWarning( ) << "Fragment Shader konnte nicht geladen oder kompiliert werden.\n";

		return 0;
	}

	if(	!shaderProgram->link( ) ){

		qWarning( ) << "Shader Programm konnte nicht gelinkt werden.\n";

		return  0;
	}

	 return shaderProgram;
}

void
GLView::slotErneuereFensterGeometrie( ) {

	desktopGeometry = QGuiApplication::primaryScreen( )->availableGeometry( );

	mousePos = QCursor::pos( );

//	mousePos.setY( mousePos.y( ) - desktopGeometry.y( ) );

	switch( parameterVerhalten.zustand ) {

		case ParameterVerhalten::AUS : {

			if( this->isVisible( ) ) {

				this->setVisible( false );
			}

			if( !this->timer.isActive( ) ) {

				this->timer.stop( );
			}

			return;
		}

		case ParameterVerhalten::HORIZONTAL : {

			if( mousePos.x( ) < desktopGeometry.width( ) / 2 ){

				this->setGeometry( desktopGeometry.width( ) / 2, desktopGeometry.y( ), desktopGeometry.width( ) / 2, desktopGeometry.height( ) );
				screenOnLowerSide = false;
			}
			else{

				if( mousePos.x( ) >= desktopGeometry.width( ) / 2 ){

					this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ), desktopGeometry.width( ) / 2, desktopGeometry.height( ) );
					screenOnLowerSide   =	true;
				}
			}
			break;
		}

		case ParameterVerhalten::VERTIKAL : {

			if( mousePos.y( ) < desktopGeometry.height( ) / 2 ){

				this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ) + desktopGeometry.height( ) / 2, desktopGeometry.width( ), desktopGeometry.height( ) / 2 );
				screenOnLowerSide = false;
			}
			else{

				if( mousePos.y( ) >= desktopGeometry.height( ) / 2 ){

					this->setGeometry( desktopGeometry.x( ), desktopGeometry.y( ), desktopGeometry.width( ), desktopGeometry.height( ) / 2 );
					screenOnLowerSide = true;
				}
			}
			break;
		}

		default :
			break;
	}
}

void
GLView::slotTimerEvent( ){

	if( parameterVerhalten.zustand == ParameterVerhalten::AUS ) {

		return;
	}

	controlWindowsBehaviour( );

	switch( parameterVerhalten.zustand ) {

		case ParameterVerhalten::AUS : {

			return;
		}

		case ParameterVerhalten::HORIZONTAL : {

			parameterSimulation.mausX = 1.0 * ( mousePos.x( ) - screenOnLowerSide * desktopGeometry.width( ) / 2 ) / this->width( ),
			parameterSimulation.mausY = 1.0 * mousePos.y( ) / this->height( );

			break;
		}

		case ParameterVerhalten::VERTIKAL : {

			parameterSimulation.mausX = 1.0 * mousePos.x( ) / this->width( ),
			parameterSimulation.mausY = 1.0 * ( mousePos.y( ) - screenOnLowerSide * desktopGeometry.height( ) / 2 ) / this->height( );

			break;
		}
	}

	grabScreen( );

	updateGL( );
}
