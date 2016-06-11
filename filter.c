/* Copyright (C)
* 2015 - John Melton, G0ORX/N6LYT
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*/

#include "filter.h"

FILTER filterLSB[FILTERS]={
    {-5150,-150,"5.0k"},
    {-4550,-150,"4.4k"},
    {-3950,-150,"3.8k"},
    {-3450,-150,"3.3k"},
    {-3050,-150,"2.9k"},
    {-2850,-150,"2.7k"},
    {-2550,-150,"2.4k"},
    {-2250,-150,"2.1k"},
    {-1950,-150,"1.8k"},
    {-1150,-150,"1.0k"}/*,
    {-2850,-150,"Var1"},
    {-2850,-150,"Var2"}*/
    };

FILTER filterDIGL[FILTERS]={
    {-5150,-150,"5.0k"},
    {-4550,-150,"4.4k"},
    {-3950,-150,"3.8k"},
    {-3450,-150,"3.3k"},
    {-3050,-150,"2.9k"},
    {-2850,-150,"2.7k"},
    {-2550,-150,"2.4k"},
    {-2250,-150,"2.1k"},
    {-1950,-150,"1.8k"},
    {-1150,-150,"1.0k"}/*,
    {-2850,-150,"Var1"},
    {-2850,-150,"Var2"}*/
    };

FILTER filterUSB[FILTERS]={
    {150,5150,"5.0k"},
    {150,4550,"4.4k"},
    {150,3950,"3.8k"},
    {150,3450,"3.3k"},
    {150,3050,"2.9k"},
    {150,2850,"2.7k"},
    {150,2550,"2.4k"},
    {150,2250,"2.1k"},
    {150,1950,"1.8k"},
    {150,1150,"1.0k"}/*,
    {150,2850,"Var1"},
    {150,2850,"Var2"}*/
    };

FILTER filterDIGU[FILTERS]={
    {150,5150,"5.0k"},
    {150,4550,"4.4k"},
    {150,3950,"3.8k"},
    {150,3450,"3.3k"},
    {150,3050,"2.9k"},
    {150,2850,"2.7k"},
    {150,2550,"2.4k"},
    {150,2250,"2.1k"},
    {150,1950,"1.8k"},
    {150,1150,"1.0k"}/*,
    {150,2850,"Var1"},
    {150,2850,"Var2"}*/
    };

FILTER filterCWL[FILTERS]={
    {500,500,"1.0k"},
    {400,400,"800"},
    {375,375,"750"},
    {300,300,"600"},
    {250,250,"500"},
    {200,200,"400"},
    {125,125,"250"},
    {50,50,"100"},
    {25,25,"50"},
    {13,13,"25"}/*,
    {250,250,"Var1"},
    {250,250,"Var2"}*/
    };

FILTER filterCWU[FILTERS]={
    {500,500,"1.0k"},
    {400,400,"800"},
    {375,375,"750"},
    {300,300,"600"},
    {250,250,"500"},
    {200,200,"400"},
    {125,125,"250"},
    {50,50,"100"},
    {25,25,"50"},
    {13,13,"25"}/*,
    {250,250,"Var1"},
    {250,250,"Var2"}*/
    };

FILTER filterAM[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

FILTER filterSAM[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

FILTER filterFMN[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

FILTER filterDSB[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

FILTER filterSPEC[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

FILTER filterDRM[FILTERS]={
    {-8000,8000,"16k"},
    {-6000,6000,"12k"},
    {-5000,5000,"10k"},
    {-4000,4000,"8k"},
    {-3300,3300,"6.6k"},
    {-2600,2600,"5.2k"},
    {-2000,2000,"4.0k"},
    {-1550,1550,"3.1k"},
    {-1450,1450,"2.9k"},
    {-1200,1200,"2.4k"}/*,
    {-3300,3300,"Var1"},
    {-3300,3300,"Var2"}*/
    };

#ifdef FREEDV
FILTER filterFREEDV[FILTERS]={
    {150,5150,"5.0k"},
    {150,4550,"4.4k"},
    {150,3950,"3.8k"},
    {150,3450,"3.3k"},
    {150,3050,"2.9k"},
    {150,2850,"2.7k"},
    {150,2550,"2.4k"},
    {150,2250,"2.1k"},
    {150,1950,"1.8k"},
    {150,1150,"1.0k"}/*,
    {150,2850,"Var1"},
    {150,2850,"Var2"}*/
    };
#endif


FILTER *filters[]={
    filterLSB
    ,filterUSB
    ,filterDSB
    ,filterCWL
    ,filterCWU
    ,filterFMN
    ,filterAM
    ,filterDIGU
    ,filterSPEC
    ,filterDIGL
    ,filterSAM
    ,filterDRM
#ifdef FREEDV
    ,filterFREEDV
#endif
};

