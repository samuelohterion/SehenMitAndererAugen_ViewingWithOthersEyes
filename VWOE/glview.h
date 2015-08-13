#ifndef	GLVIEW_H
#define	GLVIEW_H

#include	<QGuiApplication>
#include	<QDesktopWidget>
#include	<QFileInfo>
#include	<QOpenGLFramebufferObject>
#include	<QOpenGLTexture>
#include	<QOpenGLShader>
#include	<QGLWidget>
#include	<QImage>
#include	<QMouseEvent>
#include	<QPixmap>
#include	<QScreen>
#include	<QTimer>
#include	<iostream>
//#include	"properties.hpp"
//#include	"necessary_matrices.h"
#include	"parametersimulation.h"
#include	"parameterverhalten.h"

namespace	Ui{

	class GLView;
}

class	GLView:
public	QGLWidget{

		Q_OBJECT

	public:

		explicit
		GLView(	QString const & p_shadersPath = "./shaders/", QString const & p_picturesPath = "./pix/", QWidget	*p_parent = 0 );

		~GLView( );

	private:

		Ui::GLView *
		ui;

		int
		aktuellesGlaukom;

	public:

		QString
		shadersPath,
		picturesPath;

		ParameterSimulation
		parameterSimulation;

		ParameterVerhalten
		parameterVerhalten;

		QTimer
		timer;

//		GLuint
//		texture;

		QImage
		screenShotImage;

		QOpenGLFramebufferObject
		* fboRender;

		QOpenGLTexture
//		* textureScreenGrab,
		* textureGesichtsfeld;

		QOpenGLShaderProgram
		* shaderProgram1,
		* shaderProgram2;

		bool
		screenOnLowerSide;

		QRect
		desktopGeometry;

		QPoint
		mousePos;

	protected:

		void
		initializeGL( );

		void
		paintGL( );

		void
		resizeGL( int p_width, int p_height );

	public:
		void
		createShaders( );

		void
		grabScreen( );

		QOpenGLShaderProgram *
		erstelleShaderProgramAusDateien( QString const & p_filenameVertexShader, QString const & p_filenameFragmentShader );

		void
		controlWindowsBehaviour( );

	public:

//        void
//        closeEvent(	QCloseEvent	*p_CloseEvent );

	public slots:

		void
		slotErneuereFensterGeometrie( );

		void
		slotTimerEvent( );
};

#endif // GLVIEW_H
