#ifndef __BVHCHANNEL_H__
#define __BVHCHANNEL_H__

#include "BVHAxis.h"
#include <vector>

/** @addtogroup BVH
	@{
*/

namespace chara {


/** @brief Motion capture bone dof evolution

	@remark
		Contains the evolution of a transformation type
		on an axis (degree of freedom) during the animation.
*/
class BVHChannel
{
public:
	//! BVHChannel Type
	enum TYPE
	{
		TYPE_TRANSLATION,
		TYPE_ROTATION,
	};

	//! Constructor
	BVHChannel(TYPE type, AXIS axis);
	//! Destructor
	~BVHChannel();

	//! Check if the channel is a rotation
	bool isRotation(void) const;
	//! Check if the channel is a translation
	bool isTranslation(void) const;
	//! Return the channel type
	TYPE getType(void) const;
	//! Modify the channel type
	void setType(TYPE type);

	//! Return the axis of the channel
	AXIS getAxis(void) const;
	//! Modify the axis of the channel
	void setAxis(AXIS axis);

	//! Return the number of datas
	int getNumData(void) const;
	//! Return the channel data for the i-th frame
	float getData(int i) const;
	//! Modify the channel data for the i-th frame
	void setData(int i, float data);

	//! Set size of the data array
	void setDataSize(int n);

	//! Scale datas
	void scale(float factor);
	//! Rotate datas
	void rotate90(AXIS axis, bool cw);

    //! Compute the multi resolution signal (See [] paper)
    void computeMultiResolution();

    //! return Multiresolution Size
//    unsigned int getMultiResolutionSize() const       { return m_multiR.size(); }

    static unsigned int getMultiResolutionSize()       { return 8; }

    //! Recompute the signal from multi resolution values multiplied bu coeef values
    void regenerateDataFromMultiResolution(const std::vector<float>& coef);

    //! print Multi Resolution data
    void printMultiResData() const;

protected:
	//! The channel Type: translation or rotation
	TYPE m_type;

	//! The channel axis: if rotation
	AXIS m_axis;

	/*! @brief BVHChannel data array
		@remarks m_data[i] contains the data of the channel at the i-th frame.
	*/
	std::vector<float> m_data;

	//! Multi Res data
	std::vector< std::vector<float> > m_multiR;

	//! Multi Res average
	float m_multiRav;
};

} // namespace

/** @}
*/

#endif //__CHANNEL_H__

