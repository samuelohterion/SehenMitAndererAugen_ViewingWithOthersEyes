#include "parameterverhalten.h"

ParameterVerhalten::ParameterVerhalten( Zustand const & p_zustand, QObject * parent ) :
QObject( parent ),
zustand( p_zustand ) {

}

void
ParameterVerhalten::slotSetzeZustand( Zustand const & p_zustand ) {

	zustand	=	p_zustand;
	emit signalAenderungZustand( zustand );
}
