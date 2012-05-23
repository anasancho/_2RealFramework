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

#include "_2RealBlockData.h"
#include "_2RealParameterData.h"
#include "_2RealException.h"
#include "_2RealHelpers.h"

#include <iostream>
#include <sstream>

namespace _2Real
{

	BlockData::BlockData( std::string const& name ) :
		m_Name( name ),
		m_Description( "undefined" )
	{
	}

	BlockData::~BlockData()
	{
		for ( ParameterDataMap::iterator it = m_Parameters.begin(); it != m_Parameters.end(); /**/ )
		{
			delete it->second;
			it = m_Parameters.erase( it );
		}

		for ( ParameterDataMap::iterator it = m_Inlets.begin(); it != m_Inlets.end(); /**/ )
		{
			delete it->second;
			it = m_Inlets.erase( it );
		}

		for ( ParameterDataMap::iterator it = m_Outlets.begin(); it != m_Outlets.end(); /**/ )
		{
			delete it->second;
			it = m_Outlets.erase( it );
		}
	}

	std::string const& BlockData::getName() const
	{
		return m_Name;
	}

	std::string const& BlockData::getDescription() const
	{
		return m_Description;
	}

	void BlockData::setDescription(std::string const& description)
	{
		m_Description = description;
	}

	void BlockData::addParameter( ParameterData const& data )
	{
		std::string paramName = data.getName();
		if ( m_Parameters.find( paramName ) != m_Parameters.end() )
		{
			delete m_Parameters[ paramName ];
		}

		m_Parameters[ paramName ] = &data;
	}

	void BlockData::addInlet( ParameterData const& data )
	{
		std::string inletName = data.getName();
		if ( m_Inlets.find( inletName ) != m_Inlets.end() )
		{
			delete m_Inlets[ inletName ];
		}

		m_Inlets[ inletName ] = &data;
	}

	void BlockData::addOutlet( ParameterData const& data )
	{
		std::string outletName = data.getName();
		if ( m_Outlets.find( outletName ) != m_Outlets.end() )
		{
			delete m_Outlets[ outletName ];
		}

		m_Outlets[ outletName ] = &data;
	}

	std::ostream& operator<<( std::ostream &out, BlockData const& data )
	{
		out << data.getName() << std::endl;
		out << data.getDescription() << std::endl;
		out << "parameters:" << std::endl;
		out << data.getParameters() << std::endl;
		out << "inlets:" << std::endl;
		out << data.getInlets() << std::endl;
		out << "outlets:" << std::endl;
		out << data.getOutlets() << std::endl;
		return out;
	}

	std::map< std::string, ParameterData const* > const& BlockData::getParameters() const
	{
		return m_Parameters;
	}

	std::map< std::string, ParameterData const* > const& BlockData::getInlets() const
	{
		return m_Inlets;
	}

	std::map< std::string, ParameterData const* > const& BlockData::getOutlets() const
	{
		return m_Outlets;
	}

}