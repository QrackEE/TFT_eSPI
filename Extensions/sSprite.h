/******************************************************************************
 * @file    sSprite.h
 * @author  QrackEE
 * @date    2020-09-10
 * @brief   <Provide some short description here>
 * @note    <Detailed description>
 *****************************************************************************/
#ifndef _TFT_SSPRITE_H_
#define _TFT_SSPRITE_H_
//=============================================================================
//                                  Libraries
//=============================================================================
#include <stdint.h>
#include <TFT_eSPI.h>

//=============================================================================
//                                   Defines
//=============================================================================


//=============================================================================
//                                    Types
//=============================================================================

class TFT_sSprite : public TFT_eSprite {
  public:
    explicit TFT_sSprite(
      TFT_eSPI *tft, 
      uint16_t *buffer,
      uint32_t bufferSize) : 
        TFT_eSprite(tft),
        _staticBuffer(buffer),
        _staticBufferSize(bufferSize) {};

    ~TFT_sSprite(void);

    static uint32_t bufferSizeRequired(
      uint16_t w, uint16_t h, uint8_t frames, uint8_t bitsPerPixel);

  private:
    TFT_eSPI *_tft;
    uint16_t *_staticBuffer;
    uint32_t _staticBufferSize;

             // Reserve memory for the Sprite and return a pointer
    void*    callocSprite(int16_t width, int16_t height, uint8_t frames = 1);
    
};

//=============================================================================
//                               Shared variables
//=============================================================================


//=============================================================================
//                          Exposed function declarations
//=============================================================================


#endif /* _TFT_SSPRITE_H_ */
//========= NO CODE BELOW THIS LINE ========= NO CODE BELOW THIS LINE =========