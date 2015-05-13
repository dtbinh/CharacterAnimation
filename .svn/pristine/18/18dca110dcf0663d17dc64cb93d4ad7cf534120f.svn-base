#include "BVHJoint.h"
using namespace chara;

namespace chara {


//=============================================================================
BVHJoint::BVHJoint(const std::string& name, BVHJoint* parent, BVH* bvh, float* offset)
		: m_name(name)
		, m_parent(parent)
		, m_bvh(bvh)
{
	assert(bvh!=0);
	assert(offset!=0);

	memcpy(m_offset, offset, 3*sizeof(float));
	bvh->m_joints.push_back(this);
}
//-----------------------------------------------------------------------------
BVHJoint::~BVHJoint()
{
	for (int i=0; i<(int)m_channels.size(); ++i)
		delete m_channels[i];

	for (int i=0; i<(int)m_childs.size(); ++i)
		delete m_childs[i];
}
//-----------------------------------------------------------------------------
std::string BVHJoint::getName(void) const
{ return m_name; }
//-----------------------------------------------------------------------------
void BVHJoint::setName(const std::string& name)
{ m_name = name; }
//-----------------------------------------------------------------------------
void BVHJoint::getOffset(float& x, float& y, float& z) const
{
	x = m_offset[0];
	y = m_offset[1];
	z = m_offset[2];
}
//-----------------------------------------------------------------------------
void BVHJoint::setOffset(float x, float y, float z)
{
	m_offset[0] = x;
	m_offset[1] = y;
	m_offset[2] = z;
}
//-----------------------------------------------------------------------------
int BVHJoint::getNumChannel(void) const
{
	return (int)m_channels.size();
}
//-----------------------------------------------------------------------------
BVHChannel* BVHJoint::getChannel(int i) const
{
	return m_channels[i];
}
//-----------------------------------------------------------------------------
void BVHJoint::SetChannel(int i, BVHChannel* channel)
{
	m_channels[i] = channel;
}
//-----------------------------------------------------------------------------
void BVHJoint::addChannel(BVHChannel* channel)
{
	m_channels.push_back(channel);
}
//-----------------------------------------------------------------------------
BVHChannel* BVHJoint::removeChannel(BVHChannel* channel)
{
	BVHChannel* result=0;

	std::vector<BVHChannel*>::iterator ite=m_channels.begin();
	while (ite!=m_channels.end() && *ite!=channel)
		ite++;

	if (ite!=m_channels.end())
	{
		result = *ite;
		m_channels.erase(ite);
	}

	return result;
}
//-----------------------------------------------------------------------------
BVHChannel* BVHJoint::removeChannel(int i)
{
	BVHChannel* result=0;

	int k=0;
	std::vector<BVHChannel*>::iterator ite=m_channels.begin();
	while (ite!=m_channels.end() && k!=i)
	{
		ite++;
		k++;
	}

	if (ite!=m_channels.end())
	{
		result = *ite;
		m_channels.erase(ite);
	}

	return result;
}
//----------------------------------------------------------------------------
int BVHJoint::getNumChild(void) const
{
	return (int)m_childs.size();
}
//----------------------------------------------------------------------------
BVHJoint* BVHJoint::getChild(int i) const
{
	return m_childs[i];
}
//-----------------------------------------------------------------------------
void BVHJoint::addChild(BVHJoint* BVHJoint)
{
	m_childs.push_back(BVHJoint);
}
//-----------------------------------------------------------------------------
BVHJoint* BVHJoint::getParent(void) const
{
	return m_parent;
}
//----------------------------------------------------------------------------
void BVHJoint::setParent(BVHJoint* parent)
{
	m_parent = parent;
}
//----------------------------------------------------------------------------
BVH* BVHJoint::getBVH(void) const
{
	return m_bvh;
}
//----------------------------------------------------------------------------
void BVHJoint::setBVH(BVH* bvh)
{
	m_bvh = bvh;
}
//----------------------------------------------------------------------------
void BVHJoint::scale(float factor)
{
	// scaling offset
	for (int i=0; i<3; ++i)
		m_offset[i]*=factor;

	// scaling translation channels
	for (int i=0; i<getNumChannel(); ++i)
	{
		BVHChannel* curChannel = getChannel(i);
		if (curChannel->isTranslation())
		{
			curChannel->scale(factor);
		}
	}
}
//----------------------------------------------------------------------------
void BVHJoint::rotate90(AXIS axis, bool cw)
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
		to   = AXIS_Z;
		break;
	case AXIS_Y:
		from = AXIS_Z;
		to   = AXIS_X;
		break;
	case AXIS_Z:
		from = AXIS_X;
		to   = AXIS_Y;
		break;
	default:
		assert(0); // bad parameters
		return;
	}

	// Now, let's transform these axis :
	for (int i=0; i<getNumChannel(); ++i)
	{
		BVHChannel* curChannel = getChannel(i);

		if (curChannel->getAxis() == from)
		{
			// 'from' => 'to'
			curChannel->setAxis(to);
			if (cw)
				curChannel->scale(-1.0f);
		}
		else if (curChannel->getAxis() == to)
		{
			// 'to' => -'from'
			curChannel->setAxis(from);
			if (!cw)
				curChannel->scale(-1.0f);
		}
	}

	// offset switching
	float tmp = m_offset[(int)from];
	if (!cw)
	{
		m_offset[(int)from] = -m_offset[(int)to];
		m_offset[(int)to] = tmp;
	}
	else
	{
		m_offset[(int)from] = m_offset[(int)to];
		m_offset[(int)to] = -tmp;
	}
}
//----------------------------------------------------------------------------
static int g_displayIndex = 0;
std::ostream& operator << (std::ostream& os, const BVHJoint& BVHJoint)
{
	for (int i=0; i<g_displayIndex; ++i)
		os << "  ";
	os << BVHJoint.getName() << " [" << BVHJoint.getNumChannel() << " DOF]";
	os<< " offset=("<<BVHJoint.m_offset[0]<<", "<<BVHJoint.m_offset[1]<<", "<<BVHJoint.m_offset[2]<<")";
	os << std::endl;
	g_displayIndex++;
	for (int i=0; i<BVHJoint.getNumChild(); ++i)
		os << *(BVHJoint.getChild(i));
	g_displayIndex--;

	return os;
}
//-----------------------------------------------------------------------------
BVHJoint::BVHJoint(const std::string& name, BVHJoint* parent, BVH* bvh,
                   std::ifstream& stream, std::vector<BVHChannel*>& channels,
                   bool enableEndSite)
		: m_name(name)
		, m_parent(parent)
		, m_bvh(bvh)
{
	assert(bvh!=0);

	bool result = true;

	bvh->m_joints.push_back(this);

	BVH::expect("{", stream);
	BVH::expect("OFFSET", stream);
	stream >> m_offset[0] >> m_offset[1] >> m_offset[2];

	BVH::expect("CHANNELS", stream);
	int numChannels;
	stream >> numChannels;

	for (int i=0; i<numChannels; ++i)
	{
		std::string typeStr;
		BVHChannel::TYPE type;
		AXIS axis;

		stream >> typeStr;

		if (typeStr == "Xposition")
		{
			type = BVHChannel::TYPE_TRANSLATION;
			axis = AXIS_X;
		}
		else if (typeStr == "Yposition")
		{
			type = BVHChannel::TYPE_TRANSLATION;
			axis = AXIS_Y;
		}
		else if (typeStr == "Zposition")
		{
			type = BVHChannel::TYPE_TRANSLATION;
			axis = AXIS_Z;
		}
		else if (typeStr == "Xrotation")
		{
			type = BVHChannel::TYPE_ROTATION;
			axis = AXIS_X;
		}
		else if (typeStr == "Yrotation")
		{
			type = BVHChannel::TYPE_ROTATION;
			axis = AXIS_Y;
		}
		else if (typeStr == "Zrotation")
		{
			type = BVHChannel::TYPE_ROTATION;
			axis = AXIS_Z;
		}
		else
		{
			std::cerr << "ERROR : bad channel type : '" << typeStr << "'." << std::endl;
			result = false;
			continue;
		}

		BVHChannel* channel = new BVHChannel(type, axis);
		addChannel(channel);
		channels.push_back(channel);
	}

	std::string str;
	stream >> str;

	while (str!="}")
	{
		if (str=="JOINT")
		{
			stream >> str;
			addChild(new BVHJoint(str, this, bvh, stream, channels, enableEndSite));
		}
		else if (str=="End")
		{
			BVH::expect("Site", stream);
			BVH::expect("{", stream);
			BVH::expect("OFFSET", stream);
			float offset[3];
			stream >> offset[0] >> offset[1] >> offset[2];
			if (enableEndSite)
			{
				std::string nameES = getEndSiteName(name);
				addChild(new BVHJoint(nameES, this, bvh, offset));
			}
			BVH::expect("}", stream);
		}
		else
		{
			std::cerr << "ERROR : unexpected word : '" << str << "'." << std::endl;
			result = false;
		}

		stream >> str;
	}

	if (!result)
		std::cerr << "ERROR during the '" << name << "' BVHJoint creation." << std::endl;
}
//----------------------------------------------------------------------------
std::string BVHJoint::getEndSiteName(const std::string& parentName)
{
	std::string result;
	if (parentName=="RWrist")
		result="RHand";
	else if (parentName=="LWrist")
		result="LHand";
	else if (parentName=="RAnkle")
		result="RFoot";
	else if (parentName=="LAnkle")
		result="LFoot";
	else
		result=parentName+"_ES";

	return result;
}
//=============================================================================

} // namespace
