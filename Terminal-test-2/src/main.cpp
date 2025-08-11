#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <PINS_JC4827W543.h>



Arduino_Canvas *canvas;
// Arduino_Canvas *lapTimesCanvas;

uint16_t lightGrey = canvas->color565(33,33,33); // Light grey color
uint16_t offWhite = canvas->color565(128,122,109); // Off-white color
uint16_t softBlue = canvas->color565(33,91,159); // Soft blue color

// 'Flag_Icon', 14x14px
const unsigned char epd_bitmap_Flag_Icon [] PROGMEM = {
	0xc0, 0x70, 0xf1, 0xcc, 0xbf, 0x34, 0xb3, 0x34, 0xcc, 0xcc, 0xcc, 0xcc, 0xb3, 0x34, 0xb3, 0x34, 
	0xcc, 0xcc, 0xcc, 0xfc, 0xb3, 0x8c, 0x8e, 0x00, 0x80, 0x00, 0x80, 0x00
};
// 'Headlights_icon', 14x14px
const unsigned char epd_bitmap_Headlights_icon [] PROGMEM = {
	0x0e, 0x00, 0x32, 0x00, 0x41, 0x60, 0x41, 0x1c, 0x81, 0x00, 0x81, 0x60, 0x81, 0x1c, 0x81, 0x00, 
	0x81, 0x60, 0x81, 0x1c, 0x41, 0x00, 0x41, 0x60, 0x32, 0x1c, 0x0e, 0x00
};
// 'Tyre_R_icon', 12x16px
const unsigned char epd_bitmap_Tyre_R_icon [] PROGMEM = {
	0x0f, 0xc0, 0x10, 0x20, 0x20, 0x10, 0x20, 0x10, 0xa0, 0x10, 0xa0, 0x10, 0xa0, 0x10, 0xa0, 0x10, 
	0xa0, 0x10, 0xa0, 0x10, 0xa0, 0x10, 0xa0, 0x10, 0x20, 0x10, 0x20, 0x10, 0x10, 0x20, 0x0f, 0xc0
};
// 'Wipers_Icon', 14x14px
const unsigned char epd_bitmap_Wipers_Icon [] PROGMEM = {
	0x00, 0x00, 0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x50, 0x08, 0x88, 0x04, 0x88, 0x04, 0x84, 0x04, 
	0x44, 0x08, 0x22, 0x10, 0x17, 0xa0, 0x09, 0x40, 0x01, 0x00, 0x00, 0x00
};
// 'tyre_L_icon', 12x16px
const unsigned char epd_bitmap_tyre_L_icon [] PROGMEM = {
	0x3f, 0x00, 0x40, 0x80, 0x80, 0x40, 0x80, 0x40, 0x80, 0x50, 0x80, 0x50, 0x80, 0x50, 0x80, 0x50, 
	0x80, 0x50, 0x80, 0x50, 0x80, 0x50, 0x80, 0x50, 0x80, 0x40, 0x80, 0x40, 0x40, 0x80, 0x3f, 0x00
};
// 'checkered_flag', 68x43px
const unsigned char epd_bitmap_checkered_flag [] PROGMEM = {
	0x3f, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0x7f, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 
	0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 
	0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 
	0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 
	0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 
	0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 
	0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 
	0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 
	0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 
	0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 
	0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 
	0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 
	0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 
	0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 
	0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 
	0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 
	0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 
	0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 
	0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 
	0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0, 
	0x01, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 
	0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 
	0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 
	0xf0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 0x00, 0x3f, 0xe0, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0xfe, 
	0x00, 0x3f, 0xc0
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 240)
const int epd_bitmap_allArray_LEN = 6;
const unsigned char* epd_bitmap_allArray[6] = {
	epd_bitmap_Flag_Icon,
	epd_bitmap_Headlights_icon,
	epd_bitmap_Tyre_R_icon,
	epd_bitmap_Wipers_Icon,
	epd_bitmap_tyre_L_icon,
  epd_bitmap_checkered_flag
};



// Screen res: 480x272

