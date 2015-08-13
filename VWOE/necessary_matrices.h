#ifndef NECESSARY_MATRICES_HPP
#define NECESSARY_MATRICES_HPP

#include	"properties.hpp"
#include	<algorithm>
#include	<sstream>
#include	<ostream>
#include	<iostream>
#include	<iomanip>


class	Mat3x3 {

	public:

		Mat3x3( ) :
		xx( datas[ 0 ] ), xy( datas[ 1 ]), xz( datas[ 2 ] ),
		yx( datas[ 3 ] ), yy( datas[ 4 ]), yz( datas[ 5 ] ),
		zx( datas[ 6 ] ), zy( datas[ 7 ]), zz( datas[ 8 ] ) {

		}

		Mat3x3( float const p_datas[ 9 ], bool const p_transpose = false ) :
		xx( datas[ 0 ] ), xy( datas[ 1 ]), xz( datas[ 2 ] ),
		yx( datas[ 3 ] ), yy( datas[ 4 ]), yz( datas[ 5 ] ),
		zx( datas[ 6 ] ), zy( datas[ 7 ]), zz( datas[ 8 ] ) {

			if( p_transpose ) {

				xx = p_datas[ 0 ]; yx = p_datas[ 1 ]; zx = p_datas[ 2 ];
				xy = p_datas[ 3 ]; yy = p_datas[ 4 ]; zy = p_datas[ 5 ];
				xz = p_datas[ 6 ]; yz = p_datas[ 7 ]; zz = p_datas[ 8 ];

				return;
			}

			std::copy( p_datas, p_datas + 9, datas );
		}

		Mat3x3(
			float const & p_xx, float const & p_xy, float const & p_xz,
			float const & p_yx, float const & p_yy, float const & p_yz,
			float const & p_zx, float const & p_zy, float const & p_zz,
			bool const p_transpose = false ) :
		xx( datas[ 0 ] ), xy( datas[ 1 ]), xz( datas[ 2 ] ),
		yx( datas[ 3 ] ), yy( datas[ 4 ]), yz( datas[ 5 ] ),
		zx( datas[ 6 ] ), zy( datas[ 7 ]), zz( datas[ 8 ] ) {

			if( p_transpose ) {

				xx = p_xx; yx = p_xy; zx = p_xz;
				xy = p_yx; yy = p_yy; zy = p_yz;
				xz = p_zx; yz = p_zy; zz = p_zz;

				return;
			}

			xx = p_xx; xy = p_xy; xz = p_xz;
			yx = p_yx; yy = p_yy; yz = p_yz;
			zx = p_zx; zy = p_zy; zz = p_zz;
		}

		Mat3x3( Mat3x3 const & p_mat3x3, bool const p_transpose = false ) :
		xx( datas[ 0 ] ), xy( datas[ 1 ]), xz( datas[ 2 ] ),
		yx( datas[ 3 ] ), yy( datas[ 4 ]), yz( datas[ 5 ] ),
		zx( datas[ 6 ] ), zy( datas[ 7 ]), zz( datas[ 8 ] ) {

			if( p_transpose ) {

				xx = p_mat3x3.xx; yx = p_mat3x3.xy; zx = p_mat3x3.xz;
				xy = p_mat3x3.yx; yy = p_mat3x3.yy; zy = p_mat3x3.yz;
				xz = p_mat3x3.zx; yz = p_mat3x3.zy; zz = p_mat3x3.zz;

				return;
			}

			xx = p_mat3x3.xx; xy = p_mat3x3.xy; xz = p_mat3x3.xz;
			yx = p_mat3x3.yx; yy = p_mat3x3.yy; yz = p_mat3x3.yz;
			zx = p_mat3x3.zx; zy = p_mat3x3.zy; zz = p_mat3x3.zz;
		}

	public:

		float
		datas[ 9 ];

		float
		&xx, &xy, &xz,
		&yx, &yy, &yz,
		&zx, &zy, &zz;

	private:

		void
		swap( float & p_a, float & p_b ) {

			float
			tmp = p_b;

			p_b = p_a;
			p_a = tmp;
		}

