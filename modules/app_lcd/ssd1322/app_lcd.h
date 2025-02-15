// $Id: app_lcd.h 1222 2011-06-23 21:12:04Z tk $
/*
 * Header file for application specific LCD Driver
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _APP_LCD_H
#define _APP_LCD_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

// supported: 1 (more toDo)
#ifndef APP_LCD_NUM_X
#define APP_LCD_NUM_X 1
#endif

// supported: 1 (more toDo)
#ifndef APP_LCD_NUM_Y
#define APP_LCD_NUM_Y 1
#endif

// don't change these values for this GLCD type
#define APP_LCD_WIDTH 256
#define APP_LCD_HEIGHT 64
#define APP_LCD_COLOUR_DEPTH 4
// We need 256*64 pixel, for 1bit legacy bitmaps a pixel is 1 bit
// size of u8 array is 256*64/8 = 2048
#define APP_LCD_1BITMAP_SIZE ((APP_LCD_NUM_X*APP_LCD_WIDTH * APP_LCD_NUM_Y*APP_LCD_HEIGHT * 1) / 8)
// We need 256*64 pixel, for SSD1322 a pixel is 4 bits
// size of u8 array is 256*64/2 = 8192
#define APP_LCD_4BITMAP_SIZE ((APP_LCD_NUM_X*APP_LCD_WIDTH * APP_LCD_NUM_Y*APP_LCD_HEIGHT * APP_LCD_COLOUR_DEPTH) / 2)

/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////


// Graphics, bitmaps fusion mode
typedef enum{
  REPLACE = 0,
  NOBLACK,
  OR,
  AND,
  XOR
}app_lcd_fusion_t;

// bitmap color depth
typedef enum{
  Is1BIT = 1,
  Is4BIT = APP_LCD_COLOUR_DEPTH
}app_lcd_color_depth_t;


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

// hooks to MIOS32_LCD
extern s32 APP_LCD_Init(u32 mode);
extern s32 APP_LCD_Data(u8 data);
extern s32 APP_LCD_Cmd(u8 cmd);
extern s32 APP_LCD_Clear(void);

extern s32 APP_LCD_CursorSet(u16 column, u16 line);
extern s32 APP_LCD_GCursorSet(u16 x, u16 y);

extern s32 APP_LCD_FontInit(u8 *font, app_lcd_color_depth_t colour_depth);    // new
extern s32 APP_LCD_SpecialCharInit(u8 num, u8 table[8]);
extern s32 APP_LCD_PrintChar(mios32_lcd_bitmap_t bitmap, float luma, s16 x, s16 y, app_lcd_fusion_t fusion, char c);   // new
extern s32 APP_LCD_PrintString(mios32_lcd_bitmap_t bitmap, float luma, s16 x, s16 y, app_lcd_fusion_t fusion, const char *str);   // new
extern s32 APP_LCD_PrintFormattedString(mios32_lcd_bitmap_t bitmap, float luma, s16 x, s16 y, app_lcd_fusion_t fusion, const char *format, ...);   //new

extern s32 APP_LCD_BColourSet(u32 rgb);   // used for: rectDraw fill.
extern s32 APP_LCD_FColourSet(u32 rgb);   // used for: rectDraw border, pixelSet, legacy 2 native PrintChar/Fusion...

extern mios32_lcd_bitmap_t APP_LCD_BitmapInit(u8 *memory, u16 width, u16 height, u16 line_offset, app_lcd_color_depth_t colour_depth);   //new
extern s32 APP_LCD_BitmapPixelSet(mios32_lcd_bitmap_t bitmap, u16 x, u16 y, u32 colour);
extern s32 APP_LCD_BitmapByteSet(mios32_lcd_bitmap_t bitmap, s16 x, s16 y, u8 value);
extern s32 APP_LCD_Bitmap4BitLuma(mios32_lcd_bitmap_t bitmap, s16 x, s16 y, u16 width, u16 height, float luma);   // new
extern s32 APP_LCD_BitmapFusion(mios32_lcd_bitmap_t src_bmp, float src_luma, mios32_lcd_bitmap_t dst_bmp, s16 x, s16 y, app_lcd_fusion_t fusion);   // new

extern s32 APP_LCD_BitmapPrint(mios32_lcd_bitmap_t bitmap);


/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////
extern u8 app_lcd_back_grayscale;
extern u8 app_lcd_fore_grayscale;

#endif /* _APP_LCD_H */
