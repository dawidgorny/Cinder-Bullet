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

#include "CollisionObject.h"

namespace bullet
{

	using namespace ci;
	using namespace std;

	CollisionObject::CollisionObject() 
	{
		mPrimitiveType		= PRIMITIVE_NONE;
		mRigidBody			= 0;
		mScale				= Vec3f::one();
		mSoftBody			= 0;
	}

	CollisionObject::~CollisionObject() 
	{
		if ( mSoftBody != 0 ) {
			delete mSoftBody;
			mSoftBody = 0;
		}
		if ( mRigidBody != 0 ) {
			if ( mRigidBody->getMotionState() ) {
				delete mRigidBody->getMotionState();
			}
			delete mRigidBody;
			mRigidBody = 0;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	btCollisionObject* CollisionObject::getBulletBody() 
	{ 
		if ( mSoftBody != 0 ) {
			return (btCollisionObject*)mSoftBody;
		} else if ( mRigidBody != 0 ) {
			return (btCollisionObject*)mRigidBody;
		}
		return 0;
	}

	btCollisionObject* CollisionObject::getBulletBody() const
	{ 
		if ( mSoftBody != 0 ) {
			return (btCollisionObject*)mSoftBody;
		} else if ( mRigidBody != 0 ) {
			return (btCollisionObject*)mRigidBody;
		}
		return 0;
	}

	Vec3f CollisionObject::getCenterPosition() 
	{ 
		Vec3f position;
		if ( mSoftBody != 0 ) {
			position = fromBulletVector3( mSoftBody->m_bounds[ 0 ].lerp( mSoftBody->m_bounds[ 1 ], 0.5f ) );
		} else if ( mRigidBody != 0 ) {
			position = fromBulletVector3( mRigidBody->getCenterOfMassPosition() );
		}
		return position;
	}

	Vec3f CollisionObject::getCenterPosition() const 
	{ 
		Vec3f position;
		if ( mSoftBody != 0 ) {
			position = fromBulletVector3( mSoftBody->m_bounds[ 0 ].lerp( mSoftBody->m_bounds[ 1 ], 0.5f ) );
		} else if ( mRigidBody != 0 ) {
			position = fromBulletVector3( mRigidBody->getCenterOfMassPosition() );
		}
		return position;
	}

	vector<size_t>& CollisionObject::getIndices()
	{
		return mIndices;
	}

	const vector<size_t>& CollisionObject::getIndices() const
	{
		return mIndices;
	}
	
	vector<Vec3f>& CollisionObject::getNormals()
	{
		return mNormals;
	}

	const vector<Vec3f>& CollisionObject::getNormals() const
	{
		return mNormals;
	}

	vector<Vec3f>& CollisionObject::getPositions()
	{
		return mPositions;
	}

	const vector<Vec3f>& CollisionObject::getPositions() const
	{
		return mPositions;
	}

	CollisionObject::PrimitiveType CollisionObject::getPrimitiveType()
	{
		return mPrimitiveType;
	}

	CollisionObject::PrimitiveType CollisionObject::getPrimitiveType() const
	{
		return mPrimitiveType;
	}

	vector<Vec2f>& CollisionObject::getTexCoords()
	{
		return mTexCoords;
	}

	const vector<Vec2f>& CollisionObject::getTexCoords() const
	{
		return mTexCoords;
	}

	Matrix44f CollisionObject::getTransformMatrix() 
	{ 
		Matrix44f worldTransform;
		if ( mSoftBody != 0 ) {
			worldTransform = getTransformMatrix( mSoftBody ); 
		} else if ( mRigidBody != 0 ) {
			worldTransform = getTransformMatrix( mRigidBody );
		}
		worldTransform.scale( mScale );
		return worldTransform;
	}

	Matrix44f CollisionObject::getTransformMatrix() const 
	{ 
		Matrix44f worldTransform;
		if ( mSoftBody != 0 ) {
			worldTransform = getTransformMatrix( mSoftBody ); 
		} else if ( mRigidBody != 0 ) {
			worldTransform = getTransformMatrix( mRigidBody );
		}
		worldTransform.scale( mScale );
		return worldTransform;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	bool CollisionObject::isMeshBody()
	{
		return mIndices.size() > 0;
	}

	bool CollisionObject::isMeshBody() const
	{
		return mIndices.size() > 0;
	}

	bool CollisionObject::isPrimitiveBody()
	{
		return mPrimitiveType != PRIMITIVE_NONE;
	}

	bool CollisionObject::isPrimitiveBody() const
	{
		return mPrimitiveType != PRIMITIVE_NONE;
	}

	bool CollisionObject::isRigidBody()
	{
		return mRigidBody != 0;
	}

	bool CollisionObject::isRigidBody() const
	{
		return mRigidBody != 0;
	}

	bool CollisionObject::isSoftBody()
	{
		return mSoftBody != 0;
	}

	bool CollisionObject::isSoftBody() const
	{
		return mSoftBody != 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	Matrix44f CollisionObject::getTransformMatrix( const btRigidBody* body )
	{
		btTransform trans;
		body->getMotionState()->getWorldTransform( trans );
		Matrix44f matrix;
		trans.getOpenGLMatrix( matrix.m );
		return matrix;
	}

	Matrix44f CollisionObject::getTransformMatrix( const btSoftBody* body )
	{
		btTransform trans = body->getWorldTransform();
		Matrix44f matrix;
		trans.getOpenGLMatrix( matrix.m );
		return matrix;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	btHeightfieldTerrainShape* CollisionObject::createHeightfieldTerrainShape( const Channel32f &heightField, float minHeight, float maxHeight, const Vec3f &scale )
	{
		int32_t len		= heightField.getHeight(); 
		int32_t width	= heightField.getWidth();

        float heightScale = math<float>::abs( minHeight ) + math<float>::abs( maxHeight );
		btHeightfieldTerrainShape* shape = new btHeightfieldTerrainShape( width, len, heightField.getData(), heightScale, minHeight, maxHeight, 1, PHY_FLOAT, false );

		shape->setLocalScaling( toBulletVector3( scale ) );
		return shape;
	}

	btBvhTriangleMeshShape* CollisionObject::createConcaveMeshShape( const vector<Vec3f>& vertices, const vector<uint32_t>& indices, const Vec3f& scale, float margin )
	{
		btTriangleMesh* mesh = new btTriangleMesh( true, false );

		uint32_t numTriangles = indices.size() / 3;
		for ( uint32_t i = 0; i < numTriangles; i += 3 )
			mesh->addTriangle( 
			toBulletVector3( vertices.at( indices.at( i + 0 ) ) ), 
			toBulletVector3( vertices.at( indices.at( i + 1 ) ) ), 
			toBulletVector3( vertices.at( indices.at( i + 2 ) ) ), 
			true
			 );

		btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape( mesh, true );
		shape->buildOptimizedBvh();

		btVector3 localScaling = toBulletVector3( scale );
		shape->setLocalScaling( localScaling );
		shape->setMargin( margin );
		return shape;
	}

	btConvexHullShape* CollisionObject::createConvexHullShape( const vector<Vec3f>& vertices, const Vec3f& scale )
	{
		btConvexHullShape* shape = new btConvexHullShape();

		for ( uint32_t i = 0; i < vertices.size(); i++ ) {
			shape->addPoint( toBulletVector3( vertices.at( i ) ) );
		}

		btVector3 localScaling = toBulletVector3( scale );
		shape->setLocalScaling( localScaling );
		return shape;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	void CollisionObject::update()
	{
		if ( mSoftBody != 0 ) {
			
			size_t count = mSoftBody->m_faces.size();
			
			mNormals.clear();
			mPositions.clear();
			
			for ( size_t i = 0; i < count; ++i ) {
				const btSoftBody::Face&	face = mSoftBody->m_faces[ i ];

				Vec3f vert0	= fromBulletVector3( face.m_n[ 0 ]->m_x );
				Vec3f vert1	= fromBulletVector3( face.m_n[ 1 ]->m_x );
				Vec3f vert2	= fromBulletVector3( face.m_n[ 2 ]->m_x );

				mPositions.push_back( vert0 );
				mPositions.push_back( vert1 );
				mPositions.push_back( vert2 );
			}

			for ( size_t i = 0; i < mPositions.size(); ++i ) {
				btVector3 position = toBulletVector3( mPositions.at( i ) );
				btVector3 normal( 0.0f, 0.0f, 0.0f );

				int32_t numFaces	= 0;
				size_t count		= mSoftBody->m_faces.size();
				for ( size_t i = 0; i < count; ++i ) {
					const btSoftBody::Face&	face = mSoftBody->m_faces[ i ];
					if ( face.m_n[ 0 ]->m_x == position || 
						face.m_n[ 1 ]->m_x == position || 
						face.m_n[ 2 ]->m_x == position ) {
						normal += face.m_normal;
						++numFaces;
					}
				}
		
				if ( numFaces > 0 ) {
					normal /= (float)numFaces;
				}

				mNormals.push_back( fromBulletVector3( normal ) * -1.0f );
			}
		}
	}

}
