/*
* CinderBullet originally created by Peter Holzkorn on 2/16/10
* 
* Copyright (c) 2013, Ban the Rewind
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or 
* without modification, are permitted provided that the following 
* conditions are met:
* 
* Redistributions of source code must retain the above copyright 
* notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright 
* notice, this list of conditions and the following disclaimer in 
* the documentation and/or other materials provided with the 
* distribution.
* 
* Neither the name of the Ban the Rewind nor the names of its 
* contributors may be used to endorse or promote products 
* derived from this software without specific prior written 
* permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
*/

#include "Utilities.h"

namespace bullet {
	using namespace ci;
	using namespace std;

	Quatf fromBulletQuaternion( const btQuaternion &quat )
	{
		return ci::Quatf( quat.getX(), quat.getY(), quat.getZ(), quat.getW() );
	}

	Matrix44f fromBulletTransform( const btTransform &matrix )
	{
		btTransform trans;
		Matrix44f m;
		matrix.getOpenGLMatrix( m.m );
		return m;
	}
	
	Vec3f fromBulletVector3( const btVector3 &vec )
	{
		return Vec3f( vec.x(), vec.y(), vec.z() );
	}

	btQuaternion toBulletQuaternion( const Quatf &quat )
	{
		return btQuaternion( quat.v.x, quat.v.y, quat.v.z, quat.w );
	}

	btTransform	toBulletTransform( const ci::Matrix44f &matrix )
	{
		btTransform trans;
		trans.setFromOpenGLMatrix( matrix.m );
		return trans;
	}

	btVector3 toBulletVector3( const Vec3f &vec )
	{
		return btVector3( vec.x, vec.y, vec.z );
	}
}
