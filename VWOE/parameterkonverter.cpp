#include <math.h>
#include "parameterkonverter.h"

ParameterKonverter::ParameterKonverter( ParameterVerhalten * p_parameterVerhaltenAdresse, ParameterFehlsichtigkeit * p_parameterFehlsichtigkeitAdresse, ParameterSimulation * p_parameterSimulationAdresse, QObject * parent ) :
QObject( parent ),
parameterVerhaltenAdresse( p_parameterVerhaltenAdresse ),
parameterFehlsichtigkeitAdresse( p_parameterFehlsichtigkeitAdresse ),
parameterSimulationAdresse( p_parameterSimulationAdresse ),
matrix3x3Model( &parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitMatrix ) {

}


void
ParameterKonverter::kombiniereFarbfehlsichtigkeitMitLinseneintruebung( ) {

	float const
	factors[ 10 * 3 ] = {

		1.0,	1.0,	1.0,
		0.998,	0.988,	0.924,
		0.994,	0.969,	0.811,
		0.989,	0.942,	0.674,
		0.982,	0.909,	0.533,
		0.974,	0.870,	0.399,
		0.964,	0.827,	0.284,
		0.953,	0.779,	0.191,
		0.941,	0.728,	0.122,
		0.,		0.,		0.			//just for preventing of index range overflow
	};

	int
	id = parameterFehlsichtigkeitAdresse->linseneintruebungInJahren / 10;

	float
	off = 0.1 * ( parameterFehlsichtigkeitAdresse->linseneintruebungInJahren - 10 * id );

	--id;

	QVector3D
	vec1( factors[ id * 3 + 0 ], factors[ id * 3 + 1 ], factors[ id * 3 + 2 ] ),
	vec2( factors[ id * 3 + 3 ], factors[ id * 3 + 4 ], factors[ id * 3 + 5 ] );

	QVector3D
	v( vec1 + ( vec2 - vec1 ) * off );

	for( int row = 0; row < 3; ++row ) {

		for( int col = 0; col < 3; ++col ) {

			parameterSimulationAdresse->matrixRGB( row, col ) = parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitMatrix( row, col ) * v[ row ];
		}
	}
}

void
ParameterKonverter::slotInit( ) {

	if( !parameterFehlsichtigkeitAdresse || !parameterSimulationAdresse ) {

		return;
	}

//	parameterVerhaltenAdresse->zustand = ParameterVerhalten::AUS;
//	parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp = ParameterFehlsichtigkeit::KEINE;
//	parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent = 0;
//	parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitMatrix.setToIdentity( );
//	parameterFehlsichtigkeitAdresse->verzerrungModellTyp = ParameterFehlsichtigkeit::GAUSS;
//	parameterFehlsichtigkeitAdresse->verzerrungAmplitudeInProzent = 0;
//	parameterFehlsichtigkeitAdresse->verzerrungRadiusInProzent = 0;
//	parameterFehlsichtigkeitAdresse->sehschaerfeInJahren = 10;
	parameterFehlsichtigkeitAdresse->linseneintruebungInJahren = 10;
//	parameterFehlsichtigkeitAdresse->kontrastempfindlichkeitInJahren = 20;
//	parameterFehlsichtigkeitAdresse->gesichtsfeldausfaelleInStufen = 0;
//	parameterFehlsichtigkeitAdresse->gesichtsfeldausfaelleInverseGroesseInProzent = 0;

	slotSetzeVerhaltenTypAufAUS( );
	slotSetzeFarbfehlsichtigkeitTypAufKeine( );
	slotSetzeFarbfehlsichtigkeitAmplitudeAuf( 0 );
	slotSetzeVerzerrungRadiusAuf( 0 );
	slotSetzeVerzerrungAmplitudeAuf( 0 );
	slotSetzeVerzerrungModellTypAufGAUSS( );
	slotSetzeSehschaerfeAuf( 10 );
	slotSetzeKontrastempfindlichkeitAuf( 20 );
	slotSetzeLinseneintruebungAuf( 10 );
	slotSetzeGesichtsfeldausfaelleStufeAuf( 0 );
	slotSetzeGesichtsfeldausfaelleGroesseAuf( 50 );
}

void
ParameterKonverter::slotSetzeVerhaltenTypAufAUS( ) {

	parameterVerhaltenAdresse->zustand = ParameterVerhalten::AUS;
}