void drawBackground() {

  // Outer border ==============================================================

  canvas->drawRoundRect(0,17,480,255,3,WHITE); // Outer border

  // Fuel box (top left)=======================================================
  canvas->drawRoundRect(3, 21, 199, 44, 3, WHITE);
  
  // Add labels for fuel box
  canvas->setTextSize(1);
  canvas->setTextColor(WHITE);
    
  // FUEL label - aligned with number (10px from left)
  canvas->setCursor(13, 28);
  canvas->print("FUEL");
    
  // AVG label - centered in middle section
  const int sectionWidth = 199 / 3;
  canvas->setCursor(3 + sectionWidth + 10, 28);
  canvas->print("AVG");
    
  // LAPS label - centered in last section
  canvas->setCursor(3 + (sectionWidth * 2) + 10, 28);
  canvas->print("LAPS");

  // TC/TC_CUT and MAP boxes (Bottom Left) ================================================
  const int bottomBoxY = 220;  // Same Y position for all bottom boxes
  
  // Calculate widths for bottom left boxes to match right section (199px total)
  const int tcBoxWidth = 94;  // Box for TC/TC_CUT
  const int mapBoxWidth = 85;  // Box for MAP
  const int bottomLeftPadding = 4;  // Padding between boxes
  
  // Left box - filled light blue with TC/TC_CUT labels
  canvas->fillRoundRect(19, bottomBoxY, tcBoxWidth, 48, 3, softBlue);
  
  // Add TC and CUT labels stacked
  canvas->setTextSize(2);
  canvas->setTextColor(BLACK);
  canvas->setCursor(35, bottomBoxY + 6);  // Top position for TC
  canvas->print("TC");
  canvas->setCursor(31, bottomBoxY + 28);  // Bottom position for CUT
  canvas->print("CUT");
  
  // Right box (MAP) - filled green
  canvas->fillRoundRect(3 + tcBoxWidth + bottomLeftPadding+16, bottomBoxY, mapBoxWidth, 48, 3, GREEN);
  
  // Add MAP label
  canvas->setTextColor(BLACK);
  canvas->setCursor(3 + tcBoxWidth + bottomLeftPadding + 20, bottomBoxY + (48 - 14)/2);
  canvas->print("MAP");

  // Calculate centers for value boxes
  const int tcBoxCenter = tcBoxWidth / 2;  // Center of TC/CUT box
  const int mapLabelWidth = 45;  // Approximate width of "MAP" text at size 2
  const int mapBoxCenter = 3 + tcBoxWidth + bottomLeftPadding + mapLabelWidth + (mapBoxWidth - mapLabelWidth) / 2;  // Center in remaining space after MAP text
  
  // Add black background boxes for values
  // TC value box (centered in TC box)
  canvas->fillRoundRect(3 + tcBoxCenter +22, bottomBoxY + 4, 35, 18, 3, BLACK);
  // TC_CUT value box (centered in TC box)
  canvas->fillRoundRect(3 + tcBoxCenter +22, bottomBoxY + 26, 35, 18, 3, BLACK); 
  // MAP value box (centered in remaining space after MAP text)
  canvas->fillRoundRect(mapBoxCenter - 4, bottomBoxY + 4, 35, 40, 3, BLACK);

  // BB and ABS ======================================================================

  // BOTTOM RIGHT boxes (with 4px padding between them)
  const int bottomBoxWidth = (199-16-4)/2;  // Total width minus padding divided by 2
    
  // Left box - filled red with black BB label
  canvas->fillRoundRect(278, bottomBoxY, bottomBoxWidth + 12, 48, 3, RED);  // Made BB box 12px wider
  
  // Add BB label
  canvas->setTextSize(2);
  canvas->setTextColor(BLACK);
  // BB text is 2 characters * 15px = 30px wide at size 3
  const int bbTextWidth = 30;  // "BB" width at size 2 (15px per character)
  canvas->setCursor(278 + 4, bottomBoxY + (48 - 14)/2); // 4px left margin
  canvas->print("BB");
    
  // Right box - filled yellow with black ABS label
  canvas->fillRoundRect(278 + bottomBoxWidth + 16, bottomBoxY, bottomBoxWidth - 12, 48, 3, YELLOW);  // Narrower ABS box
  
  // Add ABS label
  canvas->setTextColor(BLACK);
  // ABS text is 3 characters * 15px = 45px wide at size 3
  const int absTextWidth = 45;  // "ABS" width at size 2 (15px per character)
  canvas->setCursor(278 + bottomBoxWidth + 20, bottomBoxY + (48 - 14)/2); // 4px left margin from yellow box
  canvas->print("ABS");

  // Add black background box with 4px gap from BB text
  const int bbBoxX = 278 + 4 + bbTextWidth + 4;  // Base X + left padding + text width + gap
  const int bbBoxWidth = (bottomBoxWidth + 12) - (4 + bbTextWidth + 4 + 4);  // Total width - (left padding + text + gap + right padding)
  canvas->fillRoundRect(bbBoxX-8, bottomBoxY + 4, bbBoxWidth+8, 48 - 8, 3, BLACK);

  // Add black background box for ABS section with proper right padding
  const int absBoxX = 278 + bottomBoxWidth + 20 + absTextWidth + 4;  // Base X + left padding + text width + gap
  const int absBoxWidth = (bottomBoxWidth - 12) - (4 + absTextWidth + 4 + 4);  // Total width - (left padding + text + gap + right padding)
  canvas->fillRoundRect(absBoxX-10, bottomBoxY + 4, absBoxWidth+10, 48 - 8, 3, BLACK);

  // placehodler boxes ========================================================
  // TOP RIGHT box (POS-LAP-TIME)
  canvas->drawRoundRect(278, 21, 199, 44, 3, WHITE);

  // LAP TIMES box (moved down 4px)
  canvas->drawRoundRect(278, 69, 199-16, 147, 3, WHITE);

  // LEFT MFB ====================================================================
  // Draw Box
  canvas->drawRoundRect(19, 69, 199-16, 147, 3, WHITE);

  // Car Ahead Graphics------------------------------------------------------------
  canvas->setTextSize(1);
  canvas->setTextColor(WHITE);
  canvas->setCursor(19 + 4+6, 69 + 8+2); // 4px padding
  canvas->print("AHEAD:");

  // Car Behind Graphics----------------------------------------------------------
  canvas->fillRect(19,73+14+2+4, 199-16, 14+8, WHITE);;
  canvas->setTextSize(1);
  canvas->setTextColor(BLACK);
  canvas->setCursor(19+4, 101);
  canvas->print("BEHIND:");
  
  // Draw tyre icons and data =======================================================================================
  int centreX = 111;
  int centreY = 165;

  int middleOffsetH = 26; // Offset for middle tyre icons
  int middleOffsetV = 40; // Offset for vertical alignment

  int tyreIconWidth = 14;
  int tyreIconHeight = 26;
  int diskGap = 3; // Gap between tyre icon and disk
  int diskHeight = 16; // Height of the disk

  // Draw tyre icons
  canvas->fillRoundRect(centreX - middleOffsetH - tyreIconWidth/2,centreY - middleOffsetH - tyreIconHeight/2, tyreIconWidth, tyreIconHeight, 3, WHITE);// Top left tyre
  canvas->fillRoundRect(centreX + middleOffsetH - tyreIconWidth/2,centreY - middleOffsetH - tyreIconHeight/2, tyreIconWidth, tyreIconHeight, 3, WHITE);// Top right tyre
  canvas->fillRoundRect(centreX - middleOffsetH - tyreIconWidth/2,centreY + middleOffsetH - tyreIconHeight/2, tyreIconWidth, tyreIconHeight, 3, WHITE);// Bottom left tyre
  canvas->fillRoundRect(centreX + middleOffsetH - tyreIconWidth/2,centreY + middleOffsetH - tyreIconHeight/2, tyreIconWidth, tyreIconHeight, 3, WHITE);// Bottom right tyre

  canvas->drawFastVLine(centreX - middleOffsetH + tyreIconWidth/2 + diskGap,centreY - middleOffsetH - diskHeight/2, diskHeight, WHITE); // Top Left disk.
  canvas->drawFastVLine(centreX + middleOffsetH - tyreIconWidth/2 - diskGap,centreY - middleOffsetH - diskHeight/2, diskHeight, WHITE); // Top Right disk.
  canvas->drawFastVLine(centreX - middleOffsetH + tyreIconWidth/2 + diskGap,centreY + middleOffsetH - diskHeight/2, diskHeight, WHITE); // Bottom Left disk.
  canvas->drawFastVLine(centreX + middleOffsetH - tyreIconWidth/2 - diskGap,centreY + middleOffsetH - diskHeight/2, diskHeight, WHITE); // Bottom Right disk.
}

