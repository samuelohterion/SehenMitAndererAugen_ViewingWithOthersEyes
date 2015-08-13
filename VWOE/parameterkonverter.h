#ifndef PARAMETERKONVERTER_H
#define PARAMETERKONVERTER_H

#include <QObject>
#include "parameterfehlsichtigkeit.h"
#include "parametersimulation.h"
#include "parameterverhalten.h"
#include "matrix3x3model.h"
#include <QMatrix3x3>
#include <QVector3D>

class
ParameterKonverter :
public QObject {

		Q_OBJECT

	public:

		explicit
		ParameterKonverter( ParameterVerhalten * p_parameterVerhalten = 0, ParameterFehlsichtigkeit * p_parameterFehlsichtigkeit = 0, ParameterSimulation * p_parameterSimulation = 0,	QObject * parent = 0 );

	public:

		ParameterVerhalten *
		parameterVerhaltenAdresse;

		ParameterFehlsichtigkeit *
		parameterFehlsichtigkeitAdresse;

		ParameterSimulation *
		parameterSimulationAdresse;

		Matrix3x3Model
		matrix3x3Model;

	private:

		void
		kombiniereFarbfehlsichtigkeitMitLinseneintruebung( );

	public:

//		void
//		setzeParameterAdressen( ParameterVerhalten * p_parameterVerhaltenAdresse, ParameterFehlsichtigkeit * p_parameterFehlsichtigkeitAdresse, ParameterSimulation * p_parameterSimulation );

	signals:

		void
		signalAenderungVerhaltenZustand( ParameterVerhalten::Zustand );

/*
		void
		signalAenderungFarbfehlsichtigkeitTypAufKeine( );

		void
		signalAenderungFarbfehlsichtigkeitTypAufProtanopie( );

		void
		signalAenderungFarbfehlsichtigkeitTypAufDeuteranopie( );

		void
		signalAenderungFarbfehlsichtigkeitTypAufTritanopie( );

		void
		signalAenderungFarbfehlsichtigkeitTypAufAchromatopsie( );

		void
		signalAenderungFarbfehlsichtigkeitTypAufNutzerdefiniert( );

		void
		signalAenderungFarbfehlsichtigkeitTypAuf( ParameterFehlsichtigkeit::FarbfehlsichtigkeitTyp p_farbfehlsichtigkeitTyp );

*/
		void
		signalAenderungFarbfehlsichtigkeitMatrixAuf( QMatrix3x3 p_matrix );

/*
		void
		signalAenderungFarbfehlsichtigkeitAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		signalAenderungVerzerrungAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		signalAenderungVerzerrungRadiusAuf( int p_verzerrungRadiusInProzent );

		void
		signalAenderungVerzerrungModellAuf( int p_verzerrungModellTyp );

		void
		signalAenderungSehschaerfeAuf( int p_sehschaerfeInJahren );

		void
		signalAenderungKontrastempfindlichkeitAuf( int p_kontrastempfindlichkeitInJahren );

		void
		signalAenderungLinseneintruebungAuf( int p_linseneintruebungInJahren );

		void
		signalAenderungGesichtsfeldausfaelleAuf( int p_gesichtsfeldausfaelleInStufen );
*/
	public slots:

		void
		slotInit( );

		void
		slotSetzeVerhaltenTypAufAUS( );

		void
		slotSetzeVerhaltenTypAufHORIZONTAL( );

		void
		slotSetzeVerhaltenTypAufVERTIKAL( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufKeine( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufProtanopie( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufDeuteranopie( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufTritanopie( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufAchromatopsie( );

		void
		slotSetzeFarbfehlsichtigkeitTypAufNutzerdefiniert( );

		void
		slotSetzeFarbfehlsichtigkeitAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		slotSetzeVerzerrungAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		slotSetzeVerzerrungRadiusAuf( int p_verzerrungRadiusInProzent );

		void
		slotSetzeVerzerrungModellTypAufGAUSS( );

		void
		slotSetzeVerzerrungModellTypAufKUGEL( );

		void
		slotSetzeSehschaerfeAuf( int p_sehschaerfeInJahren );

		void
		slotSetzeKontrastempfindlichkeitAuf( int p_kontrastempfindlichkeitInJahren );

		void
		slotSetzeLinseneintruebungAuf( int p_linseneintruebungInJahren );

		void
		slotSetzeGesichtsfeldausfaelleStufeAuf( int p_gesichtsfeldausfaelleInStufen );

		void
		slotSetzeGesichtsfeldausfaelleGroesseAuf( int p_gesichtsfeldausfaelleGroesseInProzent );

		void
		slotSetzeFarbfehlsichtigkeitMatrixAuf( QMatrix3x3 p_matri3x3 );
};

class	FarbfehlsichtigkeitMatrices {

	public:

		static float const
		datas[ 11 * 3 * 3 * 3 + 3 * 3 ];

	public:

		FarbfehlsichtigkeitMatrices( ) {

		}

		~FarbfehlsichtigkeitMatrices( ) {

		}

	public:

		static QMatrix3x3
		getMat3x3( ParameterFehlsichtigkeit::FarbfehlsichtigkeitTyp const & p_ffs, float p_level ) {

			if(	p_ffs == ParameterFehlsichtigkeit::KEINE ) {

				return QMatrix3x3( datas );
			}

			p_level = p_level < 0. ? 0. : 1. < p_level ? 1. : p_level;

			int
			id = p_level * 10;

			if(	ParameterFehlsichtigkeit::PROTANOPIE <= p_ffs && p_ffs <= ParameterFehlsichtigkeit::TRITANOPIE ) {

				float
				off = ( 10 * p_level - id );

				QMatrix3x3
				mat1( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + id * ( 3 * 3 ) ),
				mat2( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + ( id + 1 ) * ( 3 * 3 ) );

				return	QMatrix3x3( mat1 + ( mat2 - mat1 ) * off );
			}

			if(	p_ffs == ParameterFehlsichtigkeit::ACHROMATOPSIE ) {

				QMatrix3x3
				mat1( datas + 3 * ( 3 * 3 * 11 ) ),
				eye( datas );

				return eye * ( 1.f - p_level ) + mat1 * p_level;
			}

			return QMatrix3x3( datas );
		}

		static QMatrix3x3
		getMat3x3( ParameterFehlsichtigkeit::FarbfehlsichtigkeitTyp const & p_ffs, int p_amplitudeInProzent ) {

			if(	p_ffs == ParameterFehlsichtigkeit::KEINE ) {

				return QMatrix3x3( datas );
			}

			p_amplitudeInProzent = p_amplitudeInProzent < 0 ? 0 : 100 < p_amplitudeInProzent ? 100 : p_amplitudeInProzent;

			int
			id = p_amplitudeInProzent / 10;

			if(	ParameterFehlsichtigkeit::PROTANOPIE <= p_ffs && p_ffs <= ParameterFehlsichtigkeit::TRITANOPIE ) {

				float
				off = 0.01 * ( p_amplitudeInProzent - 10 * id );

				QMatrix3x3
				mat1( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + id * ( 3 * 3 ) ),
				mat2( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + ( id + 1 ) * ( 3 * 3 ) );

				return	QMatrix3x3( mat1 + ( mat2 - mat1 ) * off );
			}

			if(	p_ffs == ParameterFehlsichtigkeit::ACHROMATOPSIE ) {

				QMatrix3x3
				mat1( datas + 3 * ( 3 * 3 * 11 ) ),
				eye( datas );

				return eye * ( 1.f - 0.01f * p_amplitudeInProzent ) + mat1 * ( 0.01f * p_amplitudeInProzent );
			}

			return QMatrix3x3( datas );
		}
};


#endif // PARAMETERKONVERTER_H
