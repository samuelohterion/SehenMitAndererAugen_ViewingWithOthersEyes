#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T11:52:28
#
#-------------------------------------------------

QT       += core gui opengl 3d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VWOE
TEMPLATE = app

SOURCES +=	main.cpp \
			glview.cpp \
			mainwindow.cpp \
			matrix3x3model.cpp \
			matrix3x3viewctrlwdgt.cpp \
			parameterverhalten.cpp \
			parameterfehlsichtigkeit.cpp \
			parameterkonverter.cpp \
			parametersimulation.cpp

HEADERS  +=	glview.h \
			mainwindow.h \
			matrix3x3model.h \
			matrix3x3viewctrlwdgt.h \
			parameterverhalten.h \
			parameterfehlsichtigkeit.h \
			parameterkonverter.h \
			parametersimulation.h

FORMS    += glview.ui \
			mainwindow.ui \
			matrix3x3viewctrlwdgt.ui

OTHER_FILES	+=	\
	shaders/Second.vert \
	shaders/Second.frag \
	shaders/First.vert \
	shaders/First.frag

#LIBS += libqt3d