void drawRevLights(int revs){
  // canvas->fillRoundRect(1,0,28,16,3,GREEN);
  // canvas->fillRoundRect(31,0,28,16,3,GREEN);
  // canvas->fillRoundRect(61,0,28,16,3,GREEN);
  // canvas->fillRoundRect(91,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(121,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(151,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(181,0,28,16,3,RED);
  // canvas->fillRoundRect(211,0,28,16,3,RED);

  // canvas->fillRoundRect(241,0,28,16,3,RED);
  // canvas->fillRoundRect(271,0,28,16,3,RED);
  // canvas->fillRoundRect(301,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(331,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(361,0,28,16,3,YELLOW);
  // canvas->fillRoundRect(391,0,28,16,3,GREEN);
  // canvas->fillRoundRect(421,0,28,16,3,GREEN);
  // canvas->fillRoundRect(451,0,28,16,3,GREEN);

  // Clear all lights
  canvas->fillRect(0,0,480,16,BLACK);

  if (revs == 0){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 1){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 2){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 3){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(91,0,28,16,3,YELLOW);

    canvas->fillRoundRect(361,0,28,16,3,YELLOW);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 4){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(91,0,28,16,3,YELLOW);
    canvas->fillRoundRect(121,0,28,16,3,YELLOW);

    canvas->fillRoundRect(331,0,28,16,3,YELLOW);
    canvas->fillRoundRect(361,0,28,16,3,YELLOW);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 5){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(91,0,28,16,3,YELLOW);
    canvas->fillRoundRect(121,0,28,16,3,YELLOW);
    canvas->fillRoundRect(151,0,28,16,3,YELLOW);

    canvas->fillRoundRect(301,0,28,16,3,YELLOW);
    canvas->fillRoundRect(331,0,28,16,3,YELLOW);
    canvas->fillRoundRect(361,0,28,16,3,YELLOW);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 6){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(91,0,28,16,3,YELLOW);
    canvas->fillRoundRect(121,0,28,16,3,YELLOW);
    canvas->fillRoundRect(151,0,28,16,3,YELLOW);
    canvas->fillRoundRect(181,0,28,16,3,RED);

    canvas->fillRoundRect(271,0,28,16,3,RED);
    canvas->fillRoundRect(301,0,28,16,3,YELLOW);
    canvas->fillRoundRect(331,0,28,16,3,YELLOW);
    canvas->fillRoundRect(361,0,28,16,3,YELLOW);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 7){
    canvas->fillRoundRect(1,0,28,16,3,GREEN);
    canvas->fillRoundRect(31,0,28,16,3,GREEN);
    canvas->fillRoundRect(61,0,28,16,3,GREEN);
    canvas->fillRoundRect(91,0,28,16,3,YELLOW);
    canvas->fillRoundRect(121,0,28,16,3,YELLOW);
    canvas->fillRoundRect(151,0,28,16,3,YELLOW);
    canvas->fillRoundRect(181,0,28,16,3,RED);
    canvas->fillRoundRect(211,0,28,16,3,RED);

    canvas->fillRoundRect(241,0,28,16,3,RED);
    canvas->fillRoundRect(271,0,28,16,3,RED);
    canvas->fillRoundRect(301,0,28,16,3,YELLOW);
    canvas->fillRoundRect(331,0,28,16,3,YELLOW);
    canvas->fillRoundRect(361,0,28,16,3,YELLOW);
    canvas->fillRoundRect(391,0,28,16,3,GREEN);
    canvas->fillRoundRect(421,0,28,16,3,GREEN);
    canvas->fillRoundRect(451,0,28,16,3,GREEN);
  } else if (revs == 8){
    canvas->fillRoundRect(1,0,28,16,3,PURPLE);
    canvas->fillRoundRect(31,0,28,16,3,PURPLE);
    canvas->fillRoundRect(61,0,28,16,3,PURPLE);
    canvas->fillRoundRect(91,0,28,16,3,PURPLE);
    canvas->fillRoundRect(121,0,28,16,3,PURPLE);
    canvas->fillRoundRect(151,0,28,16,3,PURPLE);
    canvas->fillRoundRect(181,0,28,16,3,PURPLE);
    canvas->fillRoundRect(211,0,28,16,3,PURPLE);

    canvas->fillRoundRect(241,0,28,16,3,PURPLE);
    canvas->fillRoundRect(271,0,28,16,3,PURPLE);
    canvas->fillRoundRect(301,0,28,16,3,PURPLE);
    canvas->fillRoundRect(331,0,28,16,3,PURPLE);
    canvas->fillRoundRect(361,0,28,16,3,PURPLE);
    canvas->fillRoundRect(391,0,28,16,3,PURPLE);
    canvas->fillRoundRect(421,0,28,16,3,PURPLE);
    canvas->fillRoundRect(451,0,28,16,3,PURPLE);
  } else {
    // Do nothing if revs is out of range
  }
}