void
ParameterKonverter::slotSetzeVerhaltenTypAufHORIZONTAL( ) {

	parameterVerhaltenAdresse->zustand = ParameterVerhalten::HORIZONTAL;
}

void
ParameterKonverter::slotSetzeVerhaltenTypAufVERTIKAL( ) {

	parameterVerhaltenAdresse->zustand = ParameterVerhalten::VERTIKAL;
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufKeine( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::KEINE );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufProtanopie( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::PROTANOPIE );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufDeuteranopie( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::DEUTERANOPIE );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufTritanopie( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::TRITANOPIE );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufAchromatopsie( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::ACHROMATOPSIE );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitTypAufNutzerdefiniert( ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::NUTZERDEFINIERT );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitMatrixAuf( QMatrix3x3 p_farbfehlsichtigkeitMatrix ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::NUTZERDEFINIERT );
	matrix3x3Model.slotWriteMatrix( p_farbfehlsichtigkeitMatrix );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeFarbfehlsichtigkeitAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent ) {

	parameterFehlsichtigkeitAdresse->setzeFarbfehlsichtigkeitAmplitudeAuf( p_farbfehlsichtigkeitAmplitudeInProzent );
	matrix3x3Model.slotWriteMatrix( FarbfehlsichtigkeitMatrices::getMat3x3( parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitTyp, parameterFehlsichtigkeitAdresse->farbfehlsichtigkeitAmplitudeInProzent ) );
	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeVerzerrungAmplitudeAuf( int p_verzerrungAmplitudeInProzent ) {

	parameterFehlsichtigkeitAdresse->setzeVerzerrungAmplitudeAuf( p_verzerrungAmplitudeInProzent );
	parameterSimulationAdresse->verzerrungAmplitude = 0.01 * parameterFehlsichtigkeitAdresse->verzerrungAmplitudeInProzent;
}

void
ParameterKonverter::slotSetzeVerzerrungRadiusAuf( int p_verzerrungRadiusInProzent ) {

	parameterFehlsichtigkeitAdresse->setzeVerzerrungRadiusAuf( p_verzerrungRadiusInProzent );
	parameterSimulationAdresse->verzerrungRadius = 0.01 * parameterFehlsichtigkeitAdresse->verzerrungRadiusInProzent;
	parameterSimulationAdresse->verzerrungRadius *= parameterSimulationAdresse->verzerrungRadius;
}

void
ParameterKonverter::slotSetzeVerzerrungModellTypAufGAUSS( ) {

	parameterFehlsichtigkeitAdresse->setzeVerzerrungModellTypAuf( ParameterFehlsichtigkeit::GAUSS );
	parameterSimulationAdresse->verzerrungModellTyp = ParameterFehlsichtigkeit::GAUSS;
}

void
ParameterKonverter::slotSetzeVerzerrungModellTypAufKUGEL( ) {

	parameterFehlsichtigkeitAdresse->setzeVerzerrungModellTypAuf( ParameterFehlsichtigkeit::KUGEL );
	parameterSimulationAdresse->verzerrungModellTyp = ParameterFehlsichtigkeit::KUGEL;
}

void
ParameterKonverter::slotSetzeSehschaerfeAuf( int p_sehschaerfeInJahren ) {

	parameterFehlsichtigkeitAdresse->setzeSehschaerfeAuf( p_sehschaerfeInJahren );

	float
	sigma = ( p_sehschaerfeInJahren - 9 ) / 25.;

	float
	sigmaInv = 1. / sigma,
	factor = sigmaInv * sigmaInv / 2.,
	sum = sigmaInv / sqrt( 2 * M_PI );

	for(	int i = 1; i < 10; ++i ) {

		float
		e_ = sigmaInv / sqrt( 2 * M_PI ) * exp( -factor * i * i );

		sum += ( 2 * e_ );
	}

	sigmaInv /= sum;

	for(	int i = 0; i < 10; ++i ) {

		float
		e_ = sigmaInv / sqrt( 2 * M_PI ) * exp( -factor * i * i );

		parameterSimulationAdresse->gauss[ i ] = e_;
	}
}

void
ParameterKonverter::slotSetzeKontrastempfindlichkeitAuf( int p_kontrastempfindlichkeitInJahren ) {

	if( p_kontrastempfindlichkeitInJahren < 10 ) {

		p_kontrastempfindlichkeitInJahren = 10;
	}
	else if( 90 < p_kontrastempfindlichkeitInJahren ){

		p_kontrastempfindlichkeitInJahren = 90;
	}

	parameterFehlsichtigkeitAdresse->setzeKontrastempfindlichkeitAuf( p_kontrastempfindlichkeitInJahren );

	float
	kontrast[ ] = {

		0.93, 1.0, 1.0, 0.93, 0.80, 0.67, 0.47, 0.27, 0.13, 0.
	};

	int
	id = p_kontrastempfindlichkeitInJahren / 10;

	float
	off = 0.1 * ( p_kontrastempfindlichkeitInJahren - 10 * id );

	--id;

	float
	k1 = kontrast[ id ],
	k2 = kontrast[ id + 1 ],
	k = k1 + ( k2 - k1 ) * off;


	parameterSimulationAdresse->kontrast = k;
}

void
ParameterKonverter::slotSetzeLinseneintruebungAuf( int p_linseneintruebungInJahren ) {

	if( p_linseneintruebungInJahren < 10 ) {

		p_linseneintruebungInJahren = 10;
	}
	else if( 90 < p_linseneintruebungInJahren ){

		p_linseneintruebungInJahren = 90;
	}

	parameterFehlsichtigkeitAdresse->setzeLinseneintruebungAuf( p_linseneintruebungInJahren );

	kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );
}

