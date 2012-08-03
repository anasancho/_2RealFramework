#include <iostream>
#include <string>
#include <sstream>
#include "KinectOpenNIMotorBlock.h"
#include "_2RealDatatypes.h"

using namespace _2Real;
using _2Real::bundle::BlockHandle;
using _2Real::Exception;
using std::cout;
using std::endl;
using std::string;

KinectOpenNIMotorBlock::KinectOpenNIMotorBlock( ContextBlock & context )
	:Block()
{
	m_OpenNIDeviceManager = static_cast<OpenNIDeviceManager*>( &context );
}

KinectOpenNIMotorBlock::~KinectOpenNIMotorBlock()
{
}

void KinectOpenNIMotorBlock::setup( BlockHandle &block )
{
	try
	{
		// inlet handles
		m_DeviceIndexInletHandle = block.getInletHandle("DeviceIndex");
		m_AngleInletHandle = block.getInletHandle("Angle");
		m_AngleOutletHandle = block.getOutletHandle("Angle");

		m_iCurrentDevice = -1;	// no device set yet
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}

void KinectOpenNIMotorBlock::update()
{
	try
	{
		if(m_OpenNIDeviceManager->getNumberOfConnectedDevices()<=0)	// if there is no cameras connected there is nothing todo so return
		{
			m_AngleOutletHandle.discard();
			return;
		}

		int deviceIndex = m_DeviceIndexInletHandle.getReadableRef<int>();
		int angle = m_AngleInletHandle.getReadableRef<int>();
	
		// camera index changed
		if(deviceIndex != m_iCurrentDevice || angle != m_iInputAngle )
		{
			m_iCurrentDevice = deviceIndex;
			if(m_iCurrentDevice>=0)  
			{
				m_iInputAngle = angle;
				m_OpenNIDeviceManager->setMotorAngle(m_iCurrentDevice, m_iInputAngle);
			}
		}

		if(m_iCurrentDevice>=0) 
		{
			int curAngle = m_OpenNIDeviceManager->getMotorAngle(m_iCurrentDevice);
			if(curAngle != m_iCurrentAngle)
			{
				m_iCurrentAngle = angle;
				m_AngleOutletHandle.getWriteableRef<int>() = m_iCurrentAngle;
			}
			else
			{
				m_AngleOutletHandle.discard();
			}
		}
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}

void KinectOpenNIMotorBlock::shutdown()
{
	std::cout << "shutdown block" << std::endl;
	if(m_iCurrentDevice>=0)
	{
		m_iCurrentDevice = -1;
	}
}