void drawGears(char gear){
  canvas->fillRoundRect((480-(5*12+12))/2, 21, 5*12+12, 7*12+8, 3, lightGrey); // draw background
  canvas->setCursor(210, 25);
  canvas->setTextColor(WHITE);
  canvas->setTextSize(12);
  canvas->print(gear);
}

void drawSpeed(int speed){
  canvas->fillRoundRect((480-(5*12+12))/2, 115, 5*12+12, 7*2+8, 3, WHITE); // draw background

  // Convert speed to string
  String speedStr = String(speed);

  // Calculate text bounds for centering horizontally
  int16_t x1, y1;
  uint16_t w, h;
  canvas->setTextSize(2);
  canvas->getTextBounds(speedStr, 0, 0, &x1, &y1, &w, &h);

  // Center horizontally, keep original vertical position (115+4)
  int16_t x = (480 - w) / 2;
  int16_t y = 115 + 4;

  canvas->setCursor(x, y);
  canvas->setTextColor(BLACK);
  canvas->print(speedStr);
}

void drawDelta(float delta){
  String deltaStr = String(delta,3);

  if (delta < 0) {
    canvas->fillRoundRect((480-(5*12+12))/2, 138, 5*12+12, 7*2+8, 3, GREEN); // draw background
  } else {
    canvas->fillRoundRect((480-(5*12+12))/2, 138, 5*12+12, 7*2+8, 3, RED); // draw background
    deltaStr = "+"+deltaStr;
  }

  // Calculate text bounds for centering horizontally
  int16_t x1, y1;
  uint16_t w, h;
  canvas->setTextSize(2);
  canvas->getTextBounds(deltaStr, 0, 0, &x1, &y1, &w, &h);

  // Center horizontally, keep original vertical position (115+4)
  int16_t x = (480 - w) / 2;
  int16_t y = 142;

  canvas->setCursor(x+1, y);
  canvas->setTextColor(BLACK);
  canvas->print(deltaStr);
}