	public:

		Mat3x3 &
		operator = ( Mat3x3 const & p_mat3x3 ) {

			xx = p_mat3x3.xx; xy = p_mat3x3.xy; xz = p_mat3x3.xz;
			yx = p_mat3x3.yx; yy = p_mat3x3.yy; yz = p_mat3x3.yz;
			zx = p_mat3x3.zx; zy = p_mat3x3.zy; zz = p_mat3x3.zz;

			return *this;
		}

		Mat3x3
		operator + ( Mat3x3 const & p_mat3x3 ) const {

			return Mat3x3(
				xx + p_mat3x3.xx, xy + p_mat3x3.xy, xz + p_mat3x3.xz,
				yx + p_mat3x3.yx, yy + p_mat3x3.yy, yz + p_mat3x3.yz,
				zx + p_mat3x3.zx, zy + p_mat3x3.zy, zz + p_mat3x3.zz );
		}

		Mat3x3
		operator - ( Mat3x3 const & p_mat3x3 ) const {

			return Mat3x3(
				xx - p_mat3x3.xx, xy - p_mat3x3.xy, xz - p_mat3x3.xz,
				yx - p_mat3x3.yx, yy - p_mat3x3.yy, yz - p_mat3x3.yz,
				zx - p_mat3x3.zx, zy - p_mat3x3.zy, zz - p_mat3x3.zz );
		}

		Mat3x3
		operator * ( Mat3x3 const & p_mat3x3 ) const {

			return Mat3x3(

				xx * p_mat3x3.xx + xy * p_mat3x3.yx + xz * p_mat3x3.zx,	xx * p_mat3x3.xy + xy * p_mat3x3.yy + xz * p_mat3x3.zy,	xx * p_mat3x3.xz + xy * p_mat3x3.yz + xz * p_mat3x3.zz,
				yx * p_mat3x3.xx + yy * p_mat3x3.yx + yz * p_mat3x3.zx,	yx * p_mat3x3.xy + yy * p_mat3x3.yy + yz * p_mat3x3.zy,	yx * p_mat3x3.xz + yy * p_mat3x3.yz + yz * p_mat3x3.zz,
				zx * p_mat3x3.xx + zy * p_mat3x3.yx + zz * p_mat3x3.zx,	zx * p_mat3x3.xy + zy * p_mat3x3.yy + zz * p_mat3x3.zy,	zx * p_mat3x3.xz + zy * p_mat3x3.yz + zz * p_mat3x3.zz );
		}

		Mat3x3
		operator * ( float const & p_skalar ) const {

			return Mat3x3(

				xx * p_skalar, xy * p_skalar, xz * p_skalar,
				yx * p_skalar, yy * p_skalar, yz * p_skalar,
				zx * p_skalar, zy * p_skalar, zz * p_skalar );
		}
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

		static Mat3x3
		getMat3x3( ParameterSehen::Farbfehlsichtigkeit const & p_ffs, float p_level ) {

			if(	p_ffs == ParameterSehen::KEINE ) {

				return Mat3x3( datas );
			}

			p_level = p_level < 0. ? 0. : 1. < p_level ? 1. : p_level;

			int
			id = p_level * 10;

			if(	ParameterSehen::PROTANOPIE <= p_ffs && p_ffs <= ParameterSehen::TRITANOPIE ) {

				float
				off = ( 10 * p_level - id );

				Mat3x3
				mat1( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + id * ( 3 * 3 ) ),
				mat2( datas + ( p_ffs - 1 ) * ( 3 * 3 * 11 ) + ( id + 1 ) * ( 3 * 3 ) );

				return	Mat3x3( mat1 + ( mat2 - mat1 ) * off );
			}

			if(	p_ffs == ParameterSehen::ACHROMATOPSIE ) {

				Mat3x3
				mat1( datas + 3 * ( 3 * 3 * 11 ) ),
				eye( datas );

				return eye * ( 1. - p_level ) + mat1 * p_level;
			}

			return Mat3x3( datas );
		}
};

#endif // NECESSARY_MATRICES_HPP
