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

#include "Constraint.h"

#include "Utilities.h"

namespace bullet {

	using namespace ci;
	using namespace std;

	Constraint::Constraint() 
	{
		mConstraint	= 0;
		mDistance	= numeric_limits<float>::max();
		mPosition	= Vec3f::one() * mDistance;
	}

	const Constraint& Constraint::operator=( const Constraint &rhs )
	{
		mConstraint = rhs.mConstraint;
		mDistance	= rhs.mDistance;
		mPosition	= rhs.mPosition;
		return *this;
	}
	
	Constraint::Constraint( const Constraint &rhs )
	{
		mConstraint = rhs.mConstraint;
		mDistance	= rhs.mDistance;
		mPosition	= rhs.mPosition;
	}
	
	Constraint::~Constraint() 
	{
	}

	Vec3f& Constraint::getPosition()
	{
		return mPosition;
	}

	const Vec3f& Constraint::getPosition() const
	{
		return mPosition;
	}

	void Constraint::reset()
	{
		if ( mConstraint != 0 ) {
			delete mConstraint;
			mConstraint = 0;
		}
		mDistance = 0.0f;
		mPosition = Vec3f::zero();
	}

	void Constraint::update( const ci::Ray &ray )
	{
		mPosition = ray.getOrigin() + ray.getDirection().normalized() * mDistance;
		mConstraint->setPivotB( toBulletVector3( mPosition ) );
	}

}
