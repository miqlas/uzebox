/*
 *  Uzebox video mode 5 simple demo
 *  Copyright (C) 201`  Alec Bourque
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>


#include "data/tiles.inc"
#include "data/fonts6x8.inc"
#include "data/patches.inc"

int main(){

	InitMusicPlayer(patches);

	GetPrngNumber(12712);

	//set first scanline to render to 20, and render 1 lines
	//Note: don't set the lines to render to zero. There's a bug that will
	//cause WaitVsync() to hang.
	SetRenderingParameters(112, 1); 

	SetTileTable(tiles);			//Set the tileset to use (set this first)
	SetFontTilesIndex(TILES_SIZE);	//Set the tile number in the tilset that contains the first font
	ClearVram();					//Clear the screen (fills the vram with tile zero)

	Fill(0,0,40,28,30);
	Fill(6,9,28,7,0);

	Print(8,10,PSTR("HELLO WORLD FROM MODE 5!"));
	Print(7,12,PSTR("40X28 VRAM - 8-BIT INDEXES"));
	Print(12,14,PSTR("6X8 PIXELS TILES"));

	for(u8 i=1;i<26;i++){
		PrintInt(10,i,GetPrngNumber(0),true);
	}
	
	u8 j=112;
	for(u8 i=1;i<112;i++){
		WaitVsync(1);
		SetRenderingParameters(20+j, i*2);
		j--;
	}


		

	//unsigned char channel,unsigned char patch,unsigned char note,unsigned char volume//
	//TriggerNote(0,0,60,0xff);

	u16 joy;
	while(1){
		WaitVsync(1);
		joy=ReadJoypad(0);
		if(joy==BTN_A){
			TriggerNote(0,0,70,0xff);
		}else if(joy==BTN_B){
			TriggerNote(0,0,60,0xff);
		}else if(joy==BTN_X){
			TriggerNote(0,1,70,0xff);
		}else if(joy==BTN_Y){
			TriggerNote(0,1,60,0xff);
		}
		while(ReadJoypad(0)!=0);
	}

} 
