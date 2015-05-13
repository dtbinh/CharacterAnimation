#include "BVH.h"
#include "BVHJoint.h"

namespace chara {


//=============================================================================
BVH::BVH()
 : m_numFrames(0)
 , m_frameTime(0)
 , m_root(0)
{
}
//-----------------------------------------------------------------------------
BVH::BVH(const std::string& filename, bool enableEndSite)
{
    std::ifstream stream(filename.c_str());

    if(stream.is_open())
    {
        //std::cout << "Parsing '" << filename << "'...";

        expect("HIERARCHY", stream);
        expect("ROOT", stream);

        std::string rootName;
        stream >> rootName;

        std::vector<BVHChannel*> channels;
        m_root = new BVHJoint(rootName, 0, this, stream, channels, enableEndSite); // recursive

        expect("MOTION", stream);
        expect("Frames:", stream);
        stream >> m_numFrames;

        expect("Frame", stream);
        expect("Time:", stream);
        stream >> m_frameTime;

        int i,j;
        for(j=0; j<(int)channels.size(); ++j)
            channels[j]->setDataSize(m_numFrames);

        for(i=0; i<(int)m_numFrames; ++i)
        {
            for(j=0; j<(int)channels.size(); ++j)
            {
                float data;
                stream >> data;
                channels[j]->setData(i, data);
            }
        }

//        for(j=0;j<(int)channels.size();++j)
//        {
//            channels[j]->computeMultiResolution();
//
//            channels[0]->printMultiResData();
//            std::vector<float> coef;
//            for(unsigned int i=0;i<channels[0]->getMultiResolutionSize();++i)
//                coef.push_back(1.0f);
//            channels[0]->regenerateDataFromMultiResolution(coef);
//            printf("\n\n\n");
//            channels[0]->printMultiResData();
//            printf("\n\n\n");
//        }
    }
    else // file==0
    {
        // can't open m_filename
        std::cerr << "ERROR : Unable to open " << filename << std::endl;
		assert(0);
    }
}
//-----------------------------------------------------------------------------
BVH::~BVH()
{
    delete m_root;
}
//-----------------------------------------------------------------------------
int BVH::getNumFrame(void) const
{
  return m_numFrames;
}
//-----------------------------------------------------------------------------
float BVH::getFrameTime(void) const
{
  return m_frameTime;
}
//-----------------------------------------------------------------------------
BVHJoint* BVH::getRoot(void) const
{
  return m_root;
}
//-----------------------------------------------------------------------------
void BVH::setRoot(BVHJoint* joint)
{
  m_root = joint;
}
//-----------------------------------------------------------------------------
int BVH::getNumJoint(void) const
{
    return (int)m_joints.size();
}
//-----------------------------------------------------------------------------
BVHJoint* BVH::getJoint(int i) const
{
    if(i<getNumJoint())
        return m_joints[i];
    else
        return NULL;
}
//----------------------------------------------------------------------------
BVHJoint* BVH::getJoint(const std::string& name) const
{
    int i=0;
    while(i<getNumJoint() && getJoint(i)->getName()!=name)
        ++i;

    if(i<getNumJoint())
        return getJoint(i);
    else
        return 0;
}

//----------------------------------------------------------------------------
int BVH::getJointNumber(const std::string& name) const
{
    int i=0;
    while(i<getNumJoint() && getJoint(i)->getName()!=name)
        ++i;

    if(i<getNumJoint())
        return i;
    else
        return -1;
}


//----------------------------------------------------------------------------
void BVH::scaleAnimation(float factor)
{
    assert(factor>0);
    m_frameTime*=factor;
}
//----------------------------------------------------------------------------
void BVH::scaleSkeleton(float factor)
{
    assert(factor>0);

    for(int i=0; i<getNumJoint(); ++i)
        getJoint(i)->scale(factor);
}
//----------------------------------------------------------------------------
void BVH::rotate90(chara::AXIS axis, bool cw)
{
    for(int i=0; i<getNumJoint(); ++i)
        getJoint(i)->rotate90(axis, cw);
}
//----------------------------------------------------------------------------
bool BVH::expect(const std::string& word, std::ifstream& stream)
{
    bool result=true;

    std::string str;
    stream >> str;

    if(str!=word)
    {
        std::cerr << "ERROR : Unexpected string in the file stream : '" << str <<
            "' have been founded where '" << word << "' was expected." << std::endl;
        result =  false;
    }

    return result;
}
//============================================================================
std::ostream& operator << (std::ostream& os, const BVH& bvh)
{
    os << (*bvh.getRoot())
       << std::endl
       << "Number of frames : " << bvh.getNumFrame() << std::endl
       << "Animation time   : " << bvh.getFrameTime()*(bvh.getNumFrame()-1) << " s" << std::endl;

    return os;
}
//============================================================================

void BVH::multiResEditAnimation(const std::vector<float>& coef)
{
    unsigned int i;
    int j;
    for(i=0;i<m_joints.size();++i)
    {
        for(j=0;j<m_joints[i]->getNumChannel();++j)
            m_joints[i]->getChannel(j)->regenerateDataFromMultiResolution(coef);
    }
}


} // namespace