void
ParameterKonverter::slotSetzeGesichtsfeldausfaelleStufeAuf( int p_gesichtsfeldausfaelleInStufen ) {

	p_gesichtsfeldausfaelleInStufen = p_gesichtsfeldausfaelleInStufen < 0 ? 0 : 5 < p_gesichtsfeldausfaelleInStufen ? 5 : p_gesichtsfeldausfaelleInStufen;
	parameterFehlsichtigkeitAdresse->setzeGesichtsfeldausfaelleStufeAuf( p_gesichtsfeldausfaelleInStufen );
	parameterSimulationAdresse->gesichtsfeldausfaelleInStufen = parameterFehlsichtigkeitAdresse->gesichtsfeldausfaelleInStufen;
}

void
ParameterKonverter::slotSetzeGesichtsfeldausfaelleGroesseAuf( int p_gesichtsfeldausfaelleGroesseInProzent ) {

	parameterFehlsichtigkeitAdresse->setzeGesichtsfeldausfaelleGroesseAuf( p_gesichtsfeldausfaelleGroesseInProzent );
	parameterSimulationAdresse->gesichtsfeldausfaelleGroesse = 0.09 * sqrt( parameterFehlsichtigkeitAdresse->gesichtsfeldausfaelleInverseGroesseInProzent );
}

