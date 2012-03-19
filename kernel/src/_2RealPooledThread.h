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

#include "_2RealRunnable.h"
#include "_2RealRunnableManager.h"
#include "_2RealException.h"

#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Event.h"

namespace _2Real
{

	class ThreadPoolCallback;

	class PooledThread : public Poco::Runnable
	{
	
	public:

		PooledThread(ThreadPoolCallback &callback, unsigned int stackSize = POCO_THREAD_STACK_SIZE);
		~PooledThread();

		const bool isIdle() const;
		const bool join();

		void run();
		void run(Poco::Thread::Priority const& priority, _2Real::RunnableManager &target);
		void reactivate();

		const bool operator<(PooledThread const& rhs) const;

	private:

		/**
		*	the runnable that is to be executed
		*/
		_2Real::RunnableManager		*m_Target;

		/**
		*	true if this thread has no target to execute
		*/
		volatile bool				m_IsIdle;

		/**
		*	the underlying thread
		*/
		Poco::Thread				m_Thread;

		/**
		*	callback to the threadpool
		*/
		ThreadPoolCallback			*m_Callback;

		/*
		*	sync stuff - mainly a lot of events!
		*/
		Poco::Event					m_TargetReady;
		Poco::Event					m_TargetCompleted;
		Poco::Event					m_ThreadStarted;
		Poco::Event					m_ThreadStopped;
		mutable Poco::FastMutex		m_Mutex;

	};

}