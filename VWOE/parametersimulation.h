#ifndef PARAMETERSIMULATION_H
#define PARAMETERSIMULATION_H

#include <QObject>
#include "parameterfehlsichtigkeit.h"
#include "QVector3D"
#include "QMatrix3x3"

class
ParameterSimulation {

	public:

		explicit
		ParameterSimulation( );

	public:

		float
		mausX,
		mausY,
		fensterbreite,
		fensterhoehe,
		inverseFensterbreite,
		inverseFensterhoehe,
		radiusInX;

		int
		gesichtsfeldausfaelleInStufen;

		ParameterFehlsichtigkeit::VerzerrungModellTyp
		verzerrungModellTyp;

		float
		verzerrungRadius,
		verzerrungAmplitude;

		QMatrix3x3
		matrixRGB;

		float
		kontrast,
		gesichtsfeldausfaelleGroesse;

		float
		gauss[ 10 ];
};

#endif // SIMULATIONSPARAMETER_H