float const
FarbfehlsichtigkeitMatrices::datas[ 11 * 3 * 3 * 3 + 3 * 3 ] = {

//protanopie

//grad 0.0

	1., 0., 0.,
	0., 1., 0.,
	0., 0., 1.,

//grad 0.1

	+0.856167,	+0.182038,	-0.038205,
	+0.029342,	+0.955115,	+0.015544,
	-0.002880,	-0.001563,	+1.004443,

//grad 0.2

	+0.734766,	+0.334872,	-0.069637,
	+0.051840,	+0.919198,	+0.028963,
	-0.004928,	-0.004209,	+1.009137,

//grad 0.3

	+0.630323,	+0.465641,	-0.095964,
	+0.069181,	+0.890046,	+0.040773,
	-0.006308,	-0.007724,	+1.014032,

//grad 0.4

	+0.539009,	+0.579343,	-0.118352,
	+0.082546,	+0.866121,	+0.051332,
	-0.007136,	-0.011959,	+1.019095,

//grad 0.5

	+0.458064,	+0.679578,	-0.137642,
	+0.092785,	+0.846313,	+0.060902,
	-0.007494,	-0.016807,	+1.024301,

//grad 0.6

	+0.385450,	+0.769005,	-0.154455,
	+0.100526,	+0.829802,	+0.069673,
	-0.007442,	-0.022190,	+1.029632,

//grad 0.7

	+0.319627,	+0.849633,	-0.169261,
	+0.106241,	+0.815969,	+0.077790,
	-0.007025,	-0.028051,	+1.035076,

//grad 0.8

	+0.259411,	+0.923008,	-0.182420,
	+0.110296,	+0.804340,	+0.085364,
	-0.006276,	-0.034346,	+1.040622,

//grad 0.9

	+0.203876,	+0.990338,	-0.194214,
	+0.112975,	+0.794542,	+0.092483,
	-0.005222,	-0.041043,	+1.046265,

//grad 1.0

	+0.152286,	+1.052583,	-0.204868,
	+0.114503,	+0.786281,	+0.099216,
	-0.003882,	-0.048116,	+1.051998,

//deuteranopie

//grad 0.0

	1., 0., 0.,
	0., 1., 0.,
	0., 0., 1.,

//grad 0.1

	+0.866435,	+0.177704,	-0.044139,
	+0.049567,	+0.939063,	+0.011370,
	-0.003453,	+0.007233,	+0.996220,

//grad 0.2

	+0.760729,	+0.319078,	-0.079807,
	+0.090568,	+0.889315,	+0.020117,
	-0.006027,	+0.013325,	+0.992702,

//grad 0.3

	+0.675425,	+0.433850,	-0.109275,
	+0.125303,	+0.847755,	+0.026942,
	-0.007950,	+0.018572,	+0.989378,

//grad 0.4

	+0.605511,	+0.528560,	-0.134071,
	+0.155318,	+0.812366,	+0.032316,
	-0.009376,	+0.023176,	+0.986200,

//grad 0.5

	+0.547494,	+0.607765,	-0.155259,
	+0.181692,	+0.781742,	+0.036566,
	-0.010410,	+0.027275,	+0.983136,

//grad 0.6

	+0.498864,	+0.674741,	-0.173604,
	+0.205199,	+0.754872,	+0.039929,
	-0.011131,	+0.030969,	+0.980162,

//grad 0.7

	+0.457771,	+0.731899,	-0.189670,
	+0.226409,	+0.731012,	+0.042579,
	-0.011595,	+0.034333,	+0.977261,

//grad 0.8

	+0.422823,	+0.781057,	-0.203881,
	+0.245752,	+0.709602,	+0.044646,
	-0.011843,	+0.037423,	+0.974421,

//grad 0.9

	+0.392952,	+0.823610,	-0.216562,
	+0.263559,	+0.690210,	+0.046232,
	-0.011910,	+0.040281,	+0.971630,

//grad 1.0

	+0.367322,	+0.860646,	-0.227968,
	+0.280085,	+0.672501,	+0.047413,
	-0.011820,	+0.042940,	+0.968881,

//tritanopie

//grad 0.0

	1., 0., 0.,
	0., 1., 0.,
	0., 0., 1.,

//grad 0.1

	+0.926670,	+0.092514,	-0.019184,
	+0.021191,	+0.964503,	+0.014306,
	+0.008437,	+0.054813,	+0.936750,

//grad 0.2

	+0.895720,	+0.133330,	-0.029050,
	+0.029997,	+0.945400,	+0.024603,
	+0.013027,	+0.104707,	+0.882266,

//grad 0.3

	+0.905871,	+0.127791,	-0.033662,
	+0.026856,	+0.941251,	+0.031893,
	+0.013410,	+0.148296,	+0.838294,

//grad 0.4

	+0.948035,	+0.089490,	-0.037526,
	+0.014364,	+0.946792,	+0.038844,
	+0.010853,	+0.193991,	+0.795156,

//grad 0.5

	+1.017277,	+0.027029,	-0.044306,
	-0.006113,	+0.958479,	+0.047634,
	+0.006379,	+0.248708,	+0.744913,

//grad 0.6

	+1.104996,	-0.046633,	-0.058363,
	-0.032137,	+0.971635,	+0.060503,
	+0.001336,	+0.317922,	+0.680742,

//grad 0.7

	+1.193214,	-0.109812,	-0.083402,
	-0.058496,	+0.979410,	+0.079086,
	-0.002346,	+0.403492,	+0.598854,

//grad 0.8

	+1.257728,	-0.139648,	-0.118081,
	-0.078003,	+0.975409,	+0.102594,
	-0.003316,	+0.501214,	+0.502102,

//grad 0.9

	+1.278864,	-0.125333,	-0.153531,
	-0.084748,	+0.957674,	0.127074,
	-0.000989,	+0.601151,	0.399838,

//grad 1.0

	+1.255528,	-0.076749,	-0.178779,
	-0.078411,	+0.930809,	+0.147602,
	+0.004733,	+0.691367,	+0.303900,

// achromatopsie

	+0.212656,	+0.715158,	+0.072186,
	+0.212656,	+0.715158,	+0.072186,
	+0.212656,	+0.715158,	+0.072186
};
