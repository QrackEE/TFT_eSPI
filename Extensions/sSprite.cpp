/******************************************************************************
 * @file    sSprite.cpp
 * @author  QrackEE
 * @date    2020-09-10
 * @brief   <Provide some short description here>
 * @note    <Detailed description>
 *****************************************************************************/
//=============================================================================
//                                  Libraries
//=============================================================================
#include "TFT_sSprite.h"


//=============================================================================
//                                   Defines
//=============================================================================


//=============================================================================
//                           Extern variable definitions
//=============================================================================


//=============================================================================
//                                Private Types
//=============================================================================


//=============================================================================
//                               Private variables
//=============================================================================


//=============================================================================
//                        Private function declarations (optional)
//=============================================================================


//=============================================================================
//                             Private function definitions
//=============================================================================

uint32_t TFT_sSprite::bufferSizeRequired(
  uint16_t w, uint16_t h, uint8_t frames, uint8_t bitsPerPixel) {
  if (frames > 2) frames = 2;
  if (frames < 1) frames = 1;

  switch(bitsPerPixel)
  {
    case 16:
      w = w * sizeof(uint16_t);
      break;
    case 8:
      // keep as-is
      break;
    case 4:
      w = (w+1) & 0xFFFE; // width needs to be multiple of 2, with an extra "off screen" pixel
      break;
    case 1:
      w = (w+7) & 0xFFF8; // width should be the multiple of 8 bits to be compatible with epdpaint
      break;
    default:
      // UNHANDLED PIXEL TYPE
      return UINT32_MAX;
  }

  return (w * h * frames + frames);
}


//=============================================================================
//                             Public function definitions
//=============================================================================


TFT_sSprite::~TFT_sSprite(void) {
  if (_colorMap != nullptr)
  {
    free(_colorMap);
	_colorMap = nullptr;
  }

  if (_created)
  {
    _img8_1 = nullptr;
    _img8 = nullptr;
	_created = false;
  }

#ifdef SMOOTH_FONT
  if(this->fontLoaded) this->unloadFont();
#endif
}

void* TFT_sSprite::callocSprite(
  int16_t width, int16_t height, uint8_t frames) {

  if (_staticBufferSize >= bufferSizeRequired(width, height, frames, _bpp))
  {
    if(_bpp == 4)
    {
      _iwidth = (width+1) & 0xFFFE; // width needs to be multiple of 2, with an extra "off screen" pixel
    }
    else if(_bpp == 1)
    {
      _iwidth = (width+7) & 0xFFF8; // width should be the multiple of 8 bits to be compatible with epdpaint
      _bitwidth = width;
    }

    return (void*)_staticBuffer;
  }
  else
  {
    return NULL;
  }
}

//========= NO CODE BELOW THIS LINE ========= NO CODE BELOW THIS LINE =========