void drawLights(bool lightsOn){
  const int rectWidth = 35;
  const int rectHeight = 7*2+8;
  const int rectX = (480-(5*12+12))/2;
  const int rectY = 161;
  const int iconWidth = 14;
  const int iconHeight = 14;

  // Draw background rectangle
  if (lightsOn){
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, BLUE);
  } else {
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, lightGrey);
  }

  // Calculate center position for icon
  int iconX = rectX + (rectWidth - iconWidth)/2;
  int iconY = rectY + (rectHeight - iconHeight)/2;

  // Draw centered icon
  canvas->drawBitmap(iconX, iconY, epd_bitmap_Headlights_icon, iconWidth, iconHeight, WHITE);
}

void drawWipers(bool wipersOn){
  const int rectWidth = 35;
  const int rectHeight = 7*2+8;
  const int rectX = 241;
  const int rectY = 161;
  const int iconWidth = 14;
  const int iconHeight = 14;

  // Draw background rectangle
  if (wipersOn){
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, BLUE);
  } else {
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, lightGrey);
  }

  // Calculate center position for icon
  int iconX = rectX + (rectWidth - iconWidth)/2;
  int iconY = rectY + (rectHeight - iconHeight)/2;

  // Draw centered icon
  canvas->drawBitmap(iconX, iconY, epd_bitmap_Wipers_Icon, iconWidth, iconHeight, WHITE);
}

void drawIgn(bool ignOn){
  const int rectWidth = 72;
  const int rectHeight = 15;
  const int rectX = (480-(5*12+12))/2;
  const int rectY = 269-15;

  // Draw background rectangle
  if (ignOn){
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, RED);
  } else {
    canvas->fillRoundRect(rectX, rectY, rectWidth, rectHeight, 3, lightGrey);
  }

  // Calculate text bounds for centering
  canvas->setTextSize(1);
  canvas->setTextColor(WHITE);
  int16_t x1, y1;
  uint16_t w, h;
  canvas->getTextBounds("IGN", 0, 0, &x1, &y1, &w, &h);

  // Calculate centered position
  int textX = rectX + (rectWidth - w)/2;
  int textY = rectY + (rectHeight - h)/2;

  canvas->setCursor(textX, textY);
  canvas->print("IGN");
}

void drawIR (int IR){
  const int rectWidth = 72;
  const int rectHeight = 18;
  const int rectX = (480-(5*12+12))/2;
  const int rectY = 269-15-20;

  canvas->drawRoundRect(rectX, rectY, rectWidth, rectHeight, 3, WHITE);
  canvas->drawBitmap(rectX + 2, rectY + 2, epd_bitmap_Flag_Icon, 14, 14, WHITE);
  
  canvas->setTextSize(1);
  canvas->setTextColor(WHITE);
  canvas->setCursor(rectX + 30, rectY + 6);
  canvas->print(IR);
}

