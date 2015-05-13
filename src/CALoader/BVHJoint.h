#ifndef __BVHJOINT_H__
#define __BVHJOINT_H__

#include <string>
#include <vector>
#include <cassert>

#include <iostream>
#include <fstream>

#include "BVH.h"
#include "BVHChannel.h"
#include "BVHAxis.h"

/** @addtogroup BVH
	@{
*/

namespace chara {


/** @brief Motion capture bone and bone animation

	@remark 
		Contains the description and the evolution of a bone.
*/
class BVHJoint
{
	friend class chara::BVH;
public:
	/** @brief Constructor
		@pre bvh!=0
		@pre offset!=0
	*/
	BVHJoint(const std::string& name, BVHJoint* parent, chara::BVH* bvh, float* offset);
	//! Destructor (recursive)
	~BVHJoint();

	//! Return the name of the Joint
	std::string getName(void) const;
	//! Modify the name of the Joint
	void setName(const std::string& name);
	
	//! Return the offset of the joint
	void getOffset(float& x, float& y, float& z) const;
	//! Modify the offset of the joint
	void setOffset(float x, float y, float z);
	
	//! Return the number of channels in the Joint
	int getNumChannel(void) const;
	//! Return the i-th channel of the Joint
	chara::BVHChannel* getChannel(int i) const;
	//! modify the i-th channel of the Joint
	void SetChannel(int i, chara::BVHChannel* channel);
	//! Add channel
	void addChannel(chara::BVHChannel* channel);
	//! Remove channel
	chara::BVHChannel* removeChannel(chara::BVHChannel* channel);
	//! Remove channel
	chara::BVHChannel* removeChannel(int i);
	
	//! Return the number of child
	int getNumChild(void) const;
	//! Return a child
	chara::BVHJoint* getChild(int i) const;
	//! Add child
	void addChild(chara::BVHJoint* joint);
	
	//! Return the parent of the Joint
	BVHJoint* getParent(void) const;
	//! Modify the parent of the joint
	void setParent(chara::BVHJoint* parent);
	
	//! Return the bvh
	chara::BVH* getBVH(void) const;
	//! Modify the bvh
	void setBVH(chara::BVH* bvh);
	
	//! Scaling the joint
	void scale(float factor);
	//! Rotate the bvh (recursive)
	void rotate90(AXIS axis, bool cw);
	
	//! dump (recursive)
	friend std::ostream& operator << (std::ostream& os, const BVHJoint& joint);

protected:
	/** @brief Constructor from file stream (recursive)
		@pre bvh!=0
	*/
	BVHJoint(const std::string& name, BVHJoint* parent, chara::BVH* bvh,
		  std::ifstream& stream, std::vector<BVHChannel*>& channels, 
		  bool enableEndSite);
	//! Return the best end name from it parent e.g. RHand from RWrist
	static std::string getEndSiteName(const std::string& parentName);
			
	//! Joint name
	std::string m_name;
	//! Offset vector
	float m_offset[3];

	//! Channels
	std::vector<chara::BVHChannel*> m_channels;
	
	//! Childs
	std::vector<chara::BVHJoint*> m_childs;
	//! The parent
	chara::BVHJoint* m_parent;
	
	//! The BVH
	chara::BVH* m_bvh;
};

} // namespace

/** @}
*/

#endif //__JOINT_H__
