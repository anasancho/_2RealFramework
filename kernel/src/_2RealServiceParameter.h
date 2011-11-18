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

#include "_2RealSetupParameter.h"

namespace _2Real
{

	/**
	*
	*/

	class ServiceContainer;

	class ServiceParameter : public SetupParameter
	{

	public:

		/**
		*	
		*/
		ServiceParameter(Id *const _id, ServiceContainer *const _service, std::string const& _type);

		/**
		*	
		*/
		ServiceParameter(ServiceParameter const& _src);

		/**
		*	
		*/
		ServiceParameter& operator=(ServiceParameter const& _src);

		/**
		*	
		*/
		~ServiceParameter();

		/**
		*	returns owning service container
		*/
		ServiceContainer *const			service();

		/**
		*	returns owning service container - const version
		*/
		ServiceContainer *const			service() const;

	private:

		/**
		*	the service container this parameter belongs to
		*/
		ServiceContainer				*m_Service;

	};

}