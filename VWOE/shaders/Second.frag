#version 120

uniform sampler2D
texture_;

uniform float
invWidth,
invHeight;

const int
halbeKernelBreite = 9;

uniform float
gaussGewicht[ halbeKernelBreite + 1 ];		// 0 1 2 ... 8 9     das macht eine Kernelgroesse von 19 x 19


void main( )
{
//	gl_FragColor = texture2D( texture_ , gl_TexCoord[ 0 ].st );

	vec3
	col = texture2D( texture_, gl_TexCoord[ 0 ].st ).rgb * gaussGewicht[ 0 ];

	vec2
	dv = vec2( 0. );

	for( int i = 1; i < halbeKernelBreite; ++i ) {

		dv.y += invHeight;

		col +=	(
			texture2D( texture_, gl_TexCoord[ 0 ].st - dv ).rgb +
			texture2D( texture_, gl_TexCoord[ 0 ].st + dv ).rgb
		) * gaussGewicht[ i ];
	}

	gl_FragColor = vec4( col, 1.f );
}
