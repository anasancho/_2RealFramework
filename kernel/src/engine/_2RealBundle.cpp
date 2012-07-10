
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

#include "engine/_2RealBundle.h"
#include "engine/_2RealBundleManager.h"
#include "engine/_2RealFunctionBlock.h"

#include "app/_2RealBundleHandle.h"

#include <sstream>

using std::string;
using std::ostringstream;
using std::make_pair;

namespace _2Real
{

	Bundle::Bundle( app::BundleInfo const& info, BundleManager &bundleManager ) :
		NonCopyable< Bundle >(),
		Identifiable< Bundle >( Ids(), info.getName() ),
		Handleable< app::BundleHandle >( *this ),
		m_BundleManager( bundleManager ),
		m_BundleInfo( info ),
		m_ContextBlock( nullptr )
	{
	}

	Bundle::~Bundle()
	{
		clear();
	}

	void Bundle::clear()
	{
		//for ( BlockIterator it = m_BlockInstances.begin(); it != m_BlockInstances.end(); /**/ )
		//{
		//	delete it->second;
		//	it = m_BlockInstances.erase( it );
		//}
		m_BlockInstances.clear();
	}

	app::BundleInfo const& Bundle::getBundleInfo() const
	{
		return m_BundleInfo;
	}

	app::BlockHandle & Bundle::createBlockInstance( std::string const& blockName )
	{
		return m_BundleManager.createBlockInstance( *this, blockName ).getHandle();
	}

	app::ContextBlockHandle & Bundle::getContextBlockHandle() const
	{
		return m_ContextBlock->getHandle();
	}

	unsigned int Bundle::getBlockInstanceCount( string const& blockName ) const
	{
		unsigned int counter = 0;
		std::pair< BlockInstanceConstIterator, BlockInstanceConstIterator > range = m_BlockInstances.equal_range( blockName );
		for ( BlockInstanceConstIterator it = range.first; it != range.second; ++it )
		{
			++counter;
		}

		return counter;
	}

	void Bundle::addBlockInstance( FunctionBlock< app::BlockHandle > &block, string const& blockName )
	{
		m_BlockInstances.insert( make_pair( blockName, &block ) );
	}

	void Bundle::setContextBlock( FunctionBlock< app::ContextBlockHandle > &context )
	{
		m_ContextBlock = &context;
	}
}