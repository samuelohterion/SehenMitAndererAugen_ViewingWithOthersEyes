#include "parameterfehlsichtigkeit.h"

ParameterFehlsichtigkeit::ParameterFehlsichtigkeit( QObject * parent ) :
QObject( parent ) {

}

void
ParameterFehlsichtigkeit::setzeFarbfehlsichtigkeitTypAuf( FarbfehlsichtigkeitTyp p_farbfehlsichtigkeitTyp ) {

	farbfehlsichtigkeitTyp = p_farbfehlsichtigkeitTyp;
}

void
ParameterFehlsichtigkeit::setzeFarbfehlsichtigkeitAmplitudeAuf( int p_farbfehlsichtigkeitAmplitudeInProzent ) {

	farbfehlsichtigkeitAmplitudeInProzent = p_farbfehlsichtigkeitAmplitudeInProzent;
}

void
ParameterFehlsichtigkeit::setzeVerzerrungAmplitudeAuf( int p_verzerrungAmplitudeInProzent ) {

	verzerrungAmplitudeInProzent = p_verzerrungAmplitudeInProzent;
}

void
ParameterFehlsichtigkeit::setzeVerzerrungRadiusAuf( int p_verzerrungRadiusInProzent ) {

	verzerrungRadiusInProzent = p_verzerrungRadiusInProzent;
}

void
ParameterFehlsichtigkeit::setzeVerzerrungModellTypAuf( VerzerrungModellTyp p_verzerrungModellTyp ) {

	verzerrungModellTyp = p_verzerrungModellTyp;
}

void
ParameterFehlsichtigkeit::setzeSehschaerfeAuf( int p_sehschaerfeInJahren ) {

	sehschaerfeInJahren = p_sehschaerfeInJahren;
}

void
ParameterFehlsichtigkeit::setzeKontrastempfindlichkeitAuf( int p_kontrastempfindlichkeitInJahren ) {

	kontrastempfindlichkeitInJahren = p_kontrastempfindlichkeitInJahren;
}

void
ParameterFehlsichtigkeit::setzeLinseneintruebungAuf( int p_linseneintruebungInJahren ) {

	linseneintruebungInJahren = p_linseneintruebungInJahren;
}

void
ParameterFehlsichtigkeit::setzeGesichtsfeldausfaelleStufeAuf( int p_gesichtsfeldausfaelleInStufen ) {

	gesichtsfeldausfaelleInStufen = p_gesichtsfeldausfaelleInStufen;
}

void
ParameterFehlsichtigkeit::setzeGesichtsfeldausfaelleGroesseAuf( int p_gesichtsfeldausfaelleGroesseInProzent ) {

	gesichtsfeldausfaelleInverseGroesseInProzent = p_gesichtsfeldausfaelleGroesseInProzent;
}

void
ParameterFehlsichtigkeit::setzeFarbfehlsichtigkeitMatrixAuf( QMatrix3x3 const & p_matri3x3 ) {

	farbfehlsichtigkeitMatrix = p_matri3x3;
}

