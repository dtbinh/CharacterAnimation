#include "BVHChannel.h"
#include <cassert>
#include <iostream>
#include <stdio.h>
using namespace std;


namespace chara {

//=============================================================================
BVHChannel::BVHChannel(BVHChannel::TYPE type, AXIS axis)
		: m_type(type)
		, m_axis(axis)
{
}
//-----------------------------------------------------------------------------
BVHChannel::~BVHChannel()
{
}
//-----------------------------------------------------------------------------
bool BVHChannel::isRotation(void) const
{
	return m_type==TYPE_ROTATION;
}
//-----------------------------------------------------------------------------
bool BVHChannel::isTranslation(void) const
{
	return m_type==TYPE_TRANSLATION;
}
//-----------------------------------------------------------------------------
BVHChannel::TYPE BVHChannel::getType(void) const
{
	return m_type;
}
//-----------------------------------------------------------------------------
void BVHChannel::setType(BVHChannel::TYPE type)
{
	m_type = type;
}
//-----------------------------------------------------------------------------
AXIS BVHChannel::getAxis(void) const
{
	return m_axis;
}
//-----------------------------------------------------------------------------
void BVHChannel::setAxis(AXIS axis)
{
	m_axis = axis;
}
//-----------------------------------------------------------------------------
int BVHChannel::getNumData(void) const
{
	return m_data.size();
}
//-----------------------------------------------------------------------------
float BVHChannel::getData(int i) const
{
	if ((i<0) || ( ((unsigned int)(i))>=m_data.size())) return 0;
	return m_data[i];
}
//-----------------------------------------------------------------------------
void BVHChannel::setData(int i, float data)
{
    //if (i<m_data.size()) m_data.resize(i);
	m_data[i] = data;
}
//-----------------------------------------------------------------------------
void BVHChannel::setDataSize(int n)
{
    m_data.resize(n);
}
//-----------------------------------------------------------------------------
void BVHChannel::scale(float factor)
{
	for (int i=0; i<getNumData(); ++i)
		m_data[i]*=factor;
}
//-----------------------------------------------------------------------------
void BVHChannel::rotate90(AXIS axis, bool cw)
{
	// For a 90° ccw rotation transforms
	// an axis 'from' to another axis 'to' and 'to' to -'from'.
	AXIS from;
	AXIS to;
	// 'from' and 'to' depend on the axis of the rotation 'axis'.
	// Let's find these axis :
	switch (axis)
	{
	case AXIS_X:
		from = AXIS_Y;
		to	 = AXIS_Z;
		break;
	case AXIS_Y:
		from = AXIS_Z;
		to	 = AXIS_X;
		break;
	case AXIS_Z:
		from = AXIS_X;
		to	 = AXIS_Y;
		break;
	default:
		return;
	}

	if (getAxis() == from)
	{
		// 'from' => 'to'
		setAxis(to);
		if (cw)
			scale(-1.0f);
	}
	else if (getAxis() == to)
	{
		// 'to' => -'from'
		setAxis(from);
		if (!cw)
			scale(-1.0f);
	}
}


//=============================================================================
void BVHChannel::computeMultiResolution()
{
    m_multiR.clear();

    assert( m_data.size()==8 );

    int i;
    unsigned int j;
    float m;
    i = 0;
    vector<float> av(m_data), avav, dat;
    while( av.size()>1 )
    {
        dat.clear();
        avav.clear();
        for(j=0;j<av.size();++j)
        {
            m = 0.5f*(av[j]+av[j+1]);
            avav.push_back( m );

            dat.push_back( av[j]-m );
            ++j; dat.push_back( av[j]-m );
        }
        av = avav;
        m_multiR.push_back( dat );

        if (av.size()==1) m_multiRav = av[0];
    }
    printf("BVHChannel::computeMultiResolution(): m_dataSize=%d NmultiRes=%d\n", m_data.size(), m_multiR.size() );
}


void BVHChannel::regenerateDataFromMultiResolution(const std::vector<float>& coef)
{
    assert( coef.size()==m_multiR.size() );
    vector<float> av;
    av.push_back( m_multiRav );
    unsigned int j;
    int i;
    for(i=m_multiR.size()-1; i>=0 ; --i)
    {
        vector<float>& dat(m_multiR[i]);
        m_data.clear();
        for(j=0;j<av.size();++j)
        {
            m_data.push_back( av[j]+coef[i]*dat[2*j] );
            m_data.push_back( av[j]+coef[i]*dat[2*j+1] );
        }
        av = m_data;
//        printf("i=%d avSize=%d\n", i, av.size());
    }
}


void BVHChannel::printMultiResData() const
{
    unsigned int i,j;


    cout<<"DATA size="<<m_data.size()<<endl;
    for(j=0;j<m_data.size();++j)
    {
        cout<<m_data[j]<<" ";
    }
    cout<<endl;

    cout<<"MultiR"<<endl;
    for(i=0;i<m_multiR.size();++i)
    {
        const vector<float>& dat(m_multiR[i]);
        printf("%d (size=%d) : ",i, dat.size() );
        for(j=0;j<dat.size();++j)
        {
            cout<<dat[j]<<" ";
        }
        cout<<endl;
    }
    cout<<"av="<<m_multiRav<<endl<<endl;
}

} // namespace
