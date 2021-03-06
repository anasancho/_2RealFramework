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
#include "_2RealBundle.h"
#include "OcvGaussianBlurBlock.h"
#include "OcvSobelBlock.h"
#include "ImageHelpers.h"
#include <sstream>
#include <iostream>

using namespace _2Real;
using namespace _2Real::bundle;

using std::string;
using std::cout;
using std::endl;

void getBundleMetainfo( BundleMetainfo& info )
{
	try
	{
		info.setName( "ComputerVisionBundle" );
		info.setDescription( "computer vision stuff" );
		info.setAuthor( "gerlinde emsenhuber" );
		info.setCategory( "image processing" );
		info.setContact( "help@cadet.at" );
		info.setVersion( 0, 1, 0 );

		float blue[ 4 ] = { 0.2f, 0.1f, 0.7f, 1.0f };
		float green[ 4 ] = { 0.1f, 0.7f, 0.2f, 1.0f };

		float *init = makeCirclePattern< float >( 640, 480, 3, 60, blue, green );
		Image checkerImg( init, true, 640, 480, ImageChannelOrder::RGB );
		Options< int > borderOptions = Options< int >( 0, "constant" )( 1, "replicate" )( 2, "reflect" )( 4, "reflect_101" );

		BlockMetainfo gauss = info.exportBlock< OcvGaussianBlurBlock, WithoutContext >( "OcvGaussianBlurBlock" );
		gauss.setDescription( "applies gaussian blur to input image" );
		gauss.setCategory( "image filter" );
		// can handle any format
		gauss.addInlet< Image >( "InImage", checkerImg );
		// must be odd
		gauss.addInlet< unsigned char >( "kernel_x", 1 );
		gauss.addInlet< unsigned char >( "kernel_y", 1 );
		// must be positive
		gauss.addInlet< double >( "sigma_x", 1.1 );
		gauss.addInlet< double >( "sigma_y", 1.1 );
		// those are the border interpolation options available for this function
		gauss.addInlet< int >( "boder_interpolation", 0, borderOptions );
		// format out == format in
		gauss.addOutlet< Image >( "OutImage" );

		//BlockMetainfo eq = info.exportBlock< OcvHistogramEqualizationBlock, WithoutContext >( "OcvHistogramEqualizationBlock" );
		//eq.setDescription( "xxx" );
		//eq.setCategory( "image filter" );
		//eq.addInlet< Image >( "ImageData", checkerImg );
		//eq.addOutlet< Image >( "ImageData" );

		//// either uchar in -> ushort out or float in - float out
		//BlockMetainfo sobel = info.exportBlock< OcvSobelBlock, WithoutContext >( "OcvSobelBlock" );
		//sobel.setDescription( "applies sobel filter to input image" );
		//sobel.setCategory( "image filter" );
		//sobel.addInlet< Image >( "image_in", checkerImg );
		//sobel.addInlet< unsigned char>( "order_x", 1 );
		//sobel.addInlet< unsigned char >( "order_y", 1 );
		//sobel.addInlet< unsigned char >( "aperture", 3 );
		//sobel.addOutlet< Image >( "image_out" );
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}