void drawFlag (int flagStatus) {
  const int rectWidth = 72;
  const int rectHeight = 47;
  const int rectX = (480-(5*12+12))/2;
  const int rectY = 185;

  canvas->drawRoundRect(rectX, rectY, rectWidth, rectHeight, 3, WHITE);
  canvas->fillRoundRect(rectX+1, rectY+1, rectWidth-2, rectHeight-2, 3, BLACK);  // Clear past flag
  
  switch(flagStatus) {
        case 1:
            canvas->fillRoundRect(rectX+2, rectY+2, rectWidth-4, rectHeight-4, 3, GREEN);  // Green flag
            break;
        case 2:
            canvas->fillRoundRect(rectX+2, rectY+2, rectWidth-4, rectHeight-4, 3, YELLOW);  // Yellow flag
            break;
        case 3:
            canvas->fillRoundRect(rectX+2, rectY+2, rectWidth-4, rectHeight-4, 3, RED);  // Red flag
            break;
        case 4:
            canvas->fillRoundRect(rectX+2, rectY+2, rectWidth-4, rectHeight-4, 3, BLUE);  // Blue flag
            break;
        case 5:
            canvas->fillTriangle(
              rectX+2,              rectY + rectHeight -4,    // bottom left (x1,y1)
              rectX + rectWidth-4,  rectY + 2,                // top right (x2,y2)
              rectX + rectWidth-4,  rectY + rectHeight -4,    // bottom right (x3,y3)
              WHITE                                           // Color
            );
            break;  
        case 6:
            canvas->drawBitmap(rectX + 2, rectY + 2, epd_bitmap_checkered_flag, 68, 43, WHITE);  // Checkered flag
            break;
        default:
            canvas->drawLine(rectX + 10, rectY + 10, rectX + rectWidth - 10, rectY + rectHeight - 10, WHITE);
            canvas->drawLine(rectX + 10, rectY + rectHeight - 10, rectX + rectWidth - 10, rectY + 10, WHITE);  // No flag
            break;
    }
}

void drawBB(float BB){
  // Clear the BB box area
  canvas->fillRoundRect(308, 224, 67, 40, 3, BLACK);
  
  // Convert to string with 1 decimal place
  String fullStr = String(BB, 1);
  
  // Find the decimal point position
  int decimalPos = fullStr.indexOf('.');
  
  // Split into two parts
  String integerPart = fullStr.substring(0, decimalPos);
  String decimalPart = fullStr.substring(decimalPos + 1);

  canvas->setTextColor(RED);
  canvas->setTextSize(3);
  canvas->setCursor(311, 220 + (48 - 21)/2); // Center vertically in BB box
  canvas->print(integerPart); // Print BB value with 1 decimal place
  canvas->setCursor(canvas->getCursorX() - 6,canvas->getCursorY());
  canvas->print("."); // Print decimal point
  canvas->setCursor(canvas->getCursorX() -3,canvas->getCursorY());
  canvas->print(decimalPart); // Print decimal part
}

void drawABS(int ABS){
  // Clear the ABS box area
  canvas->fillRoundRect(308, 224, 67, 40, 3, BLACK);

  canvas->setTextColor(YELLOW);
  canvas->setTextSize(3);
  canvas->setCursor(434,234);
  canvas->print(ABS);
}

void drawTC(int TC, int TC_CUT){
  // Clear the TC box area
  canvas->fillRoundRect(72, 224, 35, 18, 3, BLACK);
  canvas->fillRoundRect(72, 224+22, 35, 18, 3, BLACK);

  // Draw TC value
  canvas->setTextColor(softBlue);
  canvas->setTextSize(2);
  canvas->setCursor(75+10, 224 + (18 - 14)/2);
  canvas->print(TC);
  canvas->setCursor(75+10, 224 + 22 + (18 - 14)/2);
  canvas->print(TC_CUT);
}

void drawMAP(int MAP){
  // Clear the MAP box area
  canvas->fillRoundRect(162, 224, 35, 40, 3, BLACK);

  // Draw MAP value
  canvas->setTextColor(GREEN);
  canvas->setTextSize(3);
  canvas->setCursor(162+11,234);
  canvas->print(MAP);
}

void drawLapTimes(String currentLapTime, String lastLapTime, String bestLapTime) {
    // Box dimensions: x=278, y=69, w=188, h=147
    const int boxX = 278;
    const int boxY = 69;  // Updated from 72
    const int boxWidth = 188;
    const int boxHeight = 147;
    
    // Calculate vertical spacing
    const int sectionHeight = boxHeight / 3;
    
    // Labels (small text)
    canvas->setTextSize(1);
    canvas->setTextColor(WHITE);
    canvas->setCursor(boxX + 5, boxY + 5);
    canvas->print("CURRENT:");
    canvas->setCursor(boxX + 5, boxY + sectionHeight + 5);
    canvas->print("LAST:");
    canvas->setCursor(boxX + 5, boxY + (sectionHeight * 2) + 5);
    canvas->print("BEST:");

    // Times (larger text)
    canvas->setTextSize(3);  // Increased text size
    
    // Center each time string
    int16_t x1, y1;
    uint16_t w, h;
    
    // Current lap time
    canvas->getTextBounds(currentLapTime, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + (boxWidth - w)/2, boxY + 20);
    canvas->print(currentLapTime);
    
    // Last lap time
    canvas->getTextBounds(lastLapTime, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + (boxWidth - w)/2, boxY + sectionHeight + 20);
    canvas->setTextColor(offWhite);
    canvas->print(lastLapTime);
    
    // Best lap time
    canvas->getTextBounds(bestLapTime, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + (boxWidth - w)/2, boxY + (sectionHeight * 2) + 20);
    canvas->setTextColor(PURPLE);
    canvas->print(bestLapTime);
}

