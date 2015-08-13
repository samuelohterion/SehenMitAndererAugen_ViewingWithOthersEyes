#ifndef PARAMETERFEHLSICHTIGKEIT_H
#define PARAMETERFEHLSICHTIGKEIT_H

#include <QMatrix3x3>

class
ParameterFehlsichtigkeit :
public QObject {

		Q_OBJECT

	public:

		explicit
		ParameterFehlsichtigkeit( QObject * parent = 0 );

	public:

		enum
		FarbfehlsichtigkeitTyp {

			KEINE,
			PROTANOPIE,
			DEUTERANOPIE,
			TRITANOPIE,
			ACHROMATOPSIE,
			NUTZERDEFINIERT
		};

		enum
		VerzerrungModellTyp {

			KEINS,
			GAUSS,
			KUGEL
		};

	public:

		FarbfehlsichtigkeitTyp
		farbfehlsichtigkeitTyp;

		VerzerrungModellTyp
		verzerrungModellTyp;

		int
		farbfehlsichtigkeitAmplitudeInProzent,
		verzerrungRadiusInProzent,
		verzerrungAmplitudeInProzent,
		sehschaerfeInJahren,
		kontrastempfindlichkeitInJahren,
		linseneintruebungInJahren,
		gesichtsfeldausfaelleInStufen,
		gesichtsfeldausfaelleInverseGroesseInProzent;

		QMatrix3x3
		farbfehlsichtigkeitMatrix;

//		QVector3D
//		vektorLinseneintruebung;


	public:

		void
		setzeFarbfehlsichtigkeitTypAuf( FarbfehlsichtigkeitTyp p_farbfehlsichtigkeitTyp );

		void
		setzeFarbfehlsichtigkeitAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		setzeVerzerrungAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent );

		void
		setzeVerzerrungRadiusAuf( int p_verzerrungRadiusInProzent );

		void
		setzeVerzerrungModellTypAuf( VerzerrungModellTyp p_verzerrungModellTyp );

		void
		setzeSehschaerfeAuf( int p_sehschaerfeInJahren );

		void
		setzeKontrastempfindlichkeitAuf( int p_kontrastempfindlichkeitInJahren );

		void
		setzeLinseneintruebungAuf( int p_linseneintruebungInJahren );

		void
		setzeGesichtsfeldausfaelleStufeAuf( int p_gesichtsfeldausfaelleInStufen );

		void
		setzeGesichtsfeldausfaelleGroesseAuf( int p_gesichtsfeldausfaelleGroesseInProzent );

		void
		setzeFarbfehlsichtigkeitMatrixAuf( QMatrix3x3 const & p_matri3x3 );
};

#endif // PARAMETERFEHLSICHTIGKEIT_H
