/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "OcvSobelBlock.h"
#include "ImageHelpers.h"
#include "_2RealDatatypes.h"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace _2Real::bundle;
using namespace _2Real;
using namespace std;

OcvSobelBlock::OcvSobelBlock() : Block(), m_OutChannelOrder( ImageChannelOrder::RGB ), m_OutImageType( ImageType::UNSIGNED_BYTE ) {}
OcvSobelBlock::~OcvSobelBlock() {}

void OcvSobelBlock::setup( BlockHandle &block )
{
	try
	{
		m_Block = block;
		Image &output = block.getOutletHandle( "image_out" ).getWriteableRef< Image >();
		output = Image();

		m_OutWidth = output.getWidth();
		m_OutHeight = output.getHeight();
		m_OutChannelOrder = output.getChannelOrder();
		m_OutImageType = output.getImageType();
	}
	catch( Exception & e )
	{
		cout << e.message() << " " << e.what() << endl;
		e.rethrow();
	}
	catch( std::exception & e )
	{
		cout << e.what() << endl;
		Exception exc( e.what() );
		throw exc;
	}
}

void OcvSobelBlock::update()
{
	try
	{
		Image &output = m_Block.getOutletHandle( "image_out" ).getWriteableRef< Image >();

		vector< InletHandle > inlets = m_Block.getAllInletHandles();

		// inlets are accessible in the same order they were declared in the metadata
		Image const& input = inlets[ 0 ].getReadableRef< Image >();
		unsigned char orderX = inlets[ 1 ].getReadableRef< unsigned char >();
		unsigned char orderY = inlets[ 2 ].getReadableRef< unsigned char >();
		unsigned char aperture = inlets[ 3 ].getReadableRef< unsigned char >();

		if ( aperture != 1 && aperture != 3 && aperture != 5 && aperture != 7 )
		{
			// (?) throwing an exception is not really a good idea in this case
			// ( exc requires re-setup, and that really would not help )
			// nonetheless, the user should be notified somehow?
			m_Block.getOutletHandle( "image_out" ).discard();
			return;
		}

		if ( !( m_OutImageType == input.getImageType() && m_OutChannelOrder == input.getChannelOrder() ) || m_OutWidth != input.getWidth() || m_OutHeight != input.getHeight() )
		{
			cout << "creating new out image" << endl;
			output = input;	// this involves a copy of the data, thus making sure that the outlet has the correct datatype & channel order
							// could, however, be more efficient as the memcpy that happens is not needed
			m_OutWidth = output.getWidth();
			m_OutHeight = output.getHeight();
			m_OutChannelOrder = output.getChannelOrder();
			m_OutImageType = output.getImageType();
		}

		// no copies or anything involved here, this just allows 'viewing' the imagesource as cv mat
		cv::Mat const* const matSrc = convertToCvMat( input );
		cv::Mat *const matDst = convertToCvMat( output );

		cv::Sobel( *matSrc, *matDst, 2, orderX, orderY );

		delete matSrc;
		delete matDst;
	}
	catch( Exception & e )
	{
		cout << e.message() << " " << e.what() << endl;
		e.rethrow();
	}
	catch( std::exception & e )
	{
		cout << e.what() << endl;
	}
}

void OcvSobelBlock::shutdown() {}