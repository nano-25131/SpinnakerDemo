//=============================================================================
// Copyright (c) 2025 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef TDY_SPINNAKER_ISPINNAKERGPU_H
#define TDY_SPINNAKER_ISPINNAKERGPU_H

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /**@{*/

    /**
     *  @defgroup ISpinnakerGPU_h Spinnaker GPU Interface
     */

    /**@{*/

    /**
     * @brief The interface file for SpinnakerGPU class.
     */
    class SPINNAKER_API ISpinnakerGPU
    {
    public:
        virtual ~ISpinnakerGPU(void) {};

        virtual ImagePtr Decompress(const ImagePtr& srcImage) const = 0;
        virtual void Decompress(const ImagePtr& srcImage, ImagePtr& destImage) const = 0;

    protected:
        struct SpinnakerGPUData; // Forward declaration
        SpinnakerGPUData* m_pSpinnakerGPUData;

        ISpinnakerGPU() {};
        ISpinnakerGPU(const ISpinnakerGPU&) {};
        ISpinnakerGPU& operator=(const ISpinnakerGPU&);
    };

    /**@}*/

    /**@}*/

} // namespace Spinnaker

#endif // TDY_SPINNAKER_ISPINNAKERGPU_H