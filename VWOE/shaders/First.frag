#version 120

uniform sampler2D
texture_,
texture_glaucom_;

uniform float
mouseX,
mouseY,
width,
height,
invWidth,
invHeight,
radiusInX,
verzerrungRadius,
verzerrungAmplitude,
kontrast,
gesichtsfeldausfaelleGroesse;

uniform int
verzerrungModell;  // 0= keins 1=gauss 2=ball

uniform mat3
farbfehlsichtigkeitsMatrix;

uniform vec3
helligkeit;

const int
halbeKernelBreite = 9;

uniform float
gaussGewicht[ halbeKernelBreite + 1 ];		// 0 1 2 ... 8 9     das macht eine Kernelgroesse von 19 x 19

void
main( ){

	float
	verzerrungRadiusQuadrat = verzerrungRadius * verzerrungRadius;

	vec2
	pixelPos_	=	gl_TexCoord[ 0 ].st,
	mousePos_	=	vec2( mouseX,	mouseY ),
	grad_		=	vec2( width, height ) / radiusInX,
	gradInv_	=	vec2( invWidth, invHeight ) * radiusInX,
	relPos_		=	( pixelPos_ - mousePos_ ) * grad_;


	float
	distSqr_	=	dot(	relPos_, relPos_ );

	if( verzerrungModell == 1  ) {

		relPos_	*=	( 1.0 - verzerrungAmplitude * exp( -distSqr_ / ( .5 * 4.0 * verzerrungRadiusQuadrat ) ) );
	}
	else {

		verzerrungRadiusQuadrat *= 4.;

		float
		vA_ = ( 0.999 - verzerrungAmplitude ),
		vA2_ = vA_ * vA_,
		vR2_ = verzerrungRadiusQuadrat / ( 1. - vA2_ ),
		vR_ = sqrt( vR2_ );

		float
		verzerrungRadius_ = sqrt( verzerrungRadiusQuadrat );

		if( distSqr_ < verzerrungRadiusQuadrat  ) {

			float
			s = sqrt( distSqr_ / vR2_ );

			relPos_ *= 1 + ( vR_ * vA_ - sqrt( vR2_ - distSqr_ ) ) * tan( asin( s ) - asin( .5 * s ) ) / sqrt( distSqr_ );
		}
	}

	relPos_	*=	gradInv_;

	vec3
	col = texture2D( texture_, relPos_ + mousePos_ ).rgb * gaussGewicht[ 0 ];

	vec2
	dv = vec2( 0. );

	for( int i = 1; i < halbeKernelBreite; ++i ) {

		dv.x += invWidth;

		col +=	(

			texture2D( texture_, relPos_ + mousePos_ - dv ).rgb +
			texture2D( texture_, relPos_ + mousePos_ + dv ).rgb
//			texture2D( texture_, gl_TexCoord[ 0 ].st - dv ).rgb +
//			texture2D( texture_, gl_TexCoord[ 0 ].st + dv ).rgb
		) * gaussGewicht[ i ];
	}

	gl_FragColor = vec4( col, 1.f );
//	gl_FragColor.rgb = ( ( gl_FragColor.rgb - 0.5f ) * kontrast ) + .5f;
	gl_FragColor.rgb = ( ( gl_FragColor.rgb - helligkeit ) * kontrast ) + helligkeit;
//	gl_FragColor.rgb = farbfehlsichtigkeitsMatrix * gl_FragColor.rgb  * ( 1. - texture2D( texture_glaucom_, gesichtsfeldausfaelleGroesse * 2. * relPos_ * grad_ + vec2( 0.5 ) ).a );
	gl_FragColor.rgb = farbfehlsichtigkeitsMatrix * gl_FragColor.rgb  * ( 1. - texture2D( texture_glaucom_, gesichtsfeldausfaelleGroesse * 2. * ( pixelPos_ - mousePos_ ) * grad_ + vec2( .5 ) ).a );
}
