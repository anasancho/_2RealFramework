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

#pragma once

#include "app/_2RealCallbacks.h"
#include "engine/_2RealLink.h"
#include "helpers/_2RealEvent.h"
#include "helpers/_2RealPoco.h"
#include "app/_2RealBlockHandle.h"
#include "app/_2RealContextBlockHandle.h"
#include "_2RealSystemState.h"			// MOVE TO APP FOLDER

#include <set>
#include <string>

namespace _2Real
{

	namespace app
	{
		class BundleHandle;
		class SystemState;
	}

	class Logger;
	class Timer;
	class Typetable;
	class ThreadPool;
	class BundleManager;
	class AbstractUberBlock;
	class System;
	class AbstractInletIO;
	class OutletIO;
	class Bundle;

	template< typename T >
	class FunctionBlock;

	class EngineImpl
	{

		template< typename T >
		friend class SingletonHolder;

	public:

		struct LinkCmp
		{
			bool operator()( IOLink *l1, IOLink *l2 )
			{
				return ( *l1 < *l2 );
			}
		};

		typedef std::set< IOLink *, LinkCmp >											Links;
		typedef std::set< IOLink *, LinkCmp >::iterator									LinkIterator;
		typedef std::set< IOLink *, LinkCmp >::const_iterator							LinkConstIterator;

		typedef std::list< FunctionBlock< app::BlockHandle > * >						BlockInstances;
		typedef std::list< FunctionBlock< app::BlockHandle > * >::iterator				BlockInstanceIterator;
		typedef std::list< FunctionBlock< app::BlockHandle > * >::const_iterator		BlockInstanceConstIterator;

		typedef std::list< FunctionBlock< app::ContextBlockHandle > * >					BundleContexts;
		typedef std::list< FunctionBlock< app::ContextBlockHandle > * >::iterator		BundleContextIterator;
		typedef std::list< FunctionBlock< app::ContextBlockHandle > * >::const_iterator	BundleContextConstIterator;

		typedef std::set< Bundle * >													Bundles;
		typedef std::set< Bundle * >::iterator											BundleIterator;
		typedef std::set< Bundle * >::const_iterator									BundleConstIterator;

		static EngineImpl & instance();

		Timer&							getTimer();
		Logger&							getLogger();
		ThreadPool &					getThreadPool();

		const long						getElapsedTime() const;

		void							clearFully();
		void							clearBlockInstances();

		void							addBlock( FunctionBlock< app::BlockHandle > &block );
		void							addBlock( FunctionBlock< app::ContextBlockHandle > &block );
		void							removeBlock( FunctionBlock< app::BlockHandle > &block, const long timeout );
		void							removeBlock( FunctionBlock< app::ContextBlockHandle > &block, const long timeout );

		void							registerToException( app::BlockExcCallback &callback );
		void							unregisterFromException( app::BlockExcCallback &callback );
		void							registerToException( app::ContextBlockExcCallback &callback );
		void							unregisterFromException( app::ContextBlockExcCallback &callback );
		void							handleException( app::BlockHandle &block, Exception const& exception ) const;
		void							handleException( app::ContextBlockHandle &block, Exception const& exception ) const;

		BlockInstances					getCurrentBlockInstances() const;
		Bundles const&					getCurrentBundles() const;
		Links const&					getCurrentLinks() const;
		Links&							getCurrentLinks();

		IOLink							createLink( BasicInletIO &inlet, OutletIO &outlet );
		std::pair< IOLink, IOLink >		createLinkWithConversion( BasicInletIO &inlet, OutletIO &outlet );
		void							destroyLink( BasicInletIO &inlet, OutletIO &outlet );
		void							clearLinksFor( BasicInletIO &inlet );

		void							setBaseDirectory( std::string const& directory );
		//app::BundleHandle &				loadLibrary( std::string const& libraryPath );
		//app::BundleHandle &				findBundleByName( std::string const& name ) const;
		//app::BundleHandle &				findBundleByPath( std::string const& libraryPath ) const;
		Bundle &						loadLibrary( std::string const& libraryPath );
		Bundle &						findBundleByName( std::string const& name ) const;
		Bundle &						findBundleByPath( std::string const& libraryPath ) const;
					
		void							getCurrentSystemState( app::SystemState &state ) const;

	private:

		EngineImpl();
		~EngineImpl();

		// whatever you do. do not change the ordering of member variables here!
		// ( unless you absolutely have to, in which case, good luck )

		Logger					*m_Logger;
		Timer					*m_Timer;
		ThreadPool				*m_ThreadPool;
		BundleManager			*m_BundleManager;
		System					*m_System;
		Poco::Timestamp			m_Timestamp;

		typedef std::pair< Exception, app::BlockHandle >			BlockException;
		typedef std::pair< Exception, app::ContextBlockHandle >		ContextBlockException;

		Links														m_Links;
		CallbackEvent< BlockException const& >						m_BlockExceptionEvent;
		CallbackEvent< ContextBlockException const& >				m_ContextBlockExceptionEvent;

	};

}