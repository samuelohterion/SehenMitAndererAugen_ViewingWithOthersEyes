#ifndef PARAMETERVERHALTEN_H
#define PARAMETERVERHALTEN_H

#include <QObject>

class
ParameterVerhalten :
public QObject {

		Q_OBJECT

	public:

		enum
		Zustand {

			AUS,
			HORIZONTAL,
			VERTIKAL
		}
		zustand;

	public:

		explicit
		ParameterVerhalten( const Zustand & p_zustand = AUS, QObject * parent = 0 );

	signals:

		void
		signalAenderungZustand( Zustand const & p_zustand );

	public slots:

		void
		slotSetzeZustand( Zustand const & p_zustand );
};

#endif // PARAMETERVERHALTEN_H