void drawRaceInfo(int position, int totalCars, int lap, String time) {
    // Box dimensions: x=278, y=21, w=199, h=44
    const int boxX = 278;
    const int boxY = 21;
    const int boxWidth = 199;
    const int boxHeight = 44;

    // Clear the box area
    canvas->fillRoundRect(boxX+1, boxY+1, boxWidth-2, boxHeight-2, 3, BLACK);

    // Calculate section widths
    const int sectionWidth = boxWidth / 3;

    // Position number (first part of fraction)
    canvas->setTextSize(3);
    canvas->setTextColor(WHITE);
    String posStr = String(position);
    int16_t x1, y1;
    uint16_t w, h;
    canvas->getTextBounds(posStr, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + 15, boxY + 12);
    canvas->print(posStr+"/");

    // Total cars (second part of fraction)
    canvas->setTextSize(1);
    canvas->setCursor(canvas->getCursorX()-8,canvas->getCursorY() + 14);
    String totalStr = String(totalCars);
    canvas->print(totalStr);  // Print total cars

    // Reset text size for remaining elements
    canvas->setTextSize(2);

    // Lap number (e.g., "L15")
    String lapStr = "L" + String(lap);
    canvas->getTextBounds(lapStr, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + sectionWidth + (sectionWidth - w)/2, boxY + (boxHeight - h)/2);
    canvas->print(lapStr);

    // Time (e.g., "00:00")
    canvas->getTextBounds(time, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + (sectionWidth * 2) + (sectionWidth - w)/2, boxY + (boxHeight - h)/2);
    canvas->print(time);
}

void drawFuelInfo(float fuelLevel, float fuelAvgPerLap, float fuelLapsRemaining) {
    // Box dimensions: x=3, y=21, w=199, h=44
    const int boxX = 3;
    const int boxY = 21;
    const int boxWidth = 199;
    const int boxHeight = 44;

    // Clear the box area
    canvas->fillRect(boxX + 1, boxY + 16, boxWidth - 2, boxHeight - 17, BLACK);  // Clear numbers area only

    // Calculate section widths
    const int sectionWidth = boxWidth / 3;
    
    // Move all numbers down by 8 pixels to leave room for labels
    const int verticalOffset = 8;

    // Fuel Level (first section) - Format: "99.9L"
    canvas->setTextSize(2);
    canvas->setTextColor(WHITE);
    String fuelStr = String(fuelLevel, 1);
    int16_t x1, y1;
    uint16_t w, h;
    canvas->getTextBounds(fuelStr, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + 10, boxY + (boxHeight - h)/2 + verticalOffset);
    canvas->print(fuelStr);
    
    // Add "L" in smaller font
    canvas->setTextSize(1);
    canvas->setCursor(canvas->getCursorX(), canvas->getCursorY() + 7);
    canvas->print("L");

    // Fuel per Lap (middle section) - Format: "9.9"
    canvas->setTextSize(2);
    String avgStr = String(fuelAvgPerLap, 1);
    canvas->getTextBounds(avgStr, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + sectionWidth + (sectionWidth - w)/2, boxY + (boxHeight - h)/2 + verticalOffset);
    canvas->print(avgStr);

    // Laps Remaining (last section) - Format: "99.9"
    String lapsStr = String(fuelLapsRemaining, 1);
    canvas->getTextBounds(lapsStr, 0, 0, &x1, &y1, &w, &h);
    canvas->setCursor(boxX + (sectionWidth * 2) + (sectionWidth - w)/2, boxY + (boxHeight - h)/2 + verticalOffset);
    canvas->print(lapsStr);
}

