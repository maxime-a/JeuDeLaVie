#include<stdlib.h>
#include<stdio.h>
#include"libsx.h"
#include"jeu.h"

#include"rappels.h"

void quit(Widget w, void *data)
{
	if(GetYesNo("Are you sure you want to quit ?"))
	{
		freeGrid(&g->cells);
		free(g);
		exit(0);
	}
}

void clear(Widget w, void *data)
{
	if(GetYesNo("Are you sure you want to restart from zero ?"))
	{
		ClearDrawArea();
		if(g->grid)
			drawGrid();
		setGrid(&g->cells,0);
	}
}

void button_up(Widget w, int which_button, int x, int y, void *data)
{
	if(which_button==1)
	{
		if(x/10<g->cells.width && y/10<g->cells.height)	//eviter de dessiner sur des indices interdits lors de l'agrandissement de la fenêtre
		{
			DrawFilledBox(x/10*10, y/10*10, 10, 10); 
			g->cells.values[x/10][y/10]=vivant;
		}
	}  
	else
	{ 
	  	g->cells.values[x/10][y/10]=mort;
		draw();
	}
}

void redraw(Widget w, int width, int height, void *data)
{
	draw();	
}

void  set_timeout_val(Widget w, float val, void *data)
{
  g->timeout = (int)val*10+10;
  char s[40];
  sprintf(s,"Periode : %.2fs      ",(float)g->timeout/1000);
  SetLabel(data,s);
  
}

 void  tic(void *data)
{
	//Beep();
	update(g);
	
	char s[40];
	sprintf(s,"Generation numero : %4d",g->generation);
	SetLabel(data,s);
	 
	draw();
	
	if (g->remove_timeout == FALSE)
    		AddTimeOut(g->timeout, tic, data);
  	else
    		g->remove_timeout = FALSE;
}

void anim(Widget w, void *data)
{
  if (GetToggleState(w))
   {
     SetLabel(w, "Stop Anim");
     AddTimeOut(g->timeout, tic, data); 
   }
  else
   {
     g->remove_timeout = TRUE;
     SetLabel(w, "  Animate  ");
   }
}

void load(Widget w, char *string, void *data)
{
	if(GetYesNo("Are you sure you want to load a new state from this file name ?"))
		chargerFichier(string,data);
}

void loadb(Widget w, void *data)
{
	char *string=GetStringEntry(data); 
	
	if(GetYesNo("Are you sure you want to load a new state from this file name ?"))
		chargerFichier(string,data);
}

void saveb(Widget w, void *data)
{
	char *string=GetStringEntry(data); 
	
	if(GetYesNo("Are you sure you want to save this state with this file name ?"))
		saveFile(string,data);
}

void modb(Widget w, void *data)
{
	if(GetToggleState(w))
	{
		g->variant=thompson;
		SetLabel(w,"Thompson");
	}
	else
	{
		g->variant=conway;
		SetLabel(w,"Conway");
	}
}

void helpb(Widget w, void *data)
{
	GetOkay("-Type a name and click corresponding buttons for loading or saving a game state\n-Use slider to change period\n-Left click on the drawing area to add a living cell\n-Right click on the drawing area to kill a cell");
}

void gridb(Widget w, void *data)
{
	if(GetToggleState(w))
	{
		g->grid=1;
		drawGrid();
		SetLabel(w,"Turn grid off");
	}
	else
	{	
		g->grid=0;
		draw();
		SetLabel(w,"Turn grid on");
	}
}
