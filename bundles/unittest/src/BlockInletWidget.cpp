#include "BlockInletWidget.h"

#include <iostream>

#ifdef _UNIX
    #include <float.h>  //for DBL_MAX
#endif

using namespace std;
using namespace _2Real;

// sorry for all the codeduplication but QT doesn't support templated signal/slot concept which sucks
BlockInletWidget::BlockInletWidget(_2Real::app::InletHandle& inletHandle, QWidget *parent)
	: QGroupBox(parent),
	  m_InletHandle ( inletHandle )
{
	try
	{
		QHBoxLayout*	layout = new QHBoxLayout();
		layout->addWidget( new QLabel(QString::fromStdString( m_InletHandle.getName())) );

		// set and init input widget according to inlet's type
		if(m_InletHandle.getTypename() == "bool")
		{
			m_ValueWidget = new QCheckBox();
			dynamic_cast<QCheckBox*>(m_ValueWidget)->setChecked(m_InletHandle.getCurrentInput().getData<bool>());
			connect(m_ValueWidget, SIGNAL(stateChanged(int)), this, SLOT(setBoolValue(int)));
		}
		else if(m_InletHandle.getTypename() == "unsigned char")
		{
			m_ValueWidget = new QSpinBox();
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMinimum(0);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMaximum(UCHAR_MAX);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<unsigned char>());
			connect(m_ValueWidget, SIGNAL(valueChanged(int)), this, SLOT(setUCharValue(int)));
		}
		else if(m_InletHandle.getTypename() == "char")
		{
			m_ValueWidget = new QSpinBox();
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMinimum(CHAR_MIN);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMaximum(CHAR_MAX);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<char>());
			connect(m_ValueWidget, SIGNAL(valueChanged(int)), this, SLOT(setCharValue(int)));
		}
		else if(m_InletHandle.getTypename() == "unsigned short")
		{
			m_ValueWidget = new QSpinBox();
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMinimum(0);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMaximum(USHRT_MAX);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<unsigned short>());
			connect(m_ValueWidget, SIGNAL(valueChanged(int)), this, SLOT(setUShortValue(int)));
		}
		else if(m_InletHandle.getTypename() == "short")
		{
			m_ValueWidget = new QSpinBox();
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMinimum(SHRT_MIN);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMaximum(SHRT_MAX);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<short>());
			connect(m_ValueWidget, SIGNAL(valueChanged(int)), this, SLOT(setShortValue(int)));
		}
		if(m_InletHandle.getTypename() == "unsigned int")
		{
			m_ValueWidget = new QDoubleSpinBox();
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMinimum(0);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMaximum(UINT_MAX);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<unsigned int>());
			connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setUIntValue(double)));
		}
		else if(m_InletHandle.getTypename() == "int")
		{
			m_ValueWidget = new QSpinBox();
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMinimum(INT_MIN);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setMaximum(INT_MAX);
			dynamic_cast<QSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<int>());
			connect(m_ValueWidget, SIGNAL(valueChanged(int)), this, SLOT(setIntValue(int)));
		}
		if(m_InletHandle.getTypename() == "unsigned long")
		{
			m_ValueWidget = new QDoubleSpinBox();
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMinimum(0);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMaximum(ULONG_MAX);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<unsigned long>());
			connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setULongValue(double)));
		}
		else if(m_InletHandle.getTypename() == "long")
		{
			m_ValueWidget = new QDoubleSpinBox();
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMinimum(LONG_MIN);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMaximum(LONG_MAX);
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<long>());
			connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setLongValue(double)));
		}
		else if(m_InletHandle.getTypename() == "float")
		{
			m_ValueWidget = new QDoubleSpinBox();
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<float>());
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMaximum(DBL_MAX);
			connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setFloatValue(double)));
		}
		else if(m_InletHandle.getTypename() == "double")
		{
			m_ValueWidget = new QDoubleSpinBox();
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setValue(m_InletHandle.getCurrentInput().getData<double>());
			dynamic_cast<QDoubleSpinBox*>(m_ValueWidget)->setMaximum(DBL_MAX);
			connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setDoubleValue(double)));
		}
		else if(m_InletHandle.getTypename() == "string")
		{
			m_ValueWidget = new QLineEdit();
			dynamic_cast<QLineEdit*>(m_ValueWidget)->setText(QString::fromStdString(m_InletHandle.getCurrentInput().getData<string>()));
			connect(m_ValueWidget, SIGNAL(textChanged(const QString &)), this, SLOT(setStringValue(const QString &)));
		}

		layout->addWidget( m_ValueWidget );
		setLayout( layout );
	}
	catch(Exception& e)
	{
		cout << e.message() << e.what() << std::endl;
	}
}


// Slots
void BlockInletWidget::setBoolValue(int value)
{
	try
	{
		m_InletHandle.setValue<bool>((bool)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setUCharValue(int value)
{
	try
	{
		m_InletHandle.setValue<unsigned char>((unsigned char)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setCharValue(int value)
{
	try
	{
		m_InletHandle.setValue<char>((char)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setUShortValue(int value)
{
	try
	{
		m_InletHandle.setValue<unsigned short>((unsigned short)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setShortValue(int value)
{
	try
	{
		m_InletHandle.setValue<short>((short)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setUIntValue(double value)
{
	try
	{
		m_InletHandle.setValue<unsigned int>((unsigned int)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setIntValue(int value)
{
	try
	{
		m_InletHandle.setValue<int>(value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setULongValue(double value)
{
	try
	{
		m_InletHandle.setValue<unsigned long>((unsigned long)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setLongValue(double value)
{
	try
	{
		m_InletHandle.setValue<long>((long)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setFloatValue(double value)
{
	try
	{
		m_InletHandle.setValue<float>((float)value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setDoubleValue(double value)
{
	try
	{
		m_InletHandle.setValue<double>(value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}

void BlockInletWidget::setStringValue(const QString & value)
{
	try
	{
		m_InletHandle.setValue<string>(value.toStdString());
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << " " << e.what() << std::endl;
	}
}