void drawGaps(float gapAhead, float gapBehind) {
  // Clear old text
  canvas->fillRect(63, 72, 135, 20, BLACK); // Clear gap ahead text area
  canvas->fillRect(63, 94, 135, 20, WHITE); // Clear gap behind text area
  // gap ahead
  canvas->setTextSize(2);
  canvas->setTextColor(WHITE);
  int16_t x, y;
  uint16_t w, h;
  String strGapAhead = "+" + String(gapAhead, 3); // Example gap ahead
  canvas->getTextBounds(strGapAhead, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(134 - w/2,75);
  canvas->print(strGapAhead);
  // gap behind
  String strGapBehind = "-" + String(gapBehind, 3); // Example gap behind
  canvas->getTextBounds(strGapBehind, 0, 0, &x, &y, &w, &h);
  canvas->setTextColor(BLACK);
  canvas->setCursor(134 - w/2,97);
  canvas->print(strGapBehind);
}

void drawTyreInfo (float tyrePressures[], int tyreTemps[], String tyreSet) {
  
  int centreX = 111;
  int centreY = 165;

  int HL =49;
  int HR = 174;
  int VT = 126;
  int VB = 179;

  int16_t x, y;
  uint16_t w, h;
  
  // clear old data
  canvas->fillRect(23,120,50,90,BLACK);
  canvas->fillRect(149,120,50,90,BLACK);
  canvas->fillRect(70,155,80,22,BLACK);
  // Draw tyre pressures

  canvas->setTextSize(2);
  canvas->setTextColor(WHITE);
  canvas->getTextBounds(String(tyrePressures[0], 1), 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HL - w/2, VT);
  canvas->print(String(tyrePressures[0], 1));

  canvas->getTextBounds(String(tyrePressures[1], 1), 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HR - w/2, VT);
  canvas->print(String(tyrePressures[1], 1));

  canvas->getTextBounds(String(tyrePressures[2], 1), 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HL - w/2, VB);
  canvas->print(String(tyrePressures[2], 1));

  canvas->getTextBounds(String(tyrePressures[3], 1), 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HR - w/2, VB);
  canvas->print(String(tyrePressures[3], 1));

  // Draw tyre temperatures
  canvas->setTextSize(1);
  canvas->setTextColor(offWhite);

  String tyreTempStr = String(tyreTemps[0])+" C";
  canvas->getTextBounds(tyreTempStr, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HL - w/2, VT + 20);
  canvas->print(tyreTempStr);

  tyreTempStr = String(tyreTemps[1])+" C";
  canvas->getTextBounds(tyreTempStr, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HR - w/2, VT + 20);
  canvas->print(tyreTempStr);

  tyreTempStr = String(tyreTemps[2])+" C";
  canvas->getTextBounds(tyreTempStr, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HL - w/2, VB + 20);
  canvas->print(tyreTempStr);

  tyreTempStr = String(tyreTemps[3])+" C";
  canvas->getTextBounds(tyreTempStr, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(HR - w/2, VB + 20);
  canvas->print(tyreTempStr);

  // Draw tyre set
  canvas->setTextSize(1);
  canvas->setTextColor(offWhite);;
  canvas->getTextBounds("SET", 0, 0, &x, &y, &w, &h);
  canvas->setCursor(centreX - w/2, centreY - 18);
  canvas->print("SET");
  canvas->setTextSize(2);
  canvas->getTextBounds(tyreSet, 0, 0, &x, &y, &w, &h);
  canvas->setCursor(centreX - w/2, centreY -6);
  canvas->print(tyreSet);
}

void setup() {
  Serial.begin(115200);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif

  // Create and intialise the main canvas
  canvas = new Arduino_Canvas(480, 272,gfx);
  canvas->begin();
  
  // Clear any leftovers from the display
  canvas->fillScreen(BLACK);
  canvas->flush();

  float tyrePressures[4] = {32.1, 32.2, 32.3, 32.4}; // Example tyre pressures
  int tyreTemps[4] = {71,72,73,74}; // Example tyre temperatures

  // Intial display setup
  drawBackground();
  drawSpeed(999);
  drawDelta(-1.234);
  drawLights(true); 
  drawWipers(false);
  drawIgn(true);
  drawIR(12345);
  drawFlag(0);
  drawBB(55.5);
  drawABS(3);
  drawTC(5, 2);
  drawMAP(3);
  drawLapTimes("00:00.000", "00:00.000", "00:00.000");// current - last - best
  drawRaceInfo(15, 23, 15, "00:00");// position - total cars - lap - time
  drawFuelInfo(50.5, 2.5, 20); // fuel level - fuel per lap - laps remaining
  drawTyreInfo(tyrePressures, tyreTemps, "HARD");
}

void loop() {
  // Simulate gear changes
      
  char gears[] = {'R', 'N', '1', '2', '3', '4', '5', '6'};
  int gearIndex = 0;
  for (int i = 0; i < 8; i++) {
    drawGears(gears[i]);
    drawFlag(i);

    drawBB(50.0 + i*2.1);
    drawGaps(4.123+i*7,5.456+i*3.215);
    for(int j = 0; j < 9;j++) {
      drawRevLights(j);
      canvas->flush();
      delay(120);
    }
    delay(300);
    canvas->flush();
  }
  delay(2000); // Keep the display for a while before repeating
}

