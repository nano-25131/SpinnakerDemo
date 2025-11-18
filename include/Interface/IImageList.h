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

#ifndef FLIR_SPINNAKER_IIMAGELIST_H
#define FLIR_SPINNAKER_IIMAGELIST_H

#include "Image.h"
#include "ImagePtr.h"

namespace Spinnaker
{
    class ImageList;
    class ImagePtr;
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /**@{*/

    /**
     *  @defgroup IImageList_h IImageList Class
     */

    /**@{*/

    /**
     * @brief The interface file for ImageList class.
     */

    class SPINNAKER_API IImageList
    {
      public:
        virtual ~IImageList(void){};

        virtual ImagePtr operator[](unsigned int index) = 0;
        virtual unsigned int GetSize() const = 0;
        virtual ImagePtr GetByIndex(unsigned int index) const = 0;
        virtual ImagePtr GetByPixelFormat(PixelFormatEnums pixelFormat) const = 0;
        virtual ImagePtr GetByStreamIndex(const uint64_t streamIndex) const = 0;
        virtual ImagePtr GetByPayloadType(const ImagePayloadType payloadType) const = 0;
        virtual void Clear() = 0;
        virtual void RemoveByIndex(unsigned int index) = 0;
        virtual void RemoveByPixelFormat(PixelFormatEnums pixelFormat) = 0;
        virtual void RemoveByStreamIndex(const uint64_t streamIndex) = 0;
        virtual void RemoveByPayloadType(const ImagePayloadType payloadType) = 0;
        virtual void Append(const ImageList& list) = 0;
        virtual void Add(ImagePtr image) = 0;
        virtual void Release() = 0;
        virtual void Save(const char* filename) = 0;

      protected:
        friend class ImageListImpl;
        struct ImageListData; // Forward declaration
        ImageListData* m_pImageListData;

        IImageList(){};
        IImageList(const IImageList&){};
        IImageList& operator=(const IImageList&);
    };

    /**@}*/

    /**@}*/

} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IIMAGELIST_H