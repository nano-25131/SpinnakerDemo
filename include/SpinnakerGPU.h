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

#ifndef TDY_SPINNAKER_GPU_H
#define TDY_SPINNAKER_GPU_H

#include "SpinnakerPlatform.h"
#include "Interface/ISpinnakerGPU.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /**@{*/

    /**
     *  @defgroup SpinnakerGPU_h Spinnaker GPU Class
     */
    /**@{*/

    /**
     * @brief Provides the functionality for the user to post process images on an NVIDIA GPU device.
     */

    class SPINNAKER_API SpinnakerGPU : public ISpinnakerGPU
    {
    public:
        /**
         * Creates SpinnakerGPU context for managing cuda memory allocation and deallocation
         * provided the host image dimensions.
         * 
         * NOTE: The library supports NVIDIA CUDA device with compute capability >= 3.5
         *
         * @return SpinnakerGPU object
         */
        SpinnakerGPU();

        /**
         * Default destructor.
         */
        ~SpinnakerGPU();

        /**
         * Decompresses the source image buffer and returns the result in a new image. 
         * The destination image does not need to be configured in any way before the call is made.
         *
         * @param srcImage The source image from which to convert the image from.
         *
         * @return The decompressed image.
         */
        ImagePtr Decompress(const ImagePtr& srcImage) const;

        /**
         * Decompresses the source image buffer and stores the result in the destination image.
         * The destination image needs to be configured to have the correct buffer size before
         * calling this function. See ResetImage() to setup the correct buffer size according
         * to the decompressed pixel format.
         *
         * @see ResetImage
         *
         * @param srcImage The source image from which to decompress the image from.
         * @param destImage The destination image in which the decompressed image data will be stored.
         */
        void Decompress(const ImagePtr& srcImage, ImagePtr& destImage) const;

    private:
        /**
         * Copy constructor
         */
        SpinnakerGPU(const SpinnakerGPU& processor);

        /**
         * Assignment operator.
         */
        SpinnakerGPU& operator=(const SpinnakerGPU&);
    }; // class SpinnakerGPU

    /**@}*/

    /**@}*/
} // namespace Spinnaker

#endif // TDY_SPINNAKER_GPU_H