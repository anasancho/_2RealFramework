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

#include <map>

#include "Poco/Mutex.h"

namespace _2Real
{

	class Runnable;
	class PooledThread;
	class Identifier;

	class ThreadPool
	{

	public:

		ThreadPool(unsigned int const& min, unsigned int const& max, unsigned int const& idleTime, unsigned int const& stackSize, std::string const& name);
		~ThreadPool();

		/**
		*	returns nr of allocated threads
		*	(somewhre in between min & max capacity)
		*/
		const unsigned int allocated() const;

		/**
		*	returns nr of allocated, not-idle threads
		*/
		const unsigned int used() const;

		/**
		*	starts a runnable
		*/
		void start(Runnable *const target);

		void stopAll();
		void joinAll();

		void stop(Identifier const& id);
		void join(Identifier const& id);

		void collect();

	private:

		PooledThread *const getFreeThread();
		PooledThread *const createThread();

		void housekeep();

		ThreadPool(ThreadPool const& pool);
		ThreadPool& operator=(ThreadPool const& pool);

		typedef std::pair< Identifier, PooledThread * >		NamedThread;
		typedef std::multimap< Identifier, PooledThread * >	ThreadTable;

		ThreadTable					m_Threads;

		std::string					m_Name;

		unsigned int				m_Capacity;
		unsigned int				m_MaxCapacity;
		unsigned int				m_IdleTime;
		unsigned int				m_StackSize;
		mutable Poco::FastMutex		m_Mutex;
		unsigned int				m_Age;

